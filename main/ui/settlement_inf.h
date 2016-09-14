#ifndef SETTLEMENT_INF_H
#define SETTLEMENT_INF_H

#include <QWidget>
#include "mythread.h"

namespace Ui {
class settlement_inf;
}

class settlement_inf : public QWidget
{
    Q_OBJECT

public:
    explicit settlement_inf(QWidget *parent = 0);
    ~settlement_inf();
    mythread mythread_can;

private:
    Ui::settlement_inf *ui;
public slots:
    void slot_hide();
};

#endif // SETTLEMENT_INF_H
