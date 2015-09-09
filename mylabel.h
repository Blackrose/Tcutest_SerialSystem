#ifndef MYLABEL
#define MYLABEL

#include <QLabel>
#include <QMouseEvent>

class mylabel: public QLabel
{
    Q_OBJECT

public:
    mylabel(QWidget * parent = 0);

private:

protected:
    virtual void mouseReleaseEvent(QMouseEvent * ev);

signals:
    void clicked(void);
};

#endif // MYLABEL

