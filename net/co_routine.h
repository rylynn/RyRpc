#ifndef CO_ROUTINE_H
#define CO_ROUTINE_H
#include "const_define.h"
#include "log.h"
#include "setjmp.h"
#include "co_routine_mgr.h"
extern "C"  void restore_context(jmp_buf jbf, int ret);

extern "C"  void replace_esp(jmp_buf jbf, void* esp);

extern "C"  int save_context(jmp_buf jbf);

class CoRoutine {
public:
    CoRoutine(CoRoutineFunc fun = nullptr, void* attr = nullptr, uint32_t stack_size = kDefaultStackSize) :
    func_(fun),
    attr_(attr) {
        memset(context_, 0, sizeof(context_));
    };

    ~CoRoutine()
    {
        MYLOG(INFO,"%s",  "CoRoutine destructor");
    }

    void Init() {
        if (save_context(context_) != EC_OK) {
            MYLOG(INFO,  "%s", "CoRoutine save_context first run");
            while (true) {
                CoRoutineMgr::Instance().GetCoTask(CoRoutineMgr::Instance().GetCurrentCoIndex()).Run();
            }
        }

        if (stack_ptr_ != nullptr) {
            MYLOG(INFO,  "%s", "CoRoutine replace rsp success");
            //replace_esp(context_, stack_ptr_);
        }
        MYLOG(INFO,  "%s", "CoRoutine save_context Init success");
    }

    void SetStack(unsigned char* sp, uint32_t size) { 
        stack_ptr_ = sp; 
        stack_size_ = size;
    }

    inline void SaveCtx() {
        save_context(context_);
    }

    void Yield(CoRoutine& dst) {
        save_context(context_); 
        restore_context(dst.GetCtx(), 1);
    }

    void YieldNotSave(CoRoutine& dst) {
        restore_context(dst.GetCtx(), 1);
    }
    
    jmp_buf& GetCtx() { return context_;}
    void SaveStack(unsigned char* src, uint32_t size) {
        if (!share_stack_)
            return;
        memcpy(stack_ptr_, src, size > stack_size_ ? stack_size_ : size);
    }

    void SetFunc(CoRoutineFunc func, void* attr) {
        attr_ = attr;
        func_ = func;
    }

    void SetPreFunc(CoRoutineFunc func, void* attr) {
        pre_func_ = func;
        pre_attr_ = attr;
    }

    virtual int Process() {
        if (func_ == nullptr) {return EC_SYS_ERR;}
        return func_(attr_);
    }

    virtual int PrevProcess() {
        if (pre_func_ == nullptr) { return EC_SYS_ERR;}
        return pre_func_(pre_attr_);
    }
private:
    bool share_stack_;
    unsigned char* stack_ptr_; //私有栈
    uint16_t stack_size_; //栈大小,最大支持64k
    
    CoRoutineFunc pre_func_;
    void* pre_attr_;

    CoRoutineFunc func_;
    void* attr_;
    
    jmp_buf context_;//上下文
    
};
#endif