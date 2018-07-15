#include "event_manage.h"
#include "log.h"
#include "socketopt.h"
#include "poller.h"
#include "const_define.h"


int CheckTail(char* buf, int32_t size) {
    return 0;
}

int MyProcess(void* attr) {
    EventManager* mgr = (EventManager*)attr;
    auto&& co_task = mgr->GetCurrentCo();
    MYLOG(INFO, "Process[%d] event:%d", CoRoutineMgr::Instance().GetCurrentCoIndex(), co_task.ev_mask);
    switch (co_task.ev_mask) {
        case READ_EVENT:
        {
            char buf[1024] = {0};
            int32_t size = sizeof(buf);
            int ret = mgr->Read(co_task, buf, size, 2000, &CheckTail);
            MYLOG(INFO, "Read co_task:%u buf:%s", co_task.id, buf);
            mgr->Write(co_task, buf, size, 2000);
        }
        break;
    }
    //return mgr->Process();
    return 0;
}

int AcceptFunc(int svr_fd) {
    if (svr_fd <= 0)
    {
        return EC_SYS_ERR;
    }

    sockaddr_in addr;
    socklen_t len = sizeof(addr);
    int connfd = ::accept(svr_fd, (sockaddr *)(&addr), (socklen_t *)&len);
    if (connfd > 0)
    {
        SetNonBlockAndCloseOnExec(connfd);
        SetReuseAddr(connfd, true);
        SetTcpNoDelay(connfd, true);
    }

    MYLOG(INFO, "new connect accept:%d", connfd);
    return connfd;
}

int SvrLoop(void* attr);

int EventManager::Init(std::string ip, int16_t port, int32_t type) {
    MYLOG(INFO, "ip:%s port:%u type:%u", ip.c_str(), port, type);
    poller_ptr_ = new KqueuePoller();
    poller_ptr_->Init();
    svr_sock_.fd = ::socket(AF_INET, SOCK_STREAM, type);

    struct sockaddr_in in_addr;
    memset(&in_addr, 0, sizeof(in_addr));
    in_addr.sin_family = AF_INET;
    in_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    in_addr.sin_port = htons(port);
    int ret = ::bind(svr_sock_.fd, (sockaddr*)&in_addr, sizeof(in_addr));
    if (ret < 0)
    {
        MYLOG(ERROR, "sockets(%u)::bind error:%d", svr_sock_.fd, errno);
        return ret;
    }

    ret = ::listen(svr_sock_.fd, 1024);
    if (ret < 0)
    {
        MYLOG(ERROR, "sockets(%u) listen error:%d", svr_sock_.fd, errno);
        return ret;
    }

    SetReuseAddr(svr_sock_.fd, true);
    SetTcpNoDelay(svr_sock_.fd, true);
    SetNonBlockAndCloseOnExec(svr_sock_.fd);
    ret = CoRoutineMgr::Instance().Init(1024);
    if (ret < 0)
    {
        MYLOG(ERROR, "co_routine_mgr count:%d init error", 1024);
        return ret;
    }

    MYLOG(INFO, "ip:%s port:%u type:%u init success", ip.c_str(), port, type);
    ret = CoRoutineMgr::Instance().CreateCoTask(&SvrLoop, this, svr_sock_.fd);
    EventManager::Instance().AddEvent(svr_sock_.fd, READ_EVENT, &CoRoutineMgr::Instance().GetCoTask(ret));
    return EC_OK;
}

void EventManager::Start() {
    CoRoutineMgr::Instance().Schedule(CoRoutineMgr::Instance().GetCoTask(LOOP_INDEX));
    MYLOG(INFO, "%s","start end");
}

int Loop(void* attr) {
    //MYLOG(INFO, "%s", "loop comes");
    for(;;) {
        uint64_t last_timeout = EventManager::Instance().GetLastTimeout();
        vector<Event> events;
        int32_t evnum = EventManager::Instance().Poll(events, last_timeout == 0 ? 500 : last_timeout);
        if (evnum <= 0)  {
            continue;
        }

        for (int i = 0; i < evnum; i++) {
            if (events[i].data != nullptr) {
                CoTask *task = (CoTask *)events[i].data;
                if (task->fd <= 0) {
                    continue;
                }
                
                if (task->id != CoRoutineMgr::Instance().GetCurrentCoIndex()) {
                    task->ev_mask = events[i].ev_mask;
                    CoRoutineMgr::Instance().Schedule(*task);
                    continue;
                }
            }

            //MYLOG(INFO, "new events comes:%d, events_size:%zu, fd:%d data:%p, data_item:%d", evnum, events.size(),events[i].fd, events[i].data, events[i].data_item);
            switch (events[i].ev_mask) {
                case READ_EVENT:
                    if ((CoTask *)events[i].data == NULL && events[i].fd != EventManager::Instance().SvrSocket().fd) {
                        MYLOG(ERROR, "events[%d] data == null", i);
                        break;
                    }

                    if (events[i].fd == EventManager::Instance().SvrSocket().fd) {
                        if (EventManager::Instance().CurClient() > kMaxConnectCount) {
                            EventManager::Instance().CloseTailConnect();
                        }
                        int conn_fd = AcceptFunc(EventManager::Instance().SvrSocket().fd);
                        uint32_t task_index = 0;
                        if (conn_fd > 0) {
                            task_index = CoRoutineMgr::Instance().CreateCoTask(&MyProcess, &CoRoutineMgr::Instance(), conn_fd);
                        } else {
                            continue;
                        }
                        EventManager::Instance().AddEvent(conn_fd, READ_EVENT, &CoRoutineMgr::Instance().GetCoTask(task_index));
                        MYLOG(INFO, "%d new connect, task:%u", conn_fd, task_index);
                        EventManager::Instance().CurClient()++;
                    }
                    break;
                case WRITE_EVENT:
                    break;
                case TIMEOUT_EVENT:
                    break;
                default:
                    //MYLOG(ERROR, "events[%d], ev_mask_err::%d", i, events[i].ev_mask);
                    break;
            }

        }
        EventManager::Instance().HandleTimeout();//释放长期未使用的链接
    }
    MYLOG(INFO, "%s", "loop end");
    return EC_OK;
}

int SvrLoop(void* attr) {
    return Loop(attr);
}

int EventManager::CloseTailConnect() {
    return EC_OK;
}

int EventManager::AddTask(int32_t fd, CoRoutineFunc func = nullptr, void* attr = nullptr) {
    uint32_t task_index = CoRoutineMgr::Instance().CreateCoTask(func, attr, fd);
    MYLOG(INFO, "fd:%u id%u add success", fd, task_index);
    return task_index;
}

int EventManager::Wait(CoTask& co_task, uint32_t ev_mask) {
    if (co_task.fd <= 0) {
        return EC_SYS_ERR;
    }

    poller_ptr_->AddEvent(co_task.fd, ev_mask, &co_task);
    CoRoutineMgr::Instance().YieldTask();
    poller_ptr_->DelEvent(co_task.fd, ev_mask);
    return EC_OK;
}

int EventManager::Read(CoTask& co_task, char* buf, int32_t& size, uint32_t timeout, CheckEOF checkfunc) {
    MYLOG(INFO, "%d read size:%u", co_task.id, size);
    int ret = ::read(co_task.fd, buf, size);
    uint64_t timeout_ts = cur_ts_ + timeout;
    int total_read = ret >= 0 ? ret : 0;
    while (checkfunc(buf,total_read) != 0) {
        if (unlikely(timeout_ts >= cur_ts_)) {
            errno = ETIMEDOUT;
            return EC_TIMEOUT;
        }

        Wait(co_task, READ_EVENT);
        if (co_task.ev_mask & READ_EVENT)
        {
            int ret = ::read(co_task.fd, buf, size);
            if (ret <= 0) {
                MYLOG(ERROR, "read err:%d errno:%d", ret, errno);
            }
            total_read += ret;
        }
    }
    size = ret;
    return EC_OK;
}

int EventManager::Write(CoTask& co_task, char* buf, int32_t size, uint32_t timeout) {
    int ret = ::write(co_task.fd, buf, size);
    uint64_t timeout_ts = cur_ts_ + timeout;
    int32_t total_send = ret >= 0 ? ret : 0;
    while (total_send >= size) {
        if (unlikely(timeout_ts >= cur_ts_)) {
            errno = ETIMEDOUT;
            return EC_TIMEOUT;
        }

        Wait(co_task, WRITE_EVENT); //等待有写事件
        if (co_task.ev_mask & WRITE_EVENT) {
            continue;
        }
        int ret = ::write(co_task.fd, buf, size);
        if (ret < 0)
        {
            if (errno == EINTR)
                continue;
            if (errno != EAGAIN && errno != EWOULDBLOCK)
            {
                MYLOG(ERROR, "read err:%d errno:%d", ret, errno);
            }
            total_send += ret;
        }
        total_send += ret;
    }
    return EC_OK;
}

int EventManager::Connect(CoTask& co_task, std::string& ip, int16_t port, uint32_t timeout) {
    int32_t conn_fd = -1;

    struct sockaddr_in in_addr;
    memset(&in_addr, 0, sizeof(in_addr));
    in_addr.sin_family = AF_INET;
    in_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    in_addr.sin_port = htons(port);
    auto addr_iter = socket_map_.find(HashAddress(in_addr.sin_addr.s_addr, port));
    if (addr_iter != socket_map_.end()) {
        for (auto iter = addr_iter->second.begin(); iter != addr_iter->second.end(); ++iter) {
            if (iter->fd > 0 && iter->cur_used_co == 0) {
                iter->cur_used_co = co_task.id;
                conn_fd = iter->fd;
                break;
            }
        }
    }
    if (conn_fd > 0) {
        return conn_fd;
    }

    int fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    SetNonBlockAndCloseOnExec(fd);
    SetTcpNoDelay(fd, true);
    co_task.fd = fd;

    uint64_t timeout_ts = cur_ts_ + timeout;
    int ret = ::connect(fd, (sockaddr*)&in_addr, sizeof(in_addr));
    while (ret != EC_OK) {
        if (unlikely(timeout_ts >= cur_ts_))
        {
            errno = ETIMEDOUT;
            return EC_TIMEOUT;
        }

        Wait(co_task, WRITE_EVENT);
        if (EC_OK < ret)
        {
            if (EINTR == ret) continue;
            if (EAGAIN != errno && EINPROGRESS != errno)
                return EC_SYS_ERR;

            if (co_task.ev_mask & WRITE_EVENT) {
                ret = ::connect(fd, (sockaddr*)&in_addr, sizeof(in_addr));
            }
        }
    }
    return EC_OK;
}

int EventManager::HandleTimeout() {
    // notify and close timeout;
    return EC_OK;
}