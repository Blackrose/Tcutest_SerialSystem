#include "equipment_testing.h"
#include "ui_equipment_testing.h"

equipment_testing::equipment_testing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::equipment_testing)
{
    ui->setupUi(this);
}

equipment_testing::~equipment_testing()
{
    delete ui;
}
