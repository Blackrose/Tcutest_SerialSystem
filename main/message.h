/*==============================================
	 系统检测界面
==============================================*/
#ifndef LINLONG_Message
#define LINLONG_Check

#include "ui_message.h"
#include "bell.h"
#include "power.h"
#include "led.h"
#include "sql/optMsg.h"

#include <stdio.h>
#include <QString>

class Message:public QWidget,public Ui_Message
{
        Q_OBJECT
public :
        Message(QWidget* parent = NULL);
        virtual ~Message();
	virtual void closeEvent ( QCloseEvent * event );
	void setText(QString str);
	static void _show(QString str);
	static Message* static_msg;
	int i ; 
};
#endif
