#ifndef CONST_DEFINE_H
#define CONST_DEFINE_H
#include "inttypes.h"
enum RETURN_CODE {
    EC_OK = 0,
    EC_SYS_ERR = -1,
    EC_NOT_INIT = 1,
    EC_TIMEOUT = 2,
};

#define likely(x)  __builtin_expect(!!(x), 1)
#define unlikely(x)  __builtin_expect(!!(x), 0)

#define PAGE_SIZE 4096
#define PAGE_PACK_SIZE(size) (((size) + (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1))
const uint32_t kDefaultStackSize = 128 * 1024;
static const uint32_t kMaxConnectCount = 1024;
static const uint64_t kDefaultTimeout = 200;//200ms
static const uint32_t kMaxCoTask = 1024 * 1000;
static const uint32_t kDefaultTotalStackSize = 10 * 1024 * 1024;
typedef int (*CheckEOF) (char* buf, int32_t sizebb);
typedef int (*CoRoutineFunc) (void*);
#endif