#ifndef TEST_AUTO_H
#define TEST_AUTO_H

#include <QWidget>
#include "mysigals_slots.h"


namespace Ui {
class test_auto;
}

class test_auto : public QWidget
{
    Q_OBJECT

public:
    explicit test_auto(QWidget *parent = 0);
    ~test_auto();
    mysigals_slots my_sigals;

private:
    Ui::test_auto *ui;

public slots:
    void slot_hide();

private slots:
    void on_start_but_clicked();
};

#endif // TEST_AUTO_H
