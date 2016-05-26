#include "charging_end.h"
#include "ui_charging_end.h"

charging_end::charging_end(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::charging_end)
{
    ui->setupUi(this);
}

charging_end::~charging_end()
{
    delete ui;
}
