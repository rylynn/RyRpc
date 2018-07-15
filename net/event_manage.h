#ifndef EVENT_MANAGE_H
#define EVENT_MANAGE_H
#include <unordered_map>
#include "co_routine_mgr.h"
#include <vector>
#include <unordered_map>
#include <list>
#include "co_routine_mgr.h"
#include "event.h"
#include "poller.h"

#define INIT_HEAP(v, compare) static_assert(typeid(v).name == typeid(std::vector)) \
    std::make_heap(v.begin(), v.end(), compare);

#define HEAP_POP(v, compare) static_assert(typeid(v).name == typeid(std::vector)) \
    std::pop_heap(v.begin(), v.end(), compare); \
    auto largest = v.back();\
    v.pop_back();

#define HEAP_PUSH(v, n, compare) static_assert(typeid(v).name == typeid(std::vector)) \
    v.push_back(n);\
    std::push_heap(v.begin(), v.end(), compare);

class Poller;

class Socket {
public:
    int32_t fd;
    uint32_t cur_used_co;
    uint64_t last_ts;
};

class EventManager {
public:
    EventManager(){
            MYLOG(INFO,"%s",  "EventManager constructor");
        }
    ~EventManager() {
        MYLOG(INFO,"%s",  "EventManager destructor");
    }

    static EventManager& Instance() {
        static EventManager mgr;
        return mgr;
    }

    int Init(std::string ip, int16_t port, int32_t type = IPPROTO_TCP);
    void Start();
    //int Loop();
    int Wait(CoTask& co_task, uint32_t ev_mask);
    int Process() {
        if (func_ != nullptr) return func_(attr_);
        return EC_SYS_ERR;
    }
    void SetProcess(CoRoutineFunc func, void* attr) {
        func_ = func;
        attr_ = attr;
    }

    int AddTask(int32_t fd, CoRoutineFunc func, void* attr);
    CoTask& GetCurrentCo() { return CoRoutineMgr::Instance().GetCoTask(CoRoutineMgr::Instance().GetCurrentCoIndex());}
    int32_t Read(CoTask& co_task, char* buf, int32_t& size, uint32_t timeout, CheckEOF checkfunc);
    int32_t Write(CoTask& co_task, char* buf, int32_t size, uint32_t timeout);
    int Connect(CoTask &co_task, std::string &ip, int16_t port, uint32_t timeout);
    int32_t Poll(std::vector<Event>& events, uint64_t time_out /*ms*/) {
        if (poller_ptr_ == nullptr) {
            return EC_SYS_ERR;
        }
        return poller_ptr_->Poll(events, time_out);
    }
    int32_t AddEvent(int fd, int ev_mask, void* data = NULL) {
        return poller_ptr_->AddEvent(fd, ev_mask, data);
    }
    const Socket& SvrSocket() {
        return svr_sock_;
    }
    uint32_t& CurClient() {
        return cur_connect_client_;
    }
    uint64_t GetLastTimeout() { return cur_ts_;}
    int CloseTailConnect();
    int HandleTimeout();
private:
    Socket svr_sock_;
    Poller* poller_ptr_;
    uint32_t cur_connect_client_;
    uint64_t cur_ts_;
    Ticker ticker_;
    //CoRoutineMgr& co_routine_mgr_;
    CoRoutineFunc func_;
    void* attr_;

    std::vector<uint64_t> timeout_node_;
    std::unordered_map<uint32_t/*address md5*/, std::list<Socket> > socket_map_;

    EventManager(const EventManager&) = delete;
    EventManager& operator = (const EventManager&) = delete;
};

#endif