#include "charging_monitoring.h"
#include "ui_forms/ui_charging_monitoring.h"
#include "equipment_information.h"
#include "bat_information.h"
#include "billing_info.h"
#include "charging_end.h"
#include "main.h"
#include "tcu.h"
#include <QtWidgets/QLabel>
#include <stdio.h>

Charging_monitoring::Charging_monitoring(QWidget *parent) : QWidget(parent), ui(new Ui::Charging_monitoring)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存

    ui->full_charge_but->setVisible(true);
    ui->charge_7but->setVisible(false);
    ui->charge_6but->setVisible(false);
    ui->charge_5but->setVisible(false);
    ui->charge_4but->setVisible(false);
    ui->charge_3but->setVisible(false);
    ui->charge_2but->setVisible(false);
    ui->charge_1but->setVisible(false);

    connect(ui->soc_set,SIGNAL(clicked()),this,SLOT(set_soc()));//查询
    //connect(ui->change_moni_but,SIGNAL(clicked()),this-,SLOT(change_moni());
    connect(ui->change_equ_but,SIGNAL(clicked()),this,SLOT(change_equinf()));//
    connect(ui->change_batinf_but,SIGNAL(clicked()),this,SLOT(change_batinf()));//
    //connect(ui->change_carinf_but,SIGNAL(clicked()),this,SLOT(change_carinf()));//
    connect(ui->change_billinf_but,SIGNAL(clicked()),this,SLOT(change_billinf()));//
    //connect(ui->change_end_but,SIGNAL(clicked()),this,SLOT(change_end()));//
    //connect(ui->soc_stop,SIGNAL(clicked()),this,SLOT(Charging_monitoring_hide()));
    //connect(ui->soc_stop,SIGNAL(clicked()),this,SLOT(change_main()));

    connect(&tst_timer,SIGNAL(timeout()),this,SLOT(slot_timer()));//停止充电
    tst_timer.start(100);

#if 0
    if(bat_soc_int<100){//90
        ui->full_charge_but->setVisible(false);
        ui->charge_7but->setVisible(true);
    }else if(bat_soc_int<90 && bat_soc_int>80){//80
        ui->charge_7but->setVisible(false);
        ui->charge_6but->setVisible(true);
    }else if(bat_soc_int<80 && bat_soc_int>60){//60
        ui->charge_6but->setVisible(false);
        ui->charge_5but->setVisible(true);
    }else if(bat_soc_int<60 && bat_soc_int>30){//40
        ui->charge_5but->setVisible(false);
        ui->charge_4but->setVisible(true);
    }else if(bat_soc_int<30 && bat_soc_int>20){//30
        ui->charge_4but->setVisible(false);
        ui->charge_3but->setVisible(true);
    }else if(bat_soc_int<20 && bat_soc_int>10){//20
        ui->charge_3but->setVisible(false);
        ui->charge_2but->setVisible(true);
    }else if(bat_soc_int<20){//10
        ui->charge_2but->setVisible(false);
        ui->charge_1but->setVisible(true);
    }
#endif
    printf("successs!!!");
}

void Charging_monitoring::slot_timer()
{
    if(task->tcu_stage == TCU_STAGE_STOP || task->tcu_err_stage == TCU_ERR_STAGE_STOP)
    {
            //QMessageBox::about(NULL, "Stop", "停止充电");
            my_sigals.SetValue(TCU_STAGE_STOP);
            tst_timer.stop();
    }
}


void Charging_monitoring::set_soc()
{
       ui->bat_soc->setText(ui->bat_soc->text());

       bat_soc_int =  ui->bat_soc->text().toInt();
       printf("bat_soc_txt==%d", bat_soc_int);

#if 0
       if(bat_soc_int==100 ){//90
           ui->full_charge_but->setVisible(true);
           ui->charge_7but->setVisible(false);
       }else if(bat_soc_int<100 && bat_soc_int>=90){//90
           ui->full_charge_but->setVisible(false);
           ui->charge_7but->setVisible(true);
       }else if(bat_soc_int<90 && bat_soc_int>=80){//80
           ui->charge_7but->setVisible(false);
           ui->charge_6but->setVisible(true);
       }else if(bat_soc_int<80 && bat_soc_int>=60){//60
           ui->charge_6but->setVisible(false);
           ui->charge_5but->setVisible(true);
       }else if(bat_soc_int<60 && bat_soc_int>=30){//40
           ui->charge_5but->setVisible(false);
           ui->charge_4but->setVisible(true);
       }else if(bat_soc_int<30 && bat_soc_int>=20){//30
           ui->charge_4but->setVisible(false);
           ui->charge_3but->setVisible(true);
       }else if(bat_soc_int<20 && bat_soc_int>=10){//20
           ui->charge_3but->setVisible(false);
           ui->charge_2but->setVisible(true);
       }else if(bat_soc_int<10){//10
           ui->charge_2but->setVisible(false);
           ui->charge_1but->setVisible(true);
       }
#else
       switch (bat_soc_int/10) {
       case 10://100
           ui->full_charge_but->setVisible(true);
           ui->charge_7but->setVisible(false);
           ui->charge_1but->setVisible(false);
           break;
       case 9://90
           ui->full_charge_but->setVisible(false);
           ui->charge_7but->setVisible(true);
           ui->charge_6but->setVisible(false);
           break;
       case 8://80
           ui->charge_7but->setVisible(false);
           ui->charge_6but->setVisible(true);
           ui->charge_5but->setVisible(false);
           break;
       case 7:
       case 6://60
           ui->charge_6but->setVisible(false);
           ui->charge_5but->setVisible(true);
           ui->charge_4but->setVisible(false);
           break;
       case 5:
       case 4://40
           ui->charge_5but->setVisible(false);
           ui->charge_4but->setVisible(true);
           ui->charge_3but->setVisible(false);
           break;
       case 3://30
           ui->charge_4but->setVisible(false);
           ui->charge_3but->setVisible(true);
           ui->charge_2but->setVisible(false);
           break;
       case 2://20
           ui->charge_3but->setVisible(false);
           ui->charge_2but->setVisible(true);
           ui->charge_1but->setVisible(false);
           break;
       case 1://10
       case 0:
           ui->charge_2but->setVisible(false);
           ui->charge_1but->setVisible(true);
           break;
       default:
           break;
       }
#endif
       show();
}

void Charging_monitoring::change_moni()
{
    Charging_monitoring *w_change_moni = new Charging_monitoring;
    w_change_moni->show();
}

void Charging_monitoring::change_equinf()
{
    Equipment_information *w_equipment_information = new Equipment_information;
    w_equipment_information->show();
}

void Charging_monitoring::change_batinf()
{
    bat_information *w_bat_information = new bat_information;
    w_bat_information->show();
}

void Charging_monitoring::change_billinf()
{
    Billing_info *w_billing_information = new Billing_info;
    w_billing_information->show();
}

void Charging_monitoring::change_end()
{    
    charging_end *w_charging_end = new charging_end;
    w_charging_end->show();
}

void Charging_monitoring::Charging_monitoring_hide()
{
    hide();
}

void Charging_monitoring::change_main()// error
{
    //Main *w_change_main = new Main();
    //w_change_main->show();
}

Charging_monitoring::~Charging_monitoring()
{
    delete ui;
}
