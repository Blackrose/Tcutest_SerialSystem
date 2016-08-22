#ifndef EQUIPMENT_TESTING_H
#define EQUIPMENT_TESTING_H

#include <QWidget>
#include <QTimer>
#include <unistd.h>

namespace Ui {
class equipment_testing;
}

class equipment_testing : public QWidget
{
    Q_OBJECT

public:
    explicit equipment_testing(QWidget *parent = 0);
    ~equipment_testing();
    QTimer timer;	//定时器

private:
    Ui::equipment_testing *ui;
public slots:
    void slot_timer();//定时器
};

#endif // EQUIPMENT_TESTING_H
