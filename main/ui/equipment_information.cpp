#include "equipment_information.h"
#include "ui_equipment_information.h"

Equipment_information::Equipment_information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Equipment_information)
{
    ui->setupUi(this);
}

Equipment_information::~Equipment_information()
{
    delete ui;
}
