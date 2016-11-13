#include "card_operation.h"
#include "ui_card_operation.h"
#include <QMovie>
#include "card_unlock.h"

card_operation::card_operation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::card_operation)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存

#if 1
    QMovie*movie=new QMovie(":/img/images/loading1.gif");
    ui->main_gif->setMovie(movie);
    movie->start();
    //ui->main_gif->setWindowOpacity(0.8);
#endif
    connect(&nextscreen_timer,SIGNAL(timeout()),this,SLOT(slot_nextscreen_timer()));
    nextscreen_timer.start(1000);
}

void card_operation::slot_nextscreen_timer()
{
    nextscreen_timer.stop();
    Card_unlock *w_card_unlock = new Card_unlock;
    w_card_unlock->show();
}

card_operation::~card_operation()
{
    delete ui;
}
