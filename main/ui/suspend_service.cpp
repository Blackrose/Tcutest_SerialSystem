#include "suspend_service.h"
#include "ui_suspend_service.h"

suspend_service::suspend_service(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::suspend_service)
{
    ui->setupUi(this);
}

suspend_service::~suspend_service()
{
    delete ui;
}
