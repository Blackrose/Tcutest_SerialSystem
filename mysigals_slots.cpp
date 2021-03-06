#include "mysigals_slots.h"
#include "stdio.h"
#include "tcu.h"
#include "equipment_testing.h"
#include "charging_monitoring.h"
#include "bat_information.h"
#include "settlement_inf.h"
#include <QLabel>
#include <QMessageBox>
#include "message/message.h"
#include "first_interface.h"
#include "double_gun.h"

equipment_testing *w_equ_testing;
Charging_monitoring *w_change_moni;
bat_information *w_bat_information;
settlement_inf *w_settlement_inf;
First_interface *w_first;
double_gun *w_double_gun;

mysigals_slots::mysigals_slots(QWidget *parent) : QWidget(parent)
{   
    //connect(this,SIGNAL(ValueChanged(int)),this,SLOT(ChangeValue(int)));

    connect(this,SIGNAL(ValueChanged(int)),this,SLOT(ChangeNewValue(int)));
    //QMessageBox::setGeometry(350,150,150,100);
}

void mysigals_slots::SetValue(int value)
{
    if(value!=oldvalue)
    {
        oldvalue=value;
        //value_tmp =value;
        emit ValueChanged(value);
    }//注意这里的if判断,这是避免递归的方式!如果没有if,当出现了循环连接的时候就会产生无限递归
}

void mysigals_slots::ChangeValue(int value)
{
    //FunctionForChangingTheValue(value);
    printf("now ChangeValue\n");
    //equipment_testing *w_equ_testing = new equipment_testing;
    //Charging_monitoring *w_change_moni = new Charging_monitoring;
    QMessageBox *msg = new QMessageBox();
    switch(value)
    {
        case TCU_STAGE_INVALID:
            break;
        case TCU_STAGE_CHECKVER:
            break;
        case TCU_STAGE_PARAMETER:
            break;
        case TCU_STAGE_CONNECT:
        case TCU_STAGE_WAITSTART:
            //QMessageBox::about(NULL, "Connect", "电动汽车已连接");
            w_first = new First_interface;
            w_first->show();
//            w_equ_testing = new equipment_testing;
//            w_equ_testing->show();
             Message::_show(tr("电动汽车已连接"));
             Message::static_msg->setWindowTitle("Connect");
            //w_bat_information = new bat_information;
            //w_bat_information->show();
            break;
        case TCU_STAGE_START:
            //QMessageBox::about(NULL, "Start", "电动汽车启动充电");
            w_change_moni = new Charging_monitoring;
            w_change_moni->show();
            Message::static_msg->setWindowTitle("Start");
            Message::_show(tr("电动汽车启动充电"));
            task->tcu_stage = TCU_STAGE_START;
            task->tcu_tmp_stage = TCU_STAGE_START;           
            break;
        case TCU_STAGE_STARTING:
            Message::static_msg->hide();
            break;
        case TCU_STAGE_STATUS:
            //gettimeofday(&Charging_Time.start,NULL);
            break;
        case TCU_STAGE_STOP:
            //QMessageBox::about(NULL, "Stop", "停止充电");
            w_settlement_inf = new settlement_inf;
            w_settlement_inf->show();
            Message::static_msg->setWindowTitle("Stop");
            Message::_show(tr("电动汽车停止充电"));
            task->tcu_stage = TCU_STAGE_STOP;
            task->tcu_tmp_stage = TCU_STAGE_STOP;
            break;
        case TCU_STAGE_STOP_STATUS:
            Message::static_msg->hide();
            break;
        case TCU_STAGE_STOP_END:
            w_settlement_inf = new settlement_inf;
            w_settlement_inf->show();
            Message::static_msg->setWindowTitle("Stop");
            Message::_show(tr("电动汽车停止充电"));
            task->tcu_stage = TCU_STAGE_STOP_END;
            task->tcu_tmp_stage = TCU_STAGE_STOP_END;
            break;
        case TCU_STAGE_HEAT:
            break;
        case TCU_STAGE_TIME:
            break;
        case TCU_STAGE_ANY:
            break;


    }

#if 0
    if(value == 1){
        task->tcu_stage = TCU_STAGE_CHECKVER;
        task->tcu_tmp_stage = TCU_STAGE_CHECKVER;
        task->tcu_heartbeat_stage  = TCU_STAGE_HEAT;//心跳
        task->tcu_time_stage  = TCU_STAGE_TIME;//对时
    }else if(value == 2){
        task->tcu_stage = TCU_STAGE_PARAMETER;
        task->tcu_tmp_stage = TCU_STAGE_PARAMETER;
    }else if(value == 3){
        task->tcu_wait_stage =TCU_STAGE_INVALID;
        task->tcu_stage = TCU_STAGE_CONNECT;//TCU_STAGE_CONNECT;
        task->tcu_tmp_stage = TCU_STAGE_CONNECT;//TCU_STAGE_CONNECT;
    }else	if (value == 4){
        task->tcu_stage = TCU_STAGE_START;
        task->tcu_tmp_stage = TCU_STAGE_START;
        task->tcu_heartbeat_stage  = TCU_STAGE_HEAT;//心跳
        task->tcu_time_stage  = TCU_STAGE_TIME;//对时
    }else if(value == 6){
        task->tcu_stage = TCU_STAGE_STOP;
        task->tcu_tmp_stage = TCU_STAGE_STOP;
    }else if(value ==8){
        task->tcu_heartbeat_stage  = TCU_STAGE_HEAT;//心跳
        task->tcu_stage = TCU_STAGE_HEAT;
        //task->tcu_tmp_stage = TCU_STAGE_HEAT;
    }else if(value == 9){
        task->tcu_time_stage  = TCU_STAGE_TIME;//对时
        task->tcu_stage = TCU_STAGE_TIME;
        //task->tcu_tmp_stage = TCU_STAGE_TIME;
    }else{
        task->tcu_stage = TCU_STAGE_ANY;
        task->tcu_tmp_stage = TCU_STAGE_ANY;
        printf("Please input tcu_stage\n  1版本校验\n  2下发参数\n  3连接确认\n  4启动充电\n  6停止充电\n  8心跳开始\n  ９对时开始\n");
        printf("Sorry! input error\n\n");
    }

#endif
}

void mysigals_slots::ChangeNewValue(int value)
{
    printf("now ChangeNewValue\n");
    //QMessageBox *msg = new QMessageBox();

    QString gun;
    gun += task->gun_sn;

    switch(value)
    {
        case TCU_STAGE_INVALID:
            break;
        case TCU_STAGE_CHECKVER:
            break;
        case TCU_STAGE_PARAMETER:
            break;
        case TCU_STAGE_CONNECT:
        case TCU_STAGE_WAITSTART:
            //QMessageBox::about(NULL, "Connect", "电动汽车已连接");
            w_first = new First_interface;
            w_first->show();
            gun += " #枪Connect";
//            Message::_show(tr("电动汽车已连接"));
//            Message::static_msg->setWindowTitle(gun);
            break;
        case TCU_STAGE_START:
            //QMessageBox::about(NULL, "Start", "电动汽车启动充电");
//            w_change_moni = new Charging_monitoring;
//            w_change_moni->show();
            w_double_gun = new double_gun;
            w_double_gun->show();
            gun += " #枪Start";
//            Message::static_msg->setWindowTitle(gun);
//            Message::_show(tr("电动汽车启动充电"));
            task->tcu_stage = TCU_STAGE_START;
            task->tcu_tmp_stage = TCU_STAGE_START;
            break;
        case TCU_STAGE_STARTING:
            Message::static_msg->hide();
            break;
        case TCU_STAGE_STATUS:
            //gettimeofday(&Charging_Time.start,NULL);
            break;
        case TCU_STAGE_STOP:
            //QMessageBox::about(NULL, "Stop", "停止充电");
            w_settlement_inf = new settlement_inf;
            w_settlement_inf->show();
             gun += " #枪Stop";
//            Message::static_msg->setWindowTitle(gun);
//            Message::_show(tr("电动汽车停止充电"));
//             Message::_show(gun);
            task->tcu_stage = TCU_STAGE_STOP;
            task->tcu_tmp_stage = TCU_STAGE_STOP;
            break;
        case TCU_STAGE_STOP_STATUS:
            Message::static_msg->hide();
            break;
        case TCU_STAGE_STOP_END:
            w_settlement_inf = new settlement_inf;
            w_settlement_inf->show();
            gun += " #枪Stop";
//            Message::static_msg->setWindowTitle(gun);
//            Message::_show(tr("电动汽车停止充电"));
            task->tcu_stage = TCU_STAGE_STOP_END;
            task->tcu_tmp_stage = TCU_STAGE_STOP_END;
            break;
        case TCU_STAGE_HEAT:
            break;
        case TCU_STAGE_TIME:
            break;
        case TCU_STAGE_ANY:
            break;


    }
}
