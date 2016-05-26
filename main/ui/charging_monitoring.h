#ifndef CHARGING_MONITORING_H
#define CHARGING_MONITORING_H

#include <QWidget>

namespace Ui {
class Charging_monitoring;
}

class Charging_monitoring : public QWidget
{
    Q_OBJECT

public:
    explicit Charging_monitoring(QWidget *parent = 0);
    ~Charging_monitoring();

private:
    Ui::Charging_monitoring *ui;
    int 	bat_soc_int;

 public slots:
     void set_soc();
     void change_moni();
     void change_equinf();
     void change_carinf();
     void change_end();
};

#endif // CHARGING_MONITORING_H
