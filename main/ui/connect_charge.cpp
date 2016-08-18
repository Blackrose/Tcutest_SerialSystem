#include "connect_charge.h"
#include "ui_connect_charge.h"

connect_charge::connect_charge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connect_charge)
{
    ui->setupUi(this);
    connect(ui->back_but,SIGNAL(clicked()),this,SLOT(slot_hide()));//BACK
}

void connect_charge::slot_hide()
{
    hide();
}

connect_charge::~connect_charge()
{
    delete ui;
}
