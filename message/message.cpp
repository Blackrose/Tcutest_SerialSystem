/*=============================
	系统检测界面
=============================*/

#include "message.h"
#include <QWidget>
#include <QCloseEvent>

Message* Message::static_msg = NULL;

Message::Message(QWidget *parent): QWidget(parent),Ui_Message()
{
	setupUi(this);
        setWindowFlags(Qt::Dialog
			| Qt::WindowCloseButtonHint);//窗口没有没有边框  是 一个模太对话框
    setGeometry(300, 190, 200, 100);
	setAttribute(Qt::WA_DeleteOnClose);
	printf("init Message ok\n");
	i = 0;
}
void Message::closeEvent ( QCloseEvent * event )
{
	event->ignore(); 
	lblMsg->setText(tr(""));
	lblMsg_2->setText(tr(""));
	hide();
}
Message::~Message()
{
	printf("exit Message\n");
}
void Message::setText(QString str)
{
	if( i == 0)
	{
		lblMsg->setText(str);
		i = 1;
	}
	else if(i == 1)
	{
		lblMsg_2->setText(str);
		i = 0;
	}
}
//void Message::setWindowTitle(QString str)
//{
//    static_msg->setWindowTitle(str);
//}
void Message::_show(QString str)
{
    static_msg->setGeometry(300, 190, 200, 100);
	static_msg->setText(str);
	static_msg->show();
}
