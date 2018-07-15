#ifndef LOG_H
#define LOG_H
#include <iostream>
#include "glog/logging.h"

static const uint32_t kMaxLogSize = 100;//100M
static const uint32_t kLogBufSec = 1;//

#define MYLOG(level, fmt, ...) \
    {\
    char log_buf[1024] = {0}; \
    sprintf(log_buf, "[%s][%s:%d] "#fmt, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__); \
    std::cout << log_buf << std::endl;\
    std::cout.flush();\
    }

    //LOG(level) << log_buf; 
#endif