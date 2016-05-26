#include "car_information.h"
#include "ui_car_information.h"

Car_information::Car_information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Car_information)
{
    ui->setupUi(this);
}

Car_information::~Car_information()
{
    delete ui;
}
