#include "poller.h"
#include "log.h"
#include "errno.h"
int KqueuePoller::Poll(vector<Event>& events, uint64_t time_out /*ms*/) {
    if (fd_ < 0 || events_ == nullptr)
        return EC_NOT_INIT;

    int retval = 0;
    time_out = time_out == 0 ? kDefaultPollTimeout : time_out;
    struct timespec timeout;
    timeout.tv_sec = time_out / 1000;
    timeout.tv_nsec = time_out;
    retval = kevent(fd_, NULL, 0, events_, event_size_, &timeout);
    if (retval > 0) {
        for(int j = 0; j < retval; j++) {
            Event ev;
            struct kevent *e = events_+j;
            ev.fd = e->ident;
            ev.data = e->udata;
            ev.data_item = e->data;
            if (e->filter == EVFILT_READ) ev.ev_mask |= READ_EVENT;
            if (e->filter == EVFILT_WRITE) ev.ev_mask |= WRITE_EVENT;
            events.push_back(ev);
        }
    }
    return retval;
}