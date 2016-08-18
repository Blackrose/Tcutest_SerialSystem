#ifndef EQUIPMENT_TESTING_H
#define EQUIPMENT_TESTING_H

#include <QWidget>

namespace Ui {
class equipment_testing;
}

class equipment_testing : public QWidget
{
    Q_OBJECT

public:
    explicit equipment_testing(QWidget *parent = 0);
    ~equipment_testing();

private:
    Ui::equipment_testing *ui;
};

#endif // EQUIPMENT_TESTING_H
