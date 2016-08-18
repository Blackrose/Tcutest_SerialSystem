#include "settlement_inf.h"
#include "ui_settlement_inf.h"

settlement_inf::settlement_inf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settlement_inf)
{
    ui->setupUi(this);
}

settlement_inf::~settlement_inf()
{
    delete ui;
}
