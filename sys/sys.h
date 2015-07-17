/*=========================
	系统管理
=========================*/
#ifndef LINLONG_SYS_MA
#define LINLONG_SYS_MA

#include <QWidget>
#include "ui_sys_manage.h"
#include <QString>
#include <QStackedWidget>
#include <QListWidgetItem>
#include <QTimer>
#include "Mset.h"
#include "user.h"
#include "update_pwd.h"
#include "sys_set.h"
#include "check.h"
#include "put_off.h"
#include "keyboard/imframe.h"

class  Sys:public QWidget,public Ui_SysForm
{
        Q_OBJECT
public :
        Sys(IMFrame *im,QWidget* parent=NULL);
        virtual ~Sys();

	Mset *p_Mset;//M监控参数设置
	User *p_user;//用户管理
	UpdatePwd *p_updPwd;//修改密码
	SysSet *p_sysSet;//系统设置

    	QStackedWidget *stackedWidget;

public slots:
	void curRowChg(int index);
	void _show();
};
#endif
