#ifndef CO_ROUTINE_MGR_H
#define CO_ROUTINE_MGR_H
#include <algorithm>
#include <list>
#include <unordered_map>
#include <memory>
#include "utils.h"
#include "socketopt.h"
#include "log.h"
#include "const_define.h"

#define GETINDEX(id) id/32
#define LOOP_INDEX 1

#define ADD_RUN_TASK(run_mask, free_mask, new_index, old_index) \
        FD_SET(new_index, &run_mask); \
        if (old_index != 0) \
            FD_CLR(old_index, &free_mask);

#define RM_RUN_TASK(run_mask, free_mask, new_index) \
        if (new_index != 0) \
            FD_CLR(new_index, &run_mask); \
        FD_SET(new_index, &free_mask); 

#define RECOVER_TASK(run_mask, free_mask, new_index, old_index) \
        RM_RUN_TASK(run_mask, free_mask, new_index) \
        ADD_RUN_TASK(run_mask, free_mask, old_index, new_index)

class CoRoutine;

class CoTask {
public:
    CoTask():id(0), fd(-1), timeout(kDefaultTimeout),ev_mask(0) {
     
    }
    ~CoTask();
    void Init();

    void SetProcess(CoRoutineFunc func, void* attr);

    void SetPreProcess(CoRoutineFunc func, void* attr);

    int Run();
public:
    uint32_t id;
    int32_t fd;
    uint64_t timeout;
    uint32_t ev_mask;
    CoRoutine* co_routine;
    sockaddr_in addr;
};

class CoRoutineMgr {
public:
    CoRoutineMgr():cur_co_index_(LOOP_INDEX),share_stack_(nullptr), share_stack_size_(kDefaultTotalStackSize),share_stack_cur_index_(0)
                    , max_co_count_(1024), is_init_(false){ MYLOG(INFO, "%s", "CoRoutineMgr Contructotr");}
    ~CoRoutineMgr()
    {
        MYLOG(INFO, "%s", "CoRoutineMgr destructor");
    }

    static CoRoutineMgr& Instance() {
        static CoRoutineMgr mgr;
        return mgr;
    }

    int Init(uint32_t co_count, uint32_t stack_size = kDefaultStackSize, uint32_t share_stack_size = kDefaultTotalStackSize);//初始化协程
    void Schedule(CoTask& task);
    int YieldTask();
    int GetActiveEvent();
    int CreateCoTask(CoRoutineFunc func, void* attr, int32_t fd, uint32_t stack_size = kDefaultStackSize, bool shareStack = false, bool run_now = false);
    CoTask &GetCoTask(int index) {
        return co_task_vec_[index];
    }
    inline uint32_t GetCurrentCoIndex() {return cur_co_index_;}

    int32_t RemoveRunTask(uint32_t id) {
        RM_RUN_TASK(run_co_task_mask_[GETINDEX(id)], free_co_task_mask_[0], id);
        free_co_task_list_.push_back(id);
        cur_co_index_ = LOOP_INDEX;
        return EC_OK;
    }
private:
    void SwitchRoutine(CoTask& src_ctx, CoTask& dst_ctx);

    uint32_t GetNextEventIndex();

    void Resume(CoTask& dst_ctx);

    int Resume(uint32_t id);

private:
    uint32_t cur_co_index_;
    unsigned char* share_stack_;
    uint64_t share_stack_size_;
    uint64_t share_stack_cur_index_;
    uint32_t max_co_count_;
    bool is_init_;

    std::vector<CoTask > co_task_vec_;
    fd_set run_co_task_mask_[1024];
    fd_set free_co_task_mask_[1024];
    //fd_set wait_co_task_mask_[1024];
    std::list<uint32_t> free_co_task_list_;
;
private:
    CoRoutineMgr(const CoRoutineMgr&) = delete;
    CoRoutineMgr& operator = (const CoRoutineMgr&) = delete;
};
#endif