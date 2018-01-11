#include "billing_info.h"
#include "ui_billing_info.h"
#include "charging_monitoring.h"
#include "equipment_information.h"
#include "bat_information.h"
#include "tcu.h"

Billing_info::Billing_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Billing_info)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存

    connect(ui->change_moni_but,SIGNAL(clicked()),this,SLOT(change_moni()));//
    connect(ui->change_equ_but,SIGNAL(clicked()),this,SLOT(change_equinf()));//
    connect(ui->change_batinf_but,SIGNAL(clicked()),this,SLOT(change_batinf()));//

    connect(&billing_timer,SIGNAL(timeout()),this,SLOT(slot_timer()));//参数
    billing_timer.start(100);
    connect(&tstatus_timer,SIGNAL(timeout()),this,SLOT(slot_statustimer()));//充电状态
    tstatus_timer.start(100);
}

void Billing_info::change_moni()
{
    Charging_monitoring *w_change_moni = new Charging_monitoring;
    w_change_moni->show();
}

void Billing_info::change_equinf()
{
    Equipment_information *w_equipment_information = new Equipment_information;
    w_equipment_information->show();
}

void Billing_info::change_batinf()
{
    bat_information *w_bat_information = new bat_information;
    w_bat_information->show();
}

void Billing_info::slot_timer()
{
#if 0
    ui->total_power->setText("");
    ui->total_cost->setText("");

    ui->tip_power->setText("");
    ui->tip_price->setText("");

    ui->peak_power->setText("");
    ui->peak_price->setText("");

    ui->flat_power->setText("");
    ui->flat_price->setText("");

    ui->valley_power->setText("");
    ui->valley_price->setText("");
#endif

    if(task->gun_num == GUN_NUM1 && task->gun_sn == GUN_SN0){
        ui->total_power->setText(task->emter_info[EMTER_NUM0].emter_power);
    }else if(task->gun_num == GUN_NUM1 && task->gun_sn == GUN_SN1){
        ui->total_power->setText(task->emter_info[EMTER_NUM1].emter_power);
    }else if(task->gun_num == GUN_NUM2 && task->gun_sn == GUN_SN2){
        ui->total_power->setText(task->emter_info[EMTER_NUM2].emter_power);
    }
        //ui->total_cost->setText("");
}

void Billing_info::slot_statustimer()
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

Billing_info::~Billing_info()
{
    delete ui;
}
