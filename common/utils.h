#ifndef UTILS_H
#define UTILS_H
#include <sys/time.h>
#include <errno.h>
#include <functional>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "log.h"

class Ticker {
public:
	Ticker():fp_(nullptr), cpu_hz_(0) {};
	~Ticker() {
		if (!fp_) {
			fclose(fp_);
		}
	}

#if defined( __RDTSCP__) 
static unsigned long long counter(void)
{
	register uint32_t lo, hi;
	register unsigned long long o;
	__asm__ __volatile__ (
			"rdtscp" : "=a"(lo), "=d"(hi)
			);
	o = hi;
	o <<= 32;
	return (o | lo);
}

static unsigned long long getCpuKhz()
{
	if (!fp_)
		fp_ = fopen("/proc/cpuinfo","r");
	if(!fp_) return 1;
	char buf[4096] = {0};
	fread(buf,1,sizeof(buf),fp_);

	char *lp = strstr(buf,"cpu MHz");
	if(!lp) return 1;
	lp += strlen("cpu MHz");
	while(*lp == ' ' || *lp == '\t' || *lp == ':')
	{
		++lp;
	}

	double mhz = atof(lp);
	unsigned long long u = (unsigned long long)(mhz * 1000);
	cpu_hz_ = u;
	return u;
}
#endif

	unsigned long long GetTickMS()
	{
#if defined(__RDTSCP__)
		if (cpu_hz_ == 0) {
			getCpuKhz();
		}
		return counter() / cpu_hz_;
#else
		timeval now;
		gettimeofday(&now, NULL);
		unsigned long long u = now.tv_sec;
		u *= 1000;
		u += now.tv_usec / 1000;
		return u;
#endif
	}

  private:
	FILE* fp_;
	uint64_t cpu_hz_;
};

static uint32_t HashAddress(uint32_t ip, uint16_t port) {
	//return std::hash<std::string>(std::to_string(ip) + std::to_string(port));
	return 0;
}
#endif