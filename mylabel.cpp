#include "mylabel.h"


mylabel::mylabel(QWidget * parent)
    : QLabel(parent)
{

}

void mylabel::mouseReleaseEvent(QMouseEvent * ev)
{
    Q_UNUSED(ev)
    emit clicked();
}
