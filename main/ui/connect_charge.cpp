#include "connect_charge.h"
#include "ui_connect_charge.h"
#include "equipment_testing.h"
#include "tcu_canbus/serialsystem.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "global.h"
#include "tcu.h"
#include "mysigals_slots.h"

connect_charge::connect_charge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connect_charge)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存
    connect(&timer,SIGNAL(timeout()),this,SLOT(slot_timer()));//显示系统时间
    timer.start(1000);

     flag = 0;
    //connect(&timer1,SIGNAL(timeout()),this,SLOT(slot_timer1()));//显示系统时间
    timer1.start(100);

    connect(ui->back_but,SIGNAL(clicked()),this,SLOT(slot_hide()));//BACK   
}

void connect_charge::slot_hide()
{
    hide();
}
void connect_charge::check_ver(QLineEdit* lbl)
{
    char ch[50];
    sprintf(ch,"%02x.%02x",
            task->tcv_info.spn_tcu_version[0],
            task->tcv_info.spn_tcu_version[1]);
    lbl->setText(ch);
    //timer.start();
}

void connect_charge::newTimeNoSec(QLabel* lbl)
{
    char ch[50];
    struct tm *p;
    struct timeval    tv;

    gettimeofday(&tv, NULL);
    p = localtime(&tv.tv_sec);
    //printf("time_now:%4d年%02d月%02d日 星期%d %02d:%02d:%02d.%ld\n", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, ( (p->tm_wday==0)  ? 7 : (p->tm_wday) ),p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec);

   sprintf(ch,"%02d-%02d-%02d  星期:%01d %02d:%02d:%02d:%ld",
            task->tts_info.spn1280_bcd_year,
            task->tts_info.spn1280_bcd_mon,
            (task->tts_info.spn1280_bcd_day) & 0x1f,
           ((task->tts_info.spn1280_bcd_day) & 0xe0)>>5,
            task->tts_info.spn1280_bcd_hour,
            task->tts_info.spn1280_bcd_min,
            ((task->tts_info.spn1280_bcd_sec_h)<<8 | (task->tts_info.spn1280_bcd_sec_l))/1000,
            ((task->tts_info.spn1280_bcd_sec_h)<<8 | (task->tts_info.spn1280_bcd_sec_l))%1000);

   //sprintf(ch,"%04d-%02d-%02d %02d:%02d:%02d:%ld", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min,p->tm_sec,tv.tv_usec/1000);
    lbl->setText(ch);
    timer.start();
}

void connect_charge::slot_timer()
{
    timer.stop();
    mythread_can.start(); //tcu_canbus();
    check_ver(ui->tcu_version); //版本校验
    newTimeNoSec(ui->lblLocalTime); //下发参数
    my_sigals.SetValue(3);

    //equipment_testing *w_equ_testing = new equipment_testing;
    //w_equ_testing->show();
}
void connect_charge::slot_timer1()
{   
//    my_sigals.SetValue(3);
    if(task->tcu_stage == TCU_STAGE_CONNECT)
    {
//        equipment_testing *w_equ_testing = new equipment_testing;
//        w_equ_testing->show();
        if(!flag)
        {
            printf("now enter\n");
            my_sigals.SetValue(3);
            flag = 1;
            timer1.stop();
        }
    }
}


connect_charge::~connect_charge()
{
    delete ui;
}
