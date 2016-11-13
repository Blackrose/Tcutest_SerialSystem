#ifndef CARD_UNLOCK_H
#define CARD_UNLOCK_H

#include <QWidget>
#include "mysigals_slots.h"

namespace Ui {
class Card_unlock;
}

class Card_unlock : public QWidget
{
    Q_OBJECT

public:
    explicit Card_unlock(QWidget *parent = 0);
    ~Card_unlock();
    QList<int > numbersList;//随机数列表
    int elapseTime; //启动界面停留的时间
    int num;//启动进度条计数1-100
    mysigals_slots my_sigals;

private:
    Ui::Card_unlock *ui;
    void setdisplay();
    void setProgress();
    void generateAscendRandomNumber();

public slots:
   void slot_nextscreen_timer();
   void slot_hide();  
   void slotUpdateProgress();

signals:
    void display(int number);
};

#endif // CARD_UNLOCK_H
