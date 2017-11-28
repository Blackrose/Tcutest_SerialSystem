#include "equipment_information.h"
#include "ui_equipment_information.h"
//#include "charging_monitoring.h"
#include "bat_information.h"
#include "billing_info.h"
#include "charging_end.h"
#include "tcu.h"

#include <stdio.h>
#undef AC_CHARGER


Equipment_information::Equipment_information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Equipment_information)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存

    connect(ui->change_moni_but,SIGNAL(clicked()),this,SLOT(change_moni()));//
    //connect(ui->change_equ_but,SIGNAL(clicked()),this,SLOT(change_equinf()));//
    connect(ui->change_batinf_but,SIGNAL(clicked()),this,SLOT(change_batinf()));//
    connect(ui->change_billinf_but,SIGNAL(clicked()),this,SLOT(change_billinf()));//

    connect(&tcp_timer,SIGNAL(timeout()),this,SLOT(slot_timer()));//参数
    tcp_timer.start(100);

    connect(&tstatus_timer,SIGNAL(timeout()),this,SLOT(slot_statustimer()));//充电状态
    tstatus_timer.start(100);

}

void Equipment_information::slot_timer()
{
        charger_sn(ui->charger_sn);
#ifdef AC_CHARGER
        spn_port(ui->charger_interface_ID);
        equ_inf();
#endif
}

void Equipment_information::charger_sn(QLineEdit* lbl)// 充电机编号
{
    char ch[50];
    sprintf(ch,"%02x%02x%02x%02x",
            task->tcp_info.spn2304_charger_sn[0],
            task->tcp_info.spn2304_charger_sn[1],
            task->tcp_info.spn2304_charger_sn[2],
            task->tcp_info.spn2304_charger_sn[3]);
    lbl->setText(ch);
}

void Equipment_information::spn_port(QLineEdit* lbl)
{
    char ch[50];
    sprintf(ch,"%d",task->crf_info.spn8448_port);
    lbl->setText(ch);
}

void Equipment_information::equ_inf()
{
    char ch[50];

    sprintf(ch,"%5.1f",(float)(task->ctf_info.spn8704_out_vol[1] + task->ctf_info.spn8704_out_vol[0]*256)/10);
    ui->charge_vol->setText(ch);

    sprintf(ch,"%4.2f",(float)(task->ctf_info.spn8704_out_cur[1] + task->ctf_info.spn8704_out_cur[0]*256)/100);
    ui->charge_current->setText(ch);

    sprintf(ch,"%7.3f",(float)(task->ctf_info.spn8704_out_vol[1] + task->ctf_info.spn8704_out_vol[0]*256)*(task->ctf_info.spn8704_out_cur[1] + task->ctf_info.spn8704_out_cur[0]*256)/1000000);
    ui->charge_power->setText(ch);

    int cc_status;
    cc_status = task->crf_info.spn8448_status & 0x0F;

    if(cc_status == CC_WAIT)
    {
        sprintf(ch,"待机");
    }else if(cc_status == CC_WORK)
    {
            sprintf(ch,"工作");
    }else if(cc_status == CC_FULL)
    {
            sprintf(ch,"充满");
    }else if(cc_status == CC_WARN)
    {
            sprintf(ch,"告警");
    }else if(cc_status == CC_ERROR)
    {
            sprintf(ch,"故障");
    }
    ui->charger_status->setText(ch);
}

void Equipment_information::slot_statustimer()
{
    if(task->tcu_err_stage == (TCU_ERR_STAGE_TIMEOUT | TCU_ERR_STAGE_START))
    {
        myerr_sigals.SetValue(task->tcu_err_stage);
        //ui->label_inf->setText("启动充电超时");
        //QMessageBox::critical(NULL, "Error", "启动充电超时");
        //tstatus_timer.stop();//注释掉可重试进行下一步，否则定时器停止，无法跳转界面到
    }
    if(task->tcu_err_stage == (TCU_ERR_STAGE_TIMEOUT | TCU_ERR_STAGE_STOP))
    {
        myerr_sigals.SetValue(task->tcu_err_stage);
        //ui->label_inf->setText("停止充电超时");
        //QMessageBox::critical(NULL, "Error", "停止充电超时");
        //tstatus_timer.stop();
    }

    if(task->tcu_stage == TCU_STAGE_START)
    {
        //ui->label_inf->setText("启动充电");
    }

    if(task->tcu_stage == TCU_STAGE_STARTING)
    {
        //ui->label_inf->setText("启动充电...");
        my_sigals.SetValue(TCU_STAGE_STARTING);
    }

    if(task->tcu_stage == TCU_STAGE_STATUS)
    {
        //ui->label_inf->setText("启动充电完成");
        my_sigals.SetValue(TCU_STAGE_STATUS);
    }

    if(task->tcu_stage == TCU_STAGE_CHARGING)
    {
        //ui->label_inf->setText("充电中...");
    }

    if(task->tcu_stage == TCU_STAGE_STOP || task->tcu_err_stage == TCU_ERR_STAGE_STOP)
    {
            //QMessageBox::about(NULL, "Stop", "停止充电");
            //ui->label_inf->setText("停止充电");
            my_sigals.SetValue(TCU_STAGE_STOP);
            tstatus_timer.stop();
    }

    if(task->tcu_stage == TCU_STAGE_STOP_END )
    {
            //QMessageBox::about(NULL, "Stop", "停止充电");
            //ui->label_inf->setText("停止充电");
            my_sigals.SetValue(TCU_STAGE_STOP_END);
            tstatus_timer.stop();
    }

    if(task->tcu_err_stage == TCU_ERR_STAGE_START)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_START);
        //ui->label_inf->setText("启动充电失败");
        //QMessageBox::critical(NULL, "Error", "启动充电失败");
        tstatus_timer.stop();
    }

    if(task->tcu_err_stage == TCU_ERR_STAGE_STARTING)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_STARTING);
        //ui->label_inf->setText("启动充电失败");
        //QMessageBox::critical(NULL, "Error", "启动充电失败");
        tstatus_timer.stop();
    }

    if(task->tcu_err_stage == TCU_ERR_STAGE_STOP_STATUS)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_STOP_STATUS);
        //ui->label_inf->setText("停止充电失败");
        //QMessageBox::critical(NULL, "Error", "停止充电失败");
        tstatus_timer.stop();
    }

}


void Equipment_information::change_moni()
{
    Charging_monitoring *w_change_moni = new Charging_monitoring;
    w_change_moni->show();
}

void Equipment_information::change_batinf()
{
    bat_information *w_bat_information = new bat_information;
    w_bat_information->show();
}

void Equipment_information::change_billinf()
{
    Billing_info *w_billing_information = new Billing_info;
    w_billing_information->show();
}

Equipment_information::~Equipment_information()
{
    delete ui;
}
