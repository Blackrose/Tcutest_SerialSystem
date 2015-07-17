#include "rtc.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
int Rtc::rtcTimeToSys()
{
	time_t t;
	struct tm p;
	struct timeval tv;
	//struct timezone tz;

	int fd = open("/dev/misc/rtc",O_RDWR);
	if(fd < 0)
	{
		printf("Open rtc device failed.\n");
		return fd;
	}
	printf("---rtc init ok---\n");
	//struct rtc_time rtc;

	::read( fd, &p, sizeof(struct tm));
	printf("---rtc init ok 1---\n");
	t = mktime(&p);
	printf("---rtc init ok 11---\n");
	tv.tv_sec = t;
	tv.tv_usec = 0;

	if( settimeofday( &tv, NULL) < 0 )
	{
		printf("shi jian xiu gai shi bai!");
	}
	printf("---rtc init ok 111---\n");
	close(fd);
	printf("ok !");
	return 1;
}
