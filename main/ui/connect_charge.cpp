#include "connect_charge.h"
#include "ui_connect_charge.h"
//#include "equipment_testing.h"
#include "tcu_canbus/serialsystem.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "global.h"
#include "tcu.h"
#include "mysigals_slots.h"
#include "test_manual.h"
#include "file.h"
//#include "mythread.h"
#include <QTextCodec>
#include "message/message.h"

#define EMTER_1
#undef EMTER_1

#define MYTHREAD
//#undef  MYTHREAD

//mythread connect_charge::mythread_can;

connect_charge::connect_charge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connect_charge)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存


    connect(&can_timer,SIGNAL(timeout()),this,SLOT(slot_cantimer()));//版本校验下发参数
    can_timer.start(10);

    connect(&tcv_timer,SIGNAL(timeout()),this,SLOT(slot_timer()));//版本校验下发参数
    //tcv_timer.start(100);

    connect(&nextscreen_timer,SIGNAL(timeout()),this,SLOT(slot_nextscreen_timer()));
    nextscreen_timer.start(200);

    connect(ui->back_but,SIGNAL(clicked()),this,SLOT(slot_hide()));//BACK   

    Message::static_msg = new Message();

    //show();

#ifndef EMTER_1
    flag = 1;
    if(emter_timer.isActive()){
        //emter_timer.stop();//防止重新创建
    }else{
        log_printf(WRN,RED("EmterWindow"));
        p_emter = new EmterWindow;
        p_emter->ComInit();
        connect(&emter_timer,SIGNAL(timeout()),this,SLOT(slot_emtertimer()));//充电信息
        emter_timer.start(2000);
    }
     log_printf(WRN, "TCU: "RED("connect_charge connect_charge"));
#endif
}

void connect_charge::slot_emtertimer()
{
#ifndef EMTER_1
    if(flag == 1){
        p_emter->SendData("02010100");//A项电压 //0201FF00
        flag = 0;
    }else if(flag == 0){
        p_emter->SendData("02020100");//A项电流
        flag = 2;
    }else if(flag == 2){
        p_emter->SendData("00000000");//02030100Ａ相瞬时功率
        flag = 1;
    }
    p_emter->sendEmterMsg();
#endif
}

void connect_charge::slot_hide()
{   
    tcv_timer.stop();
#ifdef MYTHREAD
     mythread_can.stop();
#endif
#ifndef EMTER_1
     log_printf(WRN,RED("slot_hide slot_hide"));
     emter_timer.stop();
     p_emter->on_Close();
//     if(p_emter->myCom != NULL){
//         if(p_emter->myCom->isOpen()){
//             p_emter->myCom->close();
//         }
//         delete p_emter->myCom;
//     }
#endif
     task->tcu_wait_stage =TCU_STAGE_ANY;
     task->tcu_stage = TCU_STAGE_CHECKVER;
     task->tcu_tmp_stage = TCU_STAGE_CHECKVER;
     hide();
     test_Manual *w_test = new test_Manual;
     w_test->show();
    //equipment_testing *w_equ_testing = new equipment_testing;
    //w_equ_testing->show();      
}
void connect_charge::check_ver(QLineEdit* lbl)
{
    char ch[50];
    sprintf(ch,"%02x.%02x",
            task->tcv_info.spn_tcu_version[0],
            task->tcv_info.spn_tcu_version[1]);
    lbl->setText(ch);
    //TDDebug("tcv_info.spn_tcu_version=%02x.%02x ",task->tcv_info.spn_tcu_version[0],task->tcv_info.spn_tcu_version[1]);
    //timer.start();
}

void connect_charge::newTimeNoSec(QLabel* lbl)
{
    char ch[50],tmp[50];
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

    sprintf(tmp,"%02d-%02d-%02d  Week:%01d %02d:%02d:%02d:%ld",
             task->tts_info.spn1280_bcd_year,
             task->tts_info.spn1280_bcd_mon,
             (task->tts_info.spn1280_bcd_day) & 0x1f,
            ((task->tts_info.spn1280_bcd_day) & 0xe0)>>5,
             task->tts_info.spn1280_bcd_hour,
             task->tts_info.spn1280_bcd_min,
             ((task->tts_info.spn1280_bcd_sec_h)<<8 | (task->tts_info.spn1280_bcd_sec_l))/1000,
             ((task->tts_info.spn1280_bcd_sec_h)<<8 | (task->tts_info.spn1280_bcd_sec_l))%1000);
    //TDDebug("tts_info=%s",tmp);
    tcv_timer.start();
}

void connect_charge::slot_cantimer()
{
    can_timer.stop();    
#ifdef MYTHREAD
    mythread_can.start(); //tcu_canbus();
#endif
    tcv_timer.start(200);
}

void connect_charge::slot_timer()
{
    tcv_timer.stop();
   // mythread_can.start(); //tcu_canbus();
    check_ver(ui->tcu_version); //版本校验
    newTimeNoSec(ui->lblLocalTime); //下发参数    
}
void connect_charge::slot_nextscreen_timer()
{
#if 1
    if(task->tcu_err_stage == (TCU_ERR_STAGE_TIMEOUT | TCU_ERR_STAGE_CHECKVER))
    {
        myerr_sigals.SetValue(task->tcu_err_stage);
        ui->label_inf->setText("版本校验超时");
        //QMessageBox::critical(NULL, "Error", "版本校验超时");
        //nextscreen_timer.stop();//注释掉可重试进行下一步，否则定时器停止，无法跳转界面到 TCU_STAGE_CONNECT
    }
    if(task->tcu_err_stage == (TCU_ERR_STAGE_TIMEOUT | TCU_ERR_STAGE_PARAMETER))
    {
        myerr_sigals.SetValue(task->tcu_err_stage);
        ui->label_inf->setText("下发参数超时");
        //QMessageBox::critical(NULL, "Error", "下发参数超时");
        //nextscreen_timer.stop();
    }

    if(task->tcu_err_stage == TCU_ERR_STAGE_CHECKVER)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_CHECKVER);
        //QMessageBox::critical(NULL, "Error", "版本校验失败");
        ui->label_inf->setText("版本校验失败");
        //nextscreen_timer.stop();
    }

    if(task->tcu_err_stage == TCU_ERR_STAGE_PARAMETER)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_PARAMETER);
        //QMessageBox::critical(NULL, "Error", "充电参数不匹配");
        ui->label_inf->setText("充电参数不匹配");
        //nextscreen_timer.stop();
    }
#else
     myerr_sigals.SetValue(task->tcu_err_stage);

#endif
    if(task->tcu_stage == TCU_STAGE_CHECKVER)
    {
        ui->label_inf->setText("版本校验中．．．");
    }
    if(task->tcu_stage == TCU_STAGE_PARAMETER)
    {
        ui->label_inf->setText("下发参数中．．．");
    }    
    if(task->tcu_stage == TCU_STAGE_WAITCONNECT)
    {
        ui->label_inf->setText("等待连接．．．");
    }

    if(task->tcu_stage == TCU_STAGE_CONNECT || task->tcu_stage == TCU_STAGE_WAITSTART)
    {          
            //QMessageBox::about(NULL, "Connect", "电动汽车已连接");
            ui->label_inf->setText("电动汽车已连接");
            //emit display(1);
            my_sigals.SetValue(task->tcu_stage);
            nextscreen_timer.stop();       
    }
}


connect_charge::~connect_charge()
{
    delete ui;
}
