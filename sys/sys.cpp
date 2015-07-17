/*=============================
	系统管理
=============================*/
#include "sys.h"
#include "define/define.h"
#include <stdio.h>
#include <QWidget>
#include "rxdata.h"
#include "main.h"

Sys::Sys(IMFrame *im,QWidget *parent): QWidget(parent),Ui_SysForm()
{
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存
 	setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边框 是一个模太对话框
	setGeometry(0,0,800,600);

        stackedWidget = new QStackedWidget(this);
        stackedWidget->setGeometry(QRect(150, 10, 681, 581));
        stackedWidget->setFrameShape(QFrame::NoFrame);
        stackedWidget->setFrameShadow(QFrame::Raised);
        stackedWidget->setMidLineWidth(1);

	p_Mset = new Mset( im, parent);//M节点参数设置
	stackedWidget->addWidget((QWidget *)p_Mset);

	p_sysSet = new SysSet( im,parent);//系统设置
	stackedWidget->addWidget((QWidget *)p_sysSet);

	p_user = new User( im, parent);//用户管理
	stackedWidget -> addWidget((QWidget *)p_user);

	p_updPwd = new UpdatePwd( im, parent);//修改密码
	stackedWidget->addWidget((QWidget *)p_updPwd);

	connect(listWidget,SIGNAL(currentRowChanged (int)),this,SLOT(curRowChg (int)));

	printf("init sys ok\n");
}
void Sys::curRowChg(int index)
{
	if(index == 0)
	{//M型节点参数设置
		stackedWidget-> setCurrentIndex(0);
		p_Mset->_show();
	}
	else if(index == 1)
	{//系统参数设置
		stackedWidget->setCurrentIndex(1);
		p_sysSet->_show();
	}
	else if(index == 2)
	{//用户管理
		if( Db::purview != DO)
		{
			stackedWidget->setCurrentIndex(2);
			p_user->_show();
		}
		else
		{
			Message::_show(tr("权限不足请使用超级用户!"));
		}
	}
	else if(index == 3)
	{//修改密码
		stackedWidget->setCurrentIndex(3);
	}
	if(index == 4)
	{
		p_Mset->timer.stop();
		hide();
	}
}
void Sys::_show()
{
	printf("listWidget = %p \n", listWidget);
	show();
	printf("listWidget12121\n");
	listWidget -> setCurrentRow(0);
	printf("ss 002\n");
}
Sys::~Sys()
{
	printf("exit Query\n");
}
