#ifndef TEST_MANUAL_H
#define TEST_MANUAL_H

#include <QWidget>
#include "mythread.h"

namespace Ui {
class test_Manual;
}

class test_Manual : public QWidget
{
    Q_OBJECT

public:
    explicit test_Manual(QWidget *parent = 0);
    ~test_Manual();
    mythread mythread_can ;
private:
    Ui::test_Manual *ui;

public slots:
    void slot_hide();
    void slot_card();
    void slot_emter();
    void slot_canbus();
};

#endif // TEST_MANUAL_H
