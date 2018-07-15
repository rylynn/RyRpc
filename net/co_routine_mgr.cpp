#include "co_routine_mgr.h"
#include "../common/const_define.h"
#include "co_routine.h"
int MyProcess2(void* attr) {
    std::cout << "Process["<< (char*)attr << "]" << std::endl; 
    return EC_OK;
}
CoTask::~CoTask () {
    MYLOG(INFO, "id:%u Destructor", id);
   // delete co_routine;
}

void CoTask::Init() {
    co_routine->Init();
}

void CoTask::SetProcess(CoRoutineFunc func, void *attr)
{
    co_routine->SetFunc(func, attr);
}

void CoTask::SetPreProcess(CoRoutineFunc func, void *attr)
{
    co_routine->SetPreFunc(func, attr);
}

int CoTask::Run() {
    co_routine->Process();
    return CoRoutineMgr::Instance().RemoveRunTask(this->id);
}

int CoRoutineMgr::Init(uint32_t co_count, uint32_t stack_size, uint32_t share_stack_size) {
    MYLOG(INFO, "co_count:%u stack_size:%u share_stack_size:%u", co_count, stack_size, share_stack_size);
    max_co_count_ = co_count;
    if (share_stack_ == nullptr) {
        share_stack_ = (unsigned char*)malloc(PAGE_PACK_SIZE(share_stack_size_));
        memset(share_stack_, 0, share_stack_size_);
    }
    if (share_stack_ == nullptr) return EC_SYS_ERR;
    share_stack_cur_index_ = 0;
    cur_co_index_ = LOOP_INDEX;
    MYLOG(INFO, "co_count:%u stack_size:%u share_stack_size:%u Init Sucess", co_count, stack_size, share_stack_size);
    cur_co_index_ = CreateCoTask(&MyProcess2, nullptr, 0);
    co_task_vec_.reserve(co_count);
    is_init_ = true;
    return EC_OK;
}

int CoRoutineMgr::CreateCoTask(CoRoutineFunc func, void* attr, int32_t fd, uint32_t stack_size, bool shareStack, bool run_now) {
    MYLOG(INFO, "CREATE task fd:%d", fd);
    unsigned char *stack_ptr = nullptr;
    if (!shareStack && share_stack_cur_index_ + stack_size < share_stack_size_) {
        stack_ptr = share_stack_ + share_stack_cur_index_ + 1;
        memset(stack_ptr, 0, stack_size);
        share_stack_cur_index_ += stack_size;
    } else {
        stack_ptr = (unsigned char *)malloc(PAGE_PACK_SIZE(stack_size)); //按页对齐
        if (stack_ptr == nullptr) {
            return EC_SYS_ERR;
        }
    }
    CoTask co_task;
    co_task.fd = fd;
    co_task.id = co_task_vec_.size();
    co_task.co_routine = new CoRoutine();
    co_task.co_routine->SetFunc(func, attr);
    co_task.co_routine->SetStack(stack_ptr, stack_size);
    if (run_now) {
       ADD_RUN_TASK(run_co_task_mask_[GETINDEX(co_task.id)], free_co_task_mask_[0], co_task.id, co_task.id);
    } else {
       RM_RUN_TASK(run_co_task_mask_[GETINDEX(co_task.id)], free_co_task_mask_[0], co_task.id);
    }
    co_task.Init();
    co_task_vec_.push_back(co_task);
    MYLOG(INFO, "CREATE task fd:%d task_id:%u init success", fd, co_task.id);
    return co_task.id;
}

void CoRoutineMgr::SwitchRoutine(CoTask &src_ctx, CoTask &dst_ctx)
{
    src_ctx.co_routine->Yield(*dst_ctx.co_routine);
}

int CoRoutineMgr::YieldTask() {
    uint32_t next_run_index = GetNextEventIndex();
    if (co_task_vec_.size() <= next_run_index) {
        MYLOG(ERROR, "index:%u > co_task_size:%zu", next_run_index, co_task_vec_.size());
        return EC_SYS_ERR;
    }
    Resume(co_task_vec_[next_run_index]);
    return EC_OK;
}

uint32_t CoRoutineMgr::GetNextEventIndex() {
    for( uint32_t i = cur_co_index_ /32 + 1; i < kMaxCoTask/32;++i) {
        for (int j = 0; j < 32; ++j) {
            uint32_t index = 1 << j;
            if (FD_ISSET(index, &run_co_task_mask_[i]))
            {
                return i*32 + index;
            }
        }
    }
    return LOOP_INDEX;
}

void CoRoutineMgr::Schedule(CoTask &task) {
    MYLOG(INFO, "current_index:%u task_id:%u fd:%u schedule", cur_co_index_, task.id, task.fd);
    //task.co_routine->SaveCtx();
    Resume(task);
}

inline int CoRoutineMgr::Resume(uint32_t id) {
    if (id == cur_co_index_) {
        return EC_OK;
    }
    if (id >= co_task_vec_.size()) {
        MYLOG(ERROR, "index:%u > co_task_size:%zu", id, co_task_vec_.size());
        return EC_SYS_ERR;
    }
    MYLOG(INFO, "cur_co_id:%u resume_task_id:%u", cur_co_index_, id);
    ADD_RUN_TASK(run_co_task_mask_[GETINDEX(id)], free_co_task_mask_[0], id, cur_co_index_);
    uint32_t prev_index = cur_co_index_;
    cur_co_index_ = id;
    co_task_vec_[prev_index].co_routine->Yield(*co_task_vec_[cur_co_index_].co_routine);
    return EC_OK;
}

inline void CoRoutineMgr::Resume(CoTask &dst_ctx) {
    if (dst_ctx.id == cur_co_index_) {
        return;
    }
    ADD_RUN_TASK(run_co_task_mask_[GETINDEX(dst_ctx.id)], free_co_task_mask_[0], dst_ctx.id, cur_co_index_)
    if (cur_co_index_ == dst_ctx.id) {
        MYLOG(INFO, "resume cur_index:%u dst_ctx_id:%u fd:%u, co_size:%zu", cur_co_index_, dst_ctx.id, dst_ctx.fd, co_task_vec_.size());
        co_task_vec_[cur_co_index_].co_routine->YieldNotSave(*dst_ctx.co_routine);
        return;
    }
    uint32_t prev_index = cur_co_index_;
    //MYLOG(INFO, "resume cur_index:%u dst_ctx_id:%u fd:%u, co_size:%zu", cur_co_index_, dst_ctx.id, dst_ctx.fd, co_task_vec_.size());
    cur_co_index_ = dst_ctx.id;
    co_task_vec_[prev_index].co_routine->Yield(*dst_ctx.co_routine);
}