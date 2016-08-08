#ifndef TEST_MANUAL_H
#define TEST_MANUAL_H

#include <QWidget>

namespace Ui {
class test_Manual;
}

class test_Manual : public QWidget
{
    Q_OBJECT

public:
    explicit test_Manual(QWidget *parent = 0);
    ~test_Manual();

private:
    Ui::test_Manual *ui;

public slots:
    void slot_hide();
    void slot_card();
};

#endif // TEST_MANUAL_H
