#include "billing_info.h"
#include "ui_billing_info.h"

Billing_info::Billing_info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Billing_info)
{
    ui->setupUi(this);
}

Billing_info::~Billing_info()
{
    delete ui;
}
