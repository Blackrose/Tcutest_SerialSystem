#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "connect_charge.h"
#include "equipment_testing.h"
#include "charging_monitoring.h"
#include "bat_information.h"
#include "settlement_inf.h"
#include "equipment_information.h"
#include "billing_info.h"

#if 1
class QStackedLayout;
class QVBoxLayout;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    connect_charge *w_connect;
    equipment_testing *w_equ_testing;
    Charging_monitoring *w_change_moni;
    bat_information *w_bat_information;
    settlement_inf *w_settlement_inf;
    Equipment_information *w_equ_inf;
    Billing_info *w_billing_inf;

private:
    QStackedLayout *stackLayout;
    QVBoxLayout *mainLayout;

signals:
    void display(int number);

};
#endif

#endif // WIDGET_H
