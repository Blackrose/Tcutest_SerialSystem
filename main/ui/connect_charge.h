#ifndef CONNECT_CHARGE_H
#define CONNECT_CHARGE_H

#include <QWidget>

namespace Ui {
class connect_charge;
}

class connect_charge : public QWidget
{
    Q_OBJECT

public:
    explicit connect_charge(QWidget *parent = 0);
    ~connect_charge();

private:
    Ui::connect_charge *ui;

public slots:
    void slot_hide();
};

#endif // CONNECT_CHARGE_H
