#ifndef MHW_POWER
#define MHW_POWER

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>  
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <QTimer>
#include <QObject>

#define SAMPLE_NUM 100
#define TIME_MS 20
#define POWER_LOW_VOLTAGE       5.0  //need test
#define POWER_SCHMIDT           0.3
#define PREPOWER_LOW_VOLTAGE    9.0  //need test
#define PREPOWER_SCHMIDT        0.5
#define PREPOWER_FULL_VOLTAGE   12.2//11.8
#define PREPOWER_BREAK_VOLTAGE  3.75 //need test
#define PREPOWER_SHORT_VOLTAGE  0.3 //need test
typedef enum {
	MAIN_POWER_0 = 0,
	PRE_POWER_1 = 1,
	CHARGE_HIGH_2 = 2,
	PRE_POWERJ_3 = 3
} CHECK_FLAG;

class Power : public QObject
{
	Q_OBJECT

public:
	static int fd;
        static int ADCValue[2];
        static int voltage[2];
        static char cmd[4];  /* 0:isMainPower  1:isPrePower  2:isChargeHigh  3:isPrePowerJ */
        static QTimer *timer;
        static Power *point;

	static int init(); //初始化
	static bool isMainPower();//是否有主电
	static bool isPrePower();//是否备电欠压
	static bool isChargeHigh();//是否充满电
	static char isPrePowerJ();//复合测试
	static void onRelay();//闭合继电器
	static void offRelay();//断开继电器
private slots:
	static void hanlde(void);
};
#endif

