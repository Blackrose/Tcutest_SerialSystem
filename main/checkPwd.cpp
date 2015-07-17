/*=============================
	密码检查界面
=============================*/

#include "checkPwd.h"
#include "sql/dbuser.h"
#include "define.h"
#include "main.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCloseEvent>

CheckPwd::CheckPwd(IMFrame *im,QWidget *parent): QDialog(parent),Ui_CheckPwd()
{
	setupUi(this);
	p_imf = im;
	par = parent;
        setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	setAttribute(Qt::WA_DeleteOnClose);	
	setGeometry(200,180,211,121);

	txt_password->installEventFilter(this);
	connect(btn_close,SIGNAL(clicked()),this,SLOT(_hide()));
	connect(btn_ok,SIGNAL(clicked()),this,SLOT(CheckPwd_ok()));
	connect(txt_password,SIGNAL(textChanged(const QString)),this,SLOT(txtChange(QString)));
	
	printf("init CheckPwd ok\n");
}
CheckPwd::~CheckPwd()
{
	printf("exit CheckPwd\n");
}
void CheckPwd::CheckPwd_ok()
{
	DbUser user;
	if(txt_password->text() == tr(""))
	{
		Message::_show(tr("密码不能为空！"));
		txt_password->setFocus();
	}
	else if( user.checkPwd(txt_password->text()) == true)
	{
		printf("pwd 1\n");
		hide();
		printf("pwd 2\n");
		clear_txt();
		printf("pwd 3\n");
		((Main*)par)->check_pwd();
		printf("pwd 4\n");
	}
	else
	{
		clear_txt();
		Message::_show(tr("密码错误！"));
	}
	
}
void CheckPwd::_hide()
{
	clear_txt();
	hide();
}
void CheckPwd::_show()
{
	setGeometry(200,180,211,121);
	txt_password->setFocus();
	show();
}
void CheckPwd::clear_txt()
{
	txt_password->setText(tr(""));
	txt_password->setFocus();
}
void CheckPwd::txtChange(const QString &str)
{//控制字符串的长度
	QLineEdit* txt=qobject_cast<QLineEdit*>(sender());
	if(str.length()>6)
		txt->setText(str.left(6));
}
void CheckPwd::closeEvent ( QCloseEvent * event )
{
	event->ignore(); 
	clear_txt();
	hide();
}
bool CheckPwd::eventFilter(QObject *obj, QEvent *event)
{//事件过滤
	QLineEdit *txt = (QLineEdit*)obj;
	QWidget* wid=(QWidget*)obj;
	QRect qr,qr1;
	if(event->type() == QEvent::MouseButtonPress){
		qr = wid->geometry();
		int w=qr.width();
		int h=qr.height();
		wid = wid->parentWidget();
		while(wid != 0 ){
			qr1 = wid->geometry();
			qr.setX(qr.x()+qr1.x());
			qr.setY(qr.y()+qr1.y());
			wid = wid->parentWidget();
		}
		qr.setRect(qr.x(),qr.y(),w,h);
		p_imf->my_show(&qr,txt);
	}
	if(event->type() == QEvent::FocusOut){
			p_imf->my_hide();
	}
	return QWidget::eventFilter(obj,event);
}
