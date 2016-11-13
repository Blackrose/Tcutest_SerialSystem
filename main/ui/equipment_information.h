#ifndef EQUIPMENT_INFORMATION_H
#define EQUIPMENT_INFORMATION_H

#include <QWidget>
#include <QTimer>
#include <QLineEdit>
#include "mysigals_slots.h"
#include "myerr_sigals_slots.h"
#include "charging_monitoring.h"

namespace Ui {
class Equipment_information;
}

class Equipment_information : public QWidget
{
    Q_OBJECT

public:
    explicit Equipment_information(QWidget *parent = 0);
    ~Equipment_information();
     QTimer tcp_timer;	//
     QTimer tstatus_timer;
     mysigals_slots my_sigals;
     myerr_sigals_slots myerr_sigals;
     //Charging_monitoring *w_change_moni1;

     void charger_sn(QLineEdit* lbl);
     void spn_port(QLineEdit* lbl);
      void equ_inf();

private:
    Ui::Equipment_information *ui;

public slots:
    void slot_timer();//定时器
    void change_moni();
    void change_batinf();
    void change_billinf();
    void slot_statustimer();

signals:
    void display(int number);
};

#endif // EQUIPMENT_INFORMATION_H
