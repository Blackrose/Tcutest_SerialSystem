#ifndef TEST_MANUAL_H
#define TEST_MANUAL_H

#include <QWidget>
//#include "mythread.h"
#include "connect_charge.h"
#include "my_only/widget.h"

#define MYTHREAD
#undef  MYTHREAD

namespace Ui {
class test_Manual;
}

//class QStackedLayout;
//class QVBoxLayout;

class test_Manual : public QWidget
{
    Q_OBJECT

public:
    explicit test_Manual(QWidget *parent = 0);
    ~test_Manual();
#ifdef MYTHREAD
    mythread mythread_can ;
#endif

private:
    Ui::test_Manual *ui;

    connect_charge *w_connect;
//    QStackedLayout *stackLayout;
//    QVBoxLayout *mainLayout;
    Widget *widget_tmp;

public slots:
    void slot_hide();
    void slot_card();
    void slot_emter();
    void slot_canbus();
    void slot_gps();
    void slot_gprs();
    void slot_network();
    void slot_touch();
    void slot_pwm();

//signals:
//    void display(int number);
};

#endif // TEST_MANUAL_H
