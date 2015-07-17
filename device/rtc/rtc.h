#ifndef LINLONG_RTC
#define LINLONG_RTC

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>  
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*struct rtc_time
{
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};*/

class Rtc
{
public:
	static int rtcTimeToSys(); //初始化
};
#endif
