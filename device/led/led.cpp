#include "led.h"

int Led::fd = -1;
int Led::fd1 = -1;
char Led::status[7];

int Led::init()
{
	int i;

//    Led::fd1 = open("/dev/relay", O_RDWR);
//    //Led::fd1 = open("/dev/irda", O_RDWR);
//	if (Led::fd1 < 0)
//	{
//		printf("Open relay device failed.\n");
//		return Led::fd1;
//	}
//    printf("Open relay device success.\n");
	Led::fd = open("/dev/leds", O_RDWR);
	if (Led::fd < 0)
	{
		printf("Open led device failed.\n");
		return Led::fd;
	}
	for (i = 0; i < 5; i++) {
		::ioctl(Led::fd, 0, i);
		Led::status[i] = 0;
	}
	Led::status[6] = 1;
	printf("---led init ok---\n");
	return 1;
}

int Led::relayinit()
{
    int i;

    Led::fd1 = open("/dev/relay", O_RDWR);
    //Led::fd1 = open("/dev/irda", O_RDWR);
    if (Led::fd1 < 0)
    {
        printf("Open relay device failed.\n");
        return Led::fd1;
    }
    printf("Open relay device success.\n");
    printf("---relay init ok---\n");
    return 1;
}


/*========================================
number:  0    1    2    3   4    5
	主电   备电    通讯    预警  报警    液晶
flag: 0: 是     是       是       是      是      不
      1: 不     不      不       不      不      是	
=========================================*/
void Led::write(char number, char flag)
{
	int num;
	int cmd;
	
	if ((number > 6) || (Led::fd < 0)) {
		printf("led write failed.\n");
		return;
	}
	num = number;
        if (flag >= 1)
        	cmd = 0;
        else
        	cmd = 1;
	if ((number < 5) && (number >= 0))
		num = 4 - number;    
	::ioctl(Led::fd, cmd, num);
	if (num < 5)
		Led::status[num] = cmd;
	else
		Led::status[num] = 1 - cmd;
}
void Led::mainLightOn()//主电源灯
{
	Led::write(0, 0);
}
void Led::mainLightOff()//主电源灯灭
{
	Led::write(0, 1);
}
bool Led::mainLightStats()
{
	if (Led::status[0] > 0)
		return true;
	return false;
}
void Led::preMainLightOn()//备电源灯
{
	Led::write(1, 0);
}
void Led::preMainLightOff()//备灯灭
{
	Led::write(1, 1);
}
bool Led::preMainLightStats()
{
	if (Led::status[1] > 0)
		return true;
	return false;
}
void Led::commLightOn()//通讯电源灯
{
	Led::write(2, 0);
}
void Led::commLightOff()//通讯灯灭
{
	Led::write(2, 1);
}
bool Led::commLightStats()
{
	if (Led::status[2] > 0)
		return true;
	return false;
}
void Led::modErrorLightOn()//模块故障灯
{
	Led::write(3, 0);
}
void Led::modErrorLightOff()//模块故障灯灭
{
	Led::write(3, 1);
}
bool Led::modErrorLightStats()//模块故障
{
	if (Led::status[3] > 0)
		return true;
	return false;
}
void Led::warnLightOn()//报警源灯
{
	Led::write(4, 0);
}

void Led::warnLightOff()//报警主灯灭
{
	Led::write(4, 1);
}
bool Led::warnLightStats()
{
	if (Led::status[4] > 0)
		return true;
	return false;
}
void Led::LCDLightOn()//液晶源灯
{
	Led::write(6, 1);
}
void Led::LCDLightOff()//液晶灯灭
{
	Led::write(6, 0);
}
bool Led::LCDStats()//是否亮
{
	if (Led::status[6] > 0)
                return true;
        return false;
}

void Led::CtlOn()//控制输出有效
{
    char on = 1;
    if (Led::fd1 > 0)
        ::write(Led::fd1, &on, 1);
    printf("CtlOn  \n");
}
void Led::CtlOff()//控制输出无效
{
    char off = 0;
    if (Led::fd1 > 0)
        ::write(fd1, &off, 0);
    printf("CtlOff\n");
}

void Led::onRelay()
{
	Led::write(5, 1);
}

void Led::offRelay()
{
        Led::write(5, 0);
}

