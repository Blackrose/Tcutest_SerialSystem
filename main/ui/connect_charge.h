#ifndef CONNECT_CHARGE_H
#define CONNECT_CHARGE_H

#include <QWidget>
#include <QTimer>
#include <unistd.h>
#include "mythread.h"
#include <QLabel>
#include <QLineEdit>
#include "global.h"
#include "mysigals_slots.h"
#include "myerr_sigals_slots.h"
#include <QMessageBox>
#include "Emter_window.h"

#define EMTER_1
#undef EMTER_1

#define MYTHREAD
//#undef  MYTHREAD

namespace Ui {
class connect_charge;
}

class connect_charge : public QWidget
{
    Q_OBJECT

public:
    explicit connect_charge(QWidget *parent = 0);
    ~connect_charge();
    QTimer can_timer;	//
    QTimer tcv_timer;	//
    QTimer nextscreen_timer;	//

#ifdef MYTHREAD
    mythread mythread_can ;
#endif

    void check_ver(QLineEdit* lbl);
    void newTimeNoSec(QLabel* lbl);

    mysigals_slots my_sigals;
    myerr_sigals_slots myerr_sigals;

#ifndef EMTER_1
         EmterWindow *p_emter;
         int flag;
         QTimer emter_timer;
#endif

private:
    Ui::connect_charge *ui;

public slots:
    void slot_hide();
    void slot_cantimer();
    void slot_timer();//定时器
    void slot_nextscreen_timer();//定时器
#ifndef EMTER_1
    void slot_emtertimer();
#endif

signals:
    void display(int number);
};

#endif // CONNECT_CHARGE_H
