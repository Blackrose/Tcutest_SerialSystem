#ifndef BILLING_INFO_H
#define BILLING_INFO_H

#include <QWidget>

namespace Ui {
class Billing_info;
}

class Billing_info : public QWidget
{
    Q_OBJECT

public:
    explicit Billing_info(QWidget *parent = 0);
    ~Billing_info();

private:
    Ui::Billing_info *ui;
};

#endif // BILLING_INFO_H
