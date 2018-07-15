#ifndef EVENT_H
#define EVENT_H

#define READ_EVENT 1
#define WRITE_EVENT 2
#define TIMEOUT_EVENT 4

class Event {
public:
    int fd;
    int ev_mask;
    void* data;
    int32_t data_item;
};
#endif