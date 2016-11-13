#include "widget.h"
#include <QStackedLayout>
#include <QPushButton>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{    
#if 1
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存
    //setFixedSize(800, 480);
    setGeometry(-10,-10,820,500);
//    setFixedSize(800,480);
    w_connect = new connect_charge;//连接界面
    w_equ_testing = new equipment_testing;//

    w_change_moni = new Charging_monitoring;//
    w_equ_inf = new Equipment_information;
    w_bat_information = new bat_information;//
    w_billing_inf = new Billing_info;
    w_settlement_inf = new settlement_inf;//

    stackLayout = new QStackedLayout;

    stackLayout->addWidget(w_connect);//连接界面
    stackLayout->addWidget(w_equ_testing);

    stackLayout->addWidget(w_change_moni);
    stackLayout->addWidget(w_equ_inf);
    stackLayout->addWidget(w_bat_information);
    stackLayout->addWidget(w_billing_inf);

    stackLayout->addWidget(w_settlement_inf);

    connect(w_connect, SIGNAL(display(int)), stackLayout, SLOT(setCurrentIndex(int)));//0
    connect(w_equ_testing, SIGNAL(display(int)), stackLayout, SLOT(setCurrentIndex(int)));//1

    connect(w_change_moni, SIGNAL(display(int)), stackLayout, SLOT(setCurrentIndex(int)));//2
    connect(w_equ_inf, SIGNAL(display(int)), stackLayout, SLOT(setCurrentIndex(int)));//3
    connect(w_bat_information, SIGNAL(display(int)), stackLayout, SLOT(setCurrentIndex(int)));//4
    connect(w_billing_inf, SIGNAL(display(int)), stackLayout, SLOT(setCurrentIndex(int)));//5
    connect(w_settlement_inf, SIGNAL(display(int)), stackLayout, SLOT(setCurrentIndex(int)));//6

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(stackLayout);
    setLayout(mainLayout);
#endif
}

Widget::~Widget()
{
}
