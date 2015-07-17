#include "watchdog.h"

int Watchdog::fd = 0;
int Watchdog::init()
{
	Watchdog::fd = open("/dev/watchdog",O_RDWR);
	if(fd < 0)
	{
		printf("Open device failed.\n");
		return fd;
	}
	printf("---Watchdog init ok---\n");
	return 1;
}
void Watchdog::kellLive()
{
//	unsigned char food = 0;

//        ::write(Watchdog::fd, &food, 1);
}
