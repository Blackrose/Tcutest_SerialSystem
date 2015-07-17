/*=============================
	系统检测界面
=============================*/

#include "check.h"
#include "main.h"
#include <QWidget>
#include <QCloseEvent>

//extern int whoChePwd;
Check::Check(QWidget *parent): QWidget(parent),Ui_CheckForm()
{
	setupUi(this);
	par=parent;
        setWindowFlags(Qt::Dialog
			| Qt::WindowCloseButtonHint);//窗口没有没有边框  是 一个模太对话框
	connect(btn_close,SIGNAL(clicked()),this,SLOT(hide()));
	connect(btn_check,SIGNAL(clicked()),this,SLOT(ch()));    
    connect(&timer,SIGNAL(timeout()),this,SLOT(slot_timer()));//显示系统时间
	setAttribute(Qt::WA_DeleteOnClose);
	printf("init Check ok\n");
}
void Check::closeEvent ( QCloseEvent * event )
{
	event->ignore(); 
	hide();
}
Check::~Check()
{
	printf("exit Check\n");
}
void Check::_show()
{	
	show();
	start();
	setGeometry(185, 145, 290, 190);
}
void Check::ch()
{
    hide();
	Main::whoChePwd=6;
    ((Main*)par)->check_pwd();
    //((Main*)par)->LCDmain();
}
//开始检测
void Check::start()
{
	int i, j;
    timer.stop();
	Main::com_led=0;
	Bell::off();
	Led::mainLightOff();
	Led::preMainLightOff();
	Led::commLightOff();
	Led::modErrorLightOff();
	Led::warnLightOff(); 
    usleep(1500000);//1.5s
    //Led::LCDLightOff();
    timer.start(1000);
    count = 1;
//	printf("check: after off before delay1!\n");
//	for(i=0;i<500;i++)
//        {
//                for(j=0;j<10000;j++)
//                {
//                        ;
//                }
//		if (i == 499)
//			printf("delay 1 delay 1 delay1!\n");
//        }
//	printf("check: after delay1!\n");
    b();

//	printf("check: after on before delay2!\n");
//	for(i=0;i<500;i++)
//	{
//		for(j=0;j<10000;j++)
//		{
//			;
//		}
//		if (i == 499)
//			printf("delay 2 delay 2 delay2!\n");
//	}
//	printf("check: after delay2!\n");
	a();	
	printf("check: end!\n");
}
/*void Check::slot_timer()
{
	//switch(count)
	//{
	//	case 1:
			//timer.stop();
			//Main::com_led=0;
			//Bell::on();
			Led::mainLightOn();
			Led::preMainLightOn();
			Led::commLightOn();
			Led::modErrorLightOn();
			Led::warnLightOn();
			timer.start(1000);
			//timer.stop();
	//		count = 2;
	//		break;
	//	case 2:
	//		Main::com_led=1;
	//		Bell::off();
	//		Led::mainLightOff();
	//		Led::preMainLightOff();
	//		Led::commLightOff();
	//		Led::modErrorLightOff();
	//		Led::warnLightOff();
	//		Led::LCDLightOn();
	//		timer.stop();
	//		break;
//	}
}*/
void Check::b()
{
			//timer.stop();
			Bell::on();
			Led::mainLightOn();
			Led::preMainLightOn();
			Led::commLightOn();
			Led::modErrorLightOn();
			Led::warnLightOn();
			//timer.start(1000);
            //Led::CtlOn();
            usleep(1500000);//1.5s
}
void Check::a()
{
	//timer.stop();
	Main::com_led=1;
			Bell::off();
			Led::mainLightOff();
			Led::preMainLightOff();
			Led::commLightOff();
			Led::modErrorLightOff();
			Led::warnLightOff();
			Led::LCDLightOn();
			//timer.stop();
            //Led::CtlOff();
            usleep(1000000);//1.0s

}

void Check::slot_timer()
{
    switch(count)
    {
    case 1:
        timer.start(1000);
        ((Main*)par)->LCDmain();
        count = 2;
        break;
    case 2:
        ((Main*)par)->LCDmain();
        count = 3;
        break;
    case 3:
        ((Main*)par)->LCDmain();
        count = 4;
        break;
    case 4:
        ((Main*)par)->LCDmain();
        count = 5;
        break;
    case 5:
        ((Main*)par)->LCDmain();
        count = 6;
        break;
    case 6:
        ((Main*)par)->LCDmain();
        //count = 2;
        timer.stop();
        break;
    }
}
