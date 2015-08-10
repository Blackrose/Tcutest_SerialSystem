/*==============================================
	 系统检测界面
==============================================*/
#ifndef LINLONG_Check
#define LINLONG_Check

#include "ui_check.h"
#include "bell.h"
#include "power.h"
#include "led.h"
#include "sql/optMsg.h"
//#include "main.h"
//#include "module/modList.h"

#include <stdio.h>
#include <QString>
//#include <QTimer>
#include <QWidget>

class Check:public QWidget,public Ui_CheckForm
{
        Q_OBJECT
public :
        Check(QWidget* parent=NULL);
        virtual ~Check();
	void _show();
	void a();
	void b();    
    QTimer timer;	//定时器
	int count;
    int sound;
//	Module *p_mod;
//	Main *main;
//	extern int whoChePwd;
private:
	virtual void closeEvent ( QCloseEvent * event );
	QWidget *par;
public slots:
	void start();
    void slot_timer();//定时器
	void ch();
};
#endif
