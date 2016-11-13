#ifndef CARD_OPERATION_H
#define CARD_OPERATION_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class card_operation;
}

class card_operation : public QWidget
{
    Q_OBJECT

public:
    explicit card_operation(QWidget *parent = 0);
    ~card_operation();
    QTimer nextscreen_timer;	//

private:
    Ui::card_operation *ui;

signals:
    void display(int number);

public slots:
        void slot_nextscreen_timer();//定时器
};

#endif // CARD_OPERATION_H
