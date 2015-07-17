#ifndef LINLONG_WatcDog
#define LINLONG_WatcDog

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>  
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

class Watchdog
{
public:
	static int fd;
	static int init(); //初始化
	/*   
		给看门狗进食
	*/
	static void kellLive();
};
#endif
