#ifndef BAT_INFORMATION_H
#define BAT_INFORMATION_H

#include <QWidget>
#include <QTimer>
#include "mysigals_slots.h"
#include "myerr_sigals_slots.h"

namespace Ui {
class bat_information;
}

class bat_information : public QWidget
{
    Q_OBJECT

public:
    explicit bat_information(QWidget *parent = 0);
    ~bat_information();
    QTimer bat_timer;
    QTimer tstatus_timer;	//
    mysigals_slots my_sigals;
    myerr_sigals_slots myerr_sigals;

private:
    Ui::bat_information *ui;

public slots:
    void change_moni();
    void change_equinf();
    void change_billinf();
    void slot_timer();
    void slot_statustimer();

signals:
    void display(int number);
};

#endif // BAT_INFORMATION_H
