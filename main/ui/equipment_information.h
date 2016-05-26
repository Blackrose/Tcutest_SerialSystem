#ifndef EQUIPMENT_INFORMATION_H
#define EQUIPMENT_INFORMATION_H

#include <QWidget>

namespace Ui {
class Equipment_information;
}

class Equipment_information : public QWidget
{
    Q_OBJECT

public:
    explicit Equipment_information(QWidget *parent = 0);
    ~Equipment_information();

private:
    Ui::Equipment_information *ui;
};

#endif // EQUIPMENT_INFORMATION_H
