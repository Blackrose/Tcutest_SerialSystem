#include "settlement_inf.h"
#include "ui_settlement_inf.h"
#include "test_manual.h"
#include "mythread.h"
#include "connect_charge.h"
#include "message/message.h"

settlement_inf::settlement_inf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settlement_inf)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存
    connect(ui->back_but,SIGNAL(clicked()),this,SLOT(slot_hide()));//BACK
    Message::static_msg = new Message();
}

settlement_inf::~settlement_inf()
{
    delete ui;
}


void settlement_inf::slot_hide()
{
     mythread_can.stop();
    test_Manual *w_Manual = new test_Manual;
    w_Manual->show();
}
