#include "settlement_inf.h"
#include "ui_forms/ui_settlement_inf.h"

settlement_inf::settlement_inf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settlement_inf)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存
}

settlement_inf::~settlement_inf()
{
    delete ui;
}
