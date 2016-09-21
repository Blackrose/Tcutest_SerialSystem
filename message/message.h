/*==============================================
	 系统检测界面
==============================================*/
#ifndef MY_Message_H
#define MY_Message_H

#include "ui_message.h"

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
    //void setWindowTitle(QString str);
	static void _show(QString str);
	static Message* static_msg;
	int i ; 
};

#endif//MY_Message_H
