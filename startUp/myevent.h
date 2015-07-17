#ifndef MY_ENENT
#define MY_ENENT

#include <QObject>
#include <QEvent>

class MyEvent : public QObject
{
Q_OBJECT

private:
	int eventNum;

signals:
	void clearSignal();

public:
	virtual bool eventFilter( QObject *obj, QEvent *event);
};

#endif
