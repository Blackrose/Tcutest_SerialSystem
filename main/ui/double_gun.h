#ifndef DOUBLE_GUN_H
#define DOUBLE_GUN_H

#include <QWidget>
#include <QMovie>
#include <QTimer>
#include "mysigals_slots.h"
#include "myerr_sigals_slots.h"

namespace Ui {
class double_gun;
}

class double_gun : public QWidget
{
    Q_OBJECT

public:
    explicit double_gun(QWidget *parent = 0);
    ~double_gun();
    mysigals_slots my_sigals;
    myerr_sigals_slots myerr_sigals;

    QTimer tst_timer;	//
    QTimer tmp_timer;	//
    QTimer charging_timer;
    QTimer charging_timer_2;
    int   mytime_substract(struct timeval *result, struct timeval *begin,struct timeval *end);


private slots:
    void on_back_but_clicked();

    void on_c_moni_but_pressed();

    void on_c_equ_but_pressed();

    void on_c_billinf_but_pressed();

    void on_soc_stop_1_pressed();

    void on_c_moni_but_2_pressed();

    void on_c_equ_but_2_pressed();

    void on_c_billinf_but_2_pressed();

    void on_soc_stop_2_pressed();

    void slot_statustimer();
    void slot_tmptimer();
    void slot_chargingtimer();
    void slot_chargingtimer_2();

private:
    Ui::double_gun *ui;

public:
    void  c_moni_msg();
    void  c_equ_msg();
    void  c_bill_msg();

    void  c_moni_msg_2();
    void  c_equ_msg_2();
    void  c_bill_msg_2();

};

#endif // DOUBLE_GUN_H
