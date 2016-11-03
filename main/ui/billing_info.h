#ifndef BILLING_INFO_H
#define BILLING_INFO_H

#include <QWidget>
#include <QTimer>
#include "myerr_sigals_slots.h"
#include "mysigals_slots.h"

namespace Ui {
class Billing_info;
}

class Billing_info : public QWidget
{
    Q_OBJECT

public:
    explicit Billing_info(QWidget *parent = 0);
    ~Billing_info();
    QTimer billing_timer;
    QTimer tstatus_timer;
    mysigals_slots my_sigals;
    myerr_sigals_slots myerr_sigals;

private:
    Ui::Billing_info *ui;
public slots:
    void change_moni();
    void change_equinf();
    void change_batinf();
    void slot_timer();
    void slot_statustimer();
};

#endif // BILLING_INFO_H
