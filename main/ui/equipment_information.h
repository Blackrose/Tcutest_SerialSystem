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

public slots:
    void change_moni();
    void change_batinf();
    void change_billinf();
};

#endif // EQUIPMENT_INFORMATION_H
