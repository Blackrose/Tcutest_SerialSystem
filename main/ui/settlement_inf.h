#ifndef SETTLEMENT_INF_H
#define SETTLEMENT_INF_H

#include <QWidget>

namespace Ui {
class settlement_inf;
}

class settlement_inf : public QWidget
{
    Q_OBJECT

public:
    explicit settlement_inf(QWidget *parent = 0);
    ~settlement_inf();

private:
    Ui::settlement_inf *ui;
};

#endif // SETTLEMENT_INF_H
