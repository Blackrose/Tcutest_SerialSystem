/*===============================
	 系统启动界面
===============================*/
#ifndef LINLONG_StartUp
#define LINLONG_StartUp

#include "ui_forms/ui_startUpFrm.h"
#include "main/main.h"

#include <stdio.h>
#include <QString>
#include <QTimer>

class StartUp:public QWidget,public Ui_startUpFrm
{
        Q_OBJECT
public :
	int myFlag;
        StartUp(QWidget* parent=NULL);
        virtual ~StartUp();
	void _show();
	QTimer timer;	//定时器
	Main *main;
signals:
	void startupClear();
public slots:
	void slot_timer();//定时器
	void emitClear();
};

#endif
