#include "test_manual.h"
#include "ui_test_manual.h"
#include "Card_window.h"

test_Manual::test_Manual(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::test_Manual)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/img/images/Main.png")));
    this->setPalette(palette);
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存

    connect(ui->back_but,SIGNAL(clicked()),this,SLOT(slot_hide()));//BACK
    connect(ui->Card_but,SIGNAL(clicked()),this,SLOT(slot_card()));
    connect(ui->Emeter_but,SIGNAL(clicked()),this,SLOT(slot_card()));
    connect(ui->Canbus_but,SIGNAL(clicked()),this,SLOT(slot_card()));
}

test_Manual::~test_Manual()
{
    delete ui;
}

void test_Manual::slot_hide()
{
    hide();
}

void test_Manual::slot_card()
{
    CardWindow *w_card = new CardWindow(this);
    w_card->show();
}
