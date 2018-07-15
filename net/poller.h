#ifndef POLLER_H
#define POLLER_H

#include "stdlib.h"
#include "event.h"
#include "log.h"
#include "../common/const_define.h"
    #ifdef HAVE_EPOLL
    #include <sys/epoll.h>
    #else
    #include <sys/types.h>
    #include <sys/event.h>
    #include <sys/time.h>
    #endif 

#include <vector>
using std::vector;
static const uint32_t kDefaultPollTimeout = 10; //ms
static const uint32_t kDefaultPollEventSize = 1024 * 10; //poll event size

class Poller {
public:
    Poller(){};
    virtual ~Poller(){};
    virtual int Init(){return EC_OK;}
    virtual int AddEvent(int fd, int ev_mask, void*){return EC_OK;}
    virtual int DelEvent(int fd, int ev_mask){return EC_OK;}
    virtual int Poll(vector<Event>& events, uint64_t time_out) = 0;
};

class KqueuePoller : public Poller {
public:
    KqueuePoller(uint32_t event_size = kDefaultPollEventSize) : fd_(-1), event_size_(event_size),
    events_(NULL) {};
    virtual int Init() {
        #ifdef HAVE_EPOLL       
            fd_ = epoll_create(event_size_);
        #else
            fd_ = kqueue();
        #endif
        if (fd_ > 0)
            events_ = (struct kevent*)malloc(sizeof(struct kevent)*event_size_);
        else
            return EC_SYS_ERR;
        MYLOG(INFO, "poller fd:%d, size_:%u", fd_, event_size_);
        return EC_OK;
    }

    int AddEvent(int fd, int ev_mask, void* data = NULL) {
        #ifdef HAVE_KQUEUE
        struct kevent ke;
        ke.ident = fd;
        MYLOG(INFO, "add event fd:%d ev_mask:%d data:%p", fd, ev_mask, data);
        int flags = ev_mask & READ_EVENT ? EVFILT_READ : 0;
        EV_SET(&ke, fd, flags, EV_ADD, 0, 0, data);
        if (kevent(fd_, &ke, 1, NULL, 0, NULL) == -1)
            return EC_SYS_ERR;
        #endif
        return EC_OK;
    }

    int DelEvent(int fd, int ev_mask) {
        #ifdef HAVE_KQUEUE
        struct kevent ke;
        int flags = ev_mask & READ_EVENT ? EVFILT_READ : EVFILT_WRITE;
        EV_SET(&ke, fd, flags, EV_DELETE, 0, 0, NULL);
        if (kevent(fd_, &ke, 1, NULL, 0, NULL) == -1) return EC_SYS_ERR;
        #endif
        return EC_OK;
    }

    virtual int Poll(vector<Event>& events, uint64_t time_out = kDefaultPollTimeout);
private:
    int32_t fd_;
    uint32_t event_size_;
    #ifdef HAVE_EPOLL
    struct epoll_event *events_;
    #else
	struct kevent *events_;
	#endif
};
#endif