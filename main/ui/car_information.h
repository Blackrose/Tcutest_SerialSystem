#ifndef CAR_INFORMATION_H
#define CAR_INFORMATION_H

#include <QWidget>

namespace Ui {
class Car_information;
}

class Car_information : public QWidget
{
    Q_OBJECT

public:
    explicit Car_information(QWidget *parent = 0);
    ~Car_information();

private:
    Ui::Car_information *ui;
};

#endif // CAR_INFORMATION_H
