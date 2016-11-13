#include "charging_mode.h"
#include "ui_charging_mode.h"
#include "swipe_card.h"

Charging_mode::Charging_mode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Charging_mode)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存
    connect(ui->charge_card_but,SIGNAL(clicked()),this,SLOT(slot_charge_card()));
}

Charging_mode::~Charging_mode()
{
    delete ui;
}

void Charging_mode::slot_charge_card()
{
    Swipe_card *w_swipe_card = new Swipe_card;
    w_swipe_card->show();
}
