#include "equipment_information.h"
#include "ui_equipment_information.h"
#include "charging_monitoring.h"
#include "bat_information.h"
#include "billing_info.h"
#include "charging_end.h"

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
