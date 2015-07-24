#include "power.h"
#include "led.h"

int Power::fd = -1;
int Power::ADCValue[2];
int Power::voltage[2];	
char Power::cmd[4];  /* 0:isMainPower  1:isPrePower  2:isChargeHigh  3:isPrePowerJ */
QTimer *Power::timer;
Power *Power::point;

int Power::init()
{
	Power::fd = open("/dev/adc", O_RDWR);
	if(Power::fd < 0)
	{
		printf("Open power device failed.\n");
		return Power::fd;
	}
	Power::timer = new QTimer();
	Power::point = new Power;
	Power::timer->start(TIME_MS);
	connect(Power::timer, SIGNAL(timeout()), Power::point, SLOT(hanlde()));
	Power::cmd[MAIN_POWER_0] = 1;
	Power::cmd[PRE_POWER_1] = 1;
	Power::cmd[CHARGE_HIGH_2] = 1;
	Power::cmd[PRE_POWERJ_3] = 2;
	printf("---power init ok---\n");
	return 1;
}

bool Power::isMainPower()//是否有主电
{
	if(Power::cmd[MAIN_POWER_0] == 0)
		return false;
	return true;
}
bool Power::isPrePower()//是否有备电
{
	if(Power::cmd[PRE_POWER_1] == 0)
		return false;
	return true;
}
bool Power::isChargeHigh()//是否充满电
{
	if(Power::cmd[CHARGE_HIGH_2] == 0)
		return false;
	return true;
}
char Power::isPrePowerJ()//备电电量是否还够用
{	
	return Power::cmd[PRE_POWERJ_3];
}
void Power::onRelay()//闭合继电器
{
	Led::onRelay();
}
void Power::offRelay()//断开继电器
{
	Led::offRelay();
}
void Power::hanlde()
{
	static int samples = 0;
	static int total[2] = {0, 0};
	float value = 0;
	samples++;

	read(fd, &Power::ADCValue, 2 * sizeof(int));

	Power::voltage[0] = 5 * 330 * Power::ADCValue[0] / 4096; //cell
	Power::voltage[1] = 5 * 330 * Power::ADCValue[1] / 4096; //power
    //total[0] += 1200;
    //total[1] += 1200;
    total[0] += Power::voltage[0];
    total[1] += Power::voltage[1];


    if(samples == SAMPLE_NUM){
        //printf("total[0]==%f  total[1]==%f\n",total[0],total[1]);
    }
	if (samples >= SAMPLE_NUM) {
		samples = 0;
		total[0] = total[0] / SAMPLE_NUM;
		value = (float)total[0] / 100; //cell

        //printf("cell voltage is %f\n", value);
		/* check back-up power break or short */
		if ((value <= PREPOWER_BREAK_VOLTAGE) && (value >= PREPOWER_SHORT_VOLTAGE))
			Power::cmd[PRE_POWERJ_3] = 0;
		else if (value < PREPOWER_SHORT_VOLTAGE)
			Power::cmd[PRE_POWERJ_3] = 1;
		else
			Power::cmd[PRE_POWERJ_3] = 2;
		
		/* check back-up power undervoltage */
		if (Power::cmd[PRE_POWER_1] == 0)
			if (value >= PREPOWER_LOW_VOLTAGE + PREPOWER_SCHMIDT)
				Power::cmd[PRE_POWER_1] = 1;
			else 
				Power::cmd[PRE_POWER_1] = 0;
		else
			if (value <= PREPOWER_LOW_VOLTAGE - PREPOWER_SCHMIDT)
				Power::cmd[PRE_POWER_1] = 0;
			else 
				Power::cmd[PRE_POWER_1] = 1;
			
		/* check back-up power charge full */
		if (Power::cmd[CHARGE_HIGH_2] == 0)
			if (value >= PREPOWER_FULL_VOLTAGE + POWER_SCHMIDT)
                Power::cmd[CHARGE_HIGH_2] = 1;//充满电
			else 
                Power::cmd[CHARGE_HIGH_2] = 0;//
		else
			if (value <= PREPOWER_FULL_VOLTAGE - POWER_SCHMIDT)
                                Power::cmd[CHARGE_HIGH_2] = 0;
                        else
                                Power::cmd[CHARGE_HIGH_2] = 1;

		total[1] = total[1] / SAMPLE_NUM;
		value = (float)total[1] / 100; //power
        //printf("power voltage is %f\n", value);
		/* check main power undervoltage */
		if (value >= POWER_LOW_VOLTAGE)
			Power::cmd[MAIN_POWER_0] = 1;
		else
			Power::cmd[MAIN_POWER_0] = 0;
		
		total[0] = 0;
		total[1] = 0;
	}
}

