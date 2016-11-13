#ifndef SWIPE_CARD_H
#define SWIPE_CARD_H

#include <QWidget>
#include "Card_window.h"

#define CARD
//#undef CARD

namespace Ui {
class Swipe_card;
}

class Swipe_card : public QWidget
{
    Q_OBJECT

public:
    explicit Swipe_card(QWidget *parent = 0);
    ~Swipe_card();

#ifdef CARD
         CardWindow *p_card;
         int flag;
         QTimer card_timer;
#endif

private:
    Ui::Swipe_card *ui;

signals:
    void display(int number);

public slots:
#ifdef CARD
    void slot_cardtimer();
#endif
};

#endif // SWIPE_CARD_H
