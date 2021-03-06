#include "settlement_inf.h"
#include "ui_settlement_inf.h"
//#include "test_manual.h"
#include "equipment_testing.h"
#include "mythread.h"
#include "connect_charge.h"
#include "message/message.h"
#include "tcu.h"
#include "first_interface.h"
#include "test_auto.h"

settlement_inf::settlement_inf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settlement_inf)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存
    connect(ui->back_but,SIGNAL(clicked()),this,SLOT(slot_hide()));//BACK

    connect(&tst_timer,SIGNAL(timeout()),this,SLOT(slot_timer()));//停止充电
    tst_timer.start(100);

    Message::static_msg = new Message();
}

settlement_inf::~settlement_inf()
{
    delete ui;
}


void settlement_inf::slot_hide()
{
    hide();

     //mythread_can.stop();
//    equipment_testing *w_equ = new equipment_testing;
//    w_equ->show();

//    First_interface *w_first = new First_interface;
//    w_first->show();
//    task->tcu_stage == TCU_STAGE_WAITCONNECT;//跳过版本校验充电参数
//    connect_charge *w_connect = new connect_charge(this);
//    w_connect->show();
//        test_auto *w_test_auto = new test_auto;
//        w_test_auto->show();
}

void settlement_inf::slot_timer()
{
    if(task->tcu_err_stage == (TCU_ERR_STAGE_TIMEOUT | TCU_ERR_STAGE_STOP))
    {
        myerr_sigals.SetValue(task->tcu_err_stage);
        ui->label_inf->setText("停止充电超时");
        //QMessageBox::critical(NULL, "Error", "停止充电超时");
        //tst_timer.stop();
    }
    if(task->tcu_err_stage == TCU_ERR_STAGE_STARTING)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_STOP_END);
        ui->label_inf->setText("启动充电失败");
        //QMessageBox::critical(NULL, "Error", "启动充电失败");
        tst_timer.stop();
    }
    if(task->tcu_err_stage == TCU_ERR_STAGE_STOP_STATUS)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_STOP_END);
        ui->label_inf->setText("停止充电失败");
        //QMessageBox::critical(NULL, "Error", "停止充电失败");
        tst_timer.stop();
    }


    if(task->tcu_stage == TCU_STAGE_STOP)
    {
        ui->label_inf->setText("停止充电");
    }
    if(task->tcu_stage == TCU_STAGE_STOP_STATUS)
    {
        ui->label_inf->setText("停止充电...");
        my_sigals.SetValue(TCU_STAGE_STOP_STATUS);
    }
    if(task->tcu_stage == TCU_STAGE_STOP_END)
    {
        ui->label_inf->setText("停止充电完成");

    }



}

void settlement_inf::on_pushButton_clicked()
{
        task->tcu_stage == TCU_STAGE_WAITCONNECT;//跳过版本校验充电参数
        connect_charge *w_connect = new connect_charge(this);
        w_connect->show();
}
