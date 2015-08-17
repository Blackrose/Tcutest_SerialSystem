/*=============================
	修改密码界面
=============================*/
#include "update_pwd.h"
#include "define.h"
#include "optMsg.h"
#include "sql/dbuser.h"

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

UpdatePwd::UpdatePwd(IMFrame *im,QWidget *parent): QWidget(parent),Ui_UpdatePwdForm()
{
	setupUi(this);
        setWindowFlags(Qt::Dialog);
	setGeometry(197,110,240,265);
	setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存
	
	connect(btn_clear,SIGNAL(clicked()),this,SLOT(clear()));
	connect(btn_update,SIGNAL(clicked()),this,SLOT(update()));

	connect(txt_name,SIGNAL(textChanged(const QString)),this,SLOT(txtChange(QString)));
	connect(txt_oldPwd,SIGNAL(textChanged(const QString)),this,SLOT(txtChange(QString)));
	connect(txt_newPwd,SIGNAL(textChanged(const QString)),this,SLOT(txtChange(QString)));
	connect(txt_newPwdChe,SIGNAL(textChanged(const QString)),this,SLOT(txtChange(QString)));

    imf = im;//QWSServer::setCurrentInputMethod(imf);
	txt_name->installEventFilter(this);
	txt_oldPwd->installEventFilter(this);
	txt_newPwd->installEventFilter(this);
	txt_newPwdChe->installEventFilter(this);

	printf("init UpdatePwd ok\n");
}
UpdatePwd::~UpdatePwd()
{
	printf("exit UpdatePwd\n");
}
void UpdatePwd::clear()
{
	txt_name->setText(tr(""));
	txt_oldPwd->setText(tr(""));
	txt_newPwd->setText(tr(""));
	txt_newPwdChe->setText(tr(""));
	txt_name->setFocus();
}
bool UpdatePwd::check()
{
	if(txt_name->text() == tr("") || txt_oldPwd->text() == tr("") || txt_newPwd->text() == tr("") || txt_newPwdChe->text() == tr(""))
	{
		if(txt_name->text() == tr(""))
			txt_name->setFocus();
		if(txt_oldPwd->text() == tr(""))
			txt_oldPwd->setFocus();
		if(txt_newPwd->text() == tr(""))
			txt_newPwd->setFocus();
		if(txt_newPwdChe->text() == tr(""))
			txt_newPwdChe->setFocus();
		QMessageBox::question(this,tr("提示信息"),tr("都不能为空！"), tr("确定"), tr("取消"));
		return false;
	}
	if(txt_newPwd->text() != txt_newPwdChe->text())
	{
		QMessageBox::question(this,tr("提示信息"),tr("两次输入的密码不一致！"), tr("确定"), tr("取消"));
		txt_newPwd->setText(tr(""));
		txt_newPwdChe->setText(tr(""));
		txt_newPwd->setFocus();
	}
	return true;
}
void UpdatePwd::update()
{
	DbUser user;
	if(txt_name->text()==tr("1"))
	{
        QMessageBox::question(this, tr("提示信息"), tr("您所在的帐户权限不足！"), tr("确定"), tr("取消"));
		txt_oldPwd->setReadOnly(true);
		txt_newPwd->setReadOnly(true);
		txt_newPwdChe->setReadOnly(true);
	}
	else
	{
	if(check())
	{
		if(QMessageBox::question(this,tr("提示信息"),tr("真的要修改用户:")+txt_name->text()+tr(" 密码吗？"), tr("确定"), tr("取消")) != 0)
			return;
		if(user.check(txt_name->text(),txt_oldPwd->text()))
		{
			if(user.updataPwd(txt_name->text(),txt_newPwd->text()))
			{
				QMessageBox::question(this,tr("提示信息"),tr("修改")+txt_name->text()+tr("密码成功！"), tr("确定"), tr("取消"));
				OptMsg::insertUpataPwd();
				clear();
			}
			else
			{
				QMessageBox::question(this, tr("提示信息"), tr("密码修改失败！"), tr("确定"), tr("取消"));
			}
		}
		else
		{
			QMessageBox::question(this, tr("提示信息"), tr("该用户不存在！"), tr("确定"), tr("取消"));
		}
	}
	}
}
void UpdatePwd::txtChange(const QString &str)
{
	QLineEdit* txt=qobject_cast<QLineEdit*>(sender());
	if(str.length()>6)
		txt->setText(str.left(6));
}
bool UpdatePwd::eventFilter(QObject *obj, QEvent *event)
{
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
		imf->my_show(&qr,txt);
	}
	if(event->type() == QEvent::FocusOut)
	{
		imf->my_hide();
	}
	return QWidget::eventFilter(obj, event);
}
