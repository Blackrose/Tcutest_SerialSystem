#ifndef MHW_LED
#define MHW_LED

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>  
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h> 
class Led
{
public:
	static int fd;
	static int fd1;
	static char status[7];
	static int init(); //初始化
	/*========================================
	number:  0    1    2    3   4    5
		主电   备电    通讯    预警  报警    液晶
	flag: 0: 是     是       是       是      是      不
	      1: 不     不      不       不      不      是	
	=========================================*/
	static void write(char number,char flag);
	
	static void mainLightOn();//主电源灯
	static void mainLightOff();//主灯灭
	static bool mainLightStats();

	static void preMainLightOn();//备电源灯
	static void preMainLightOff();//备灯灭
	static bool preMainLightStats();

	static void commLightOn();//通讯电源灯
	static void commLightOff();//通讯灯灭
	static bool commLightStats();

	static void modErrorLightOn();//模块通讯故障源灯
	static void modErrorLightOff();//模块通讯故障灯灭
	static bool modErrorLightStats();

	static void warnLightOn();//报警源灯
	static void warnLightOff();//报警主灯灭
	static bool warnLightStats();

	static void LCDLightOn();//液晶源灯
	static void LCDLightOff();//液晶灯灭
	static bool LCDStats();//是否亮


	static void CtlOn();//控制输出有效
	static void CtlOff();//控制输出无效
	
	static void onRelay();
	static void offRelay();
};
#endif

