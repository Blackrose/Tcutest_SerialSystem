/*=========================================
	系统 ui 入口函数
==========================================*/
#include "startUpFrm.h"

#include <QWaitCondition>
#include <QMutex>
#include <QTextCodec>
#include <QApplication>
#include "myevent.h"

bool MyEvent::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::MouseButtonPress) {
        //Led::LCDLightOn();
		emit clearSignal();
	}
	return QObject::eventFilter(obj, event);
}


int main(int argc,char **argv)
{
    QApplication::addLibraryPath("./plugins");
	QApplication app(argc,argv);

	MyEvent *my_event = new MyEvent;
	app.installEventFilter(my_event);

    //QTextCodec::setCodecForTr( QTextCodec::codecForName("GB2312"));

    //支持中文设计
//    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
//    QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);
	StartUp ma;
	ma.show();
	app.connect(my_event, SIGNAL(clearSignal()), &ma, SLOT(emitClear()));	
	return app.exec();
}
