#include "card_unlock.h"
#include "ui_card_unlock.h"
#include "tcu.h"
#include <QTime>
#include <QTimer>
#include <stdio.h>

Card_unlock::Card_unlock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Card_unlock)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存

    connect(ui->back_but,SIGNAL(clicked()),this,SLOT(slot_hide()));//BACK
    //connect(ui->start_but,SIGNAL(clicked()),this,SLOT(slot_start()));


    elapseTime = 1000;
    num=0;
    generateAscendRandomNumber();
    ui->label_inf->setVisible(true);
    ui->label_success->setVisible(false);
    setProgress();
}

void Card_unlock::setdisplay()
{
//    if(task->tcu_stage == TCU_STAGE_CONNECT || (task->tcu_stage == TCU_STAGE_WAITSTART))
//    {
//        ui->start_but->setVisible(false);
//        ui->label_inf->setVisible(true);
//        ui->label_success->setVisible(false);
//        setProgress();
//    }
//    else
//    {
//        ui->start_but->setVisible(true);
//        ui->label_inf->setVisible(false);
//        ui->label_success->setVisible(true);
//    }
}

void Card_unlock::setProgress()
{
    int tempTime=elapseTime/100;
    for(int i=0;i<100;i++)
    {
       QTimer::singleShot(i*tempTime, this, SLOT(slotUpdateProgress()));
    }
    //QTimer::singleShot(elapseTime, this, SLOT(close()));
    QTimer::singleShot(elapseTime, this, SLOT(slot_nextscreen_timer()));
}

void Card_unlock::slotUpdateProgress()
{
    ui->progressBar->setValue(numbersList[num]);
    //printf("numbersList%d==%d\n",num,numbersList[num]);
    num++;
    if(num == 100)
    {
         ui->progressBar->setValue(100);
         ui->label_inf->setVisible(false);
         ui->label_success->setVisible(true);
    }
}

void Card_unlock::generateAscendRandomNumber()
{
    int i;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    //生成100个大小在[0,100]之间的随机数
    for(i=0;i<100;i++)
    {
        numbersList.append(qrand()%101);
    }
    //递增排序
    qSort(numbersList.begin(),numbersList.end());
}

void Card_unlock::slot_nextscreen_timer()
{
    numbersList.clear();
    //emit display(2);
    //setdisplay();
    my_sigals.SetValue(TCU_STAGE_START);
}

void Card_unlock::slot_hide()
{
    //hide();
    numbersList.clear();
//    test_Manual *w_test = new test_Manual;
//    w_test->show();
//    connect_charge *w_connect = new connect_charge;
//    w_connect->show();
    //emit display(0);
}


Card_unlock::~Card_unlock()
{
    delete ui;
}
