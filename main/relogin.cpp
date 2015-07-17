/*=============================
	密码检查界面
=============================*/

#include "relogin.h"
#include "sql/dbuser.h"
#include "define.h"
#include "main.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

Relogin::Relogin(IMFrame *im,QWidget *main,QWidget *parent): QDialog(parent),Ui_ReloginDialog()
{
	setupUi(this);
        setWindowFlags(Qt::Dialog
			| Qt::WindowCloseButtonHint);//窗口没有没有边框  是 一个模太对话框
	txt_user->installEventFilter(this);
	txt_password->installEventFilter(this);

	setGeometry(147,170,340,160);	
	setAttribute(Qt::WA_DeleteOnClose);
	p_main = main;
	p_imf= im;
	connect(btn_close,SIGNAL(clicked()),this,SLOT(hide()));
	connect(btn_ok,SIGNAL(clicked()),this,SLOT(Relogin_ok()));
	connect(txt_user,SIGNAL(textChanged(const QString)),this,SLOT(txtChange(QString)));
	connect(txt_password,SIGNAL(textChanged(const QString)),this,SLOT(txtChange(QString)));

	printf("init Relogin ok\n");
}
Relogin::~Relogin()
{
	printf("exit Relogin\n");
}
void Relogin::_show()
{
	clear_txt();
	setGeometry(147,170,340,160);	
	show();
}
void Relogin::Relogin_ok()
{
	DbUser user;
	if(txt_user->text() == tr("") || txt_password->text() == tr(""))
	{
		QMessageBox::question(this,tr("提示信息"),tr("用户名密码都不能为空！"), tr("确定"), tr("取消"));
		if(txt_user->text() == tr(""))
			txt_user->setFocus();
		else
			txt_password->setFocus();
		return;
	}
	if(user.login(txt_user->text(),txt_password->text()))
	{
		OptMsg::insertUserLogin();
		hide();
	}
	else{
		QMessageBox::question(this,tr("提示信息"),tr("登录失败！"), tr("确定"), tr("取消"));
		clear_txt();
	}
}
void Relogin::clear_txt()
{
	txt_user->setText(tr(""));
	txt_password->setText(tr(""));
	txt_user->setFocus();
}
void Relogin::txtChange(const QString &str)
{//控制字符串的长度
	QLineEdit* txt=qobject_cast<QLineEdit*>(sender());
	if(str.length() > 6)
		txt->setText(str.left(6));
}
void Relogin::closeEvent ( QCloseEvent * event )
{
	event->ignore(); 
	hide();
}
bool Relogin::eventFilter(QObject *obj, QEvent *event)
{//事件过滤
	QLineEdit *txt = (QLineEdit*)obj;
	QWidget* wid=(QWidget*)obj;
	QRect qr,qr1;
	if(event->type() == QEvent::MouseButtonPress)
	{
		qr = wid->geometry();
		int w=qr.width();
		int h=qr.height();
		wid = wid->parentWidget();
		while(wid != 0 )
		{
			qr1 = wid->geometry();
			qr.setX(qr.x()+qr1.x());
			qr.setY(qr.y()+qr1.y());
			wid = wid->parentWidget();
		}
		qr.setRect(qr.x(),qr.y(),w,h);
		p_imf->my_show(&qr,txt);
	}
	if(event->type() == QEvent::FocusOut)
	{
			p_imf->my_hide();
	}
	return QWidget::eventFilter(obj,event);
}
