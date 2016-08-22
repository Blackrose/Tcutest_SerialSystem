#include "equipment_testing.h"
#include "ui_equipment_testing.h"
#include "connect_charge.h"

equipment_testing::equipment_testing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::equipment_testing)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存

    connect(&timer,SIGNAL(timeout()),this,SLOT(slot_timer()));//显示系统时间
    timer.start(200);
    show();
}

void equipment_testing::slot_timer()
{
    timer.stop();
    ui->progressBar->setValue(8);
    usleep(100000);
    ui->progressBar->setValue(16);
    usleep(100000);
    ui->progressBar->setValue(24);
    usleep(100000);
    ui->progressBar->setValue(32);
    usleep(100000);
    ui->progressBar->setValue(40);
    usleep(100000);
    ui->progressBar->setValue(48);
    usleep(100000);
    ui->progressBar->setValue(56);
    usleep(100000);
    ui->progressBar->setValue(64);
    usleep(100000);
    ui->progressBar->setValue(72);
    usleep(100000);
    ui->progressBar->setValue(80);
    usleep(100000);
    ui->progressBar->setValue(88);
    usleep(100000);
    ui->progressBar->setValue(96);
    usleep(100000);
    ui->progressBar->setValue(100);
    usleep(100000);
    show();
    usleep(200000);
    //connect_charge *w_connect_charge = new connect_charge;
    //w_connect_charge->show();


}
equipment_testing::~equipment_testing()
{
    delete ui;
}
