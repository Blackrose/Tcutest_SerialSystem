/*=============================
	用户管理界面
=============================*/
#include "user.h"
#include "define.h"
#include "optMsg.h"

#include <string.h>
#include <QWidget>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>

User::User(IMFrame *im,QWidget *parent): QWidget(parent),Ui_UserForm()
{
	setupUi(this);
        setWindowFlags(Qt::Dialog);
	setGeometry(130,45,380,400);
	setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存

	init_table();
	tableWidget->setAlternatingRowColors(true);//设置背景交替使用
	connect(btn_insert, SIGNAL(clicked()), this, SLOT(insert()));
	connect(txt_password,SIGNAL(textChanged(const QString)),this,SLOT(txtChange(QString)));
	connect(txt_user,SIGNAL(textChanged(const QString)),this,SLOT(txtChange(QString)));
	connect(tableWidget,SIGNAL(itemSelectionChanged()),this,SLOT(itemSelectionChanged()));
	connect(btn_delete,SIGNAL(clicked()),this,SLOT(_delete()));
	connect(btn_update,SIGNAL(clicked()),this,SLOT(update()));

	txt_user->installEventFilter(this);
	txt_password->installEventFilter(this);
    imf = im;//QWSServer::setCurrentInputMethod(imf);
	printf("init user ok\n");
}
User::~User()
{
	del_qtw();
	printf("exit user\n");
}
void User::_show()
{
	del_qtw();
	init_table();
}
/*============================*/
// 增加用户
void User::insert()
{
	int root = -1;
	if(txt_user->text() == tr("") || txt_password->text() == tr("")){
		QMessageBox::question(this,tr("提示信息"),tr("用户名密码都不能为空！"), tr("确定"), tr("取消"));
		return;
	}
	//权限的转化
	if(cmb_type->currentText() == tr("操作"))
		root = DO;
	else
		root = ROOT;
	//查看用户是否存在
	if(user.checkName(txt_user->text())){
		QMessageBox::question(this,tr("提示信息"),txt_user->text()+tr("用户存在！"), tr("确定"), tr("取消"));
		clear();
		return;
	}
	//插入用户
	if(user.insert(txt_user->text(),txt_password->text(),root)){
		QMessageBox::question(this,tr("提示信息"),txt_user->text()+tr("用户添加成功！"), tr("确定"), tr("取消"));
		OptMsg::insertUserInsert(); //添加添加用户操作记录
	}
	else{
		QMessageBox::question(this,tr("提示信息"),txt_user->text()+tr("用户添加失败！"), tr("确定"), tr("取消"));
	}
	clear();
	del_qtw();
	init_table();
	return;
}
/*============================*/
// 删除用户
void User::_delete()
{
    //QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(),pos().x(),pos().y(),frameGeometry().width(),frameGeometry().height());
//    QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(),0,0,800,600);
//    pixmap.save("6.png","png");

    if(txt_user->text()== tr("")){
        QMessageBox::question(this, tr("提示信息"), tr("用户名不能为空！"), tr("确定"), tr("取消"));
        return;
    }
    if( user.checkName(txt_user->text()) ){
        if(QMessageBox::question(this, tr("提示信息"), tr("真的要删除用户：")+txt_user->text()+tr("吗？"), tr("确定"), tr("取消"))==0){
            if(user.del(txt_user->text())){
                QMessageBox::question(this, tr("提示信息"), tr("删除用户：")+txt_user->text()+ tr("成功！"), tr("确定"), tr("取消"));
                OptMsg::insertUserDel(); //添加用户删除操作记录
                del_qtw();
                init_table();
            }
            else
                QMessageBox::question(this, tr("提示信息"), tr("删除用户：")+txt_user->text()+ tr("失败！"), tr("确定"), tr("取消"));
            clear();
        }
    }
    else{
        QMessageBox::question(this, tr("提示信息"), tr("此用户不存在！"), tr("确定"), tr("取消"));
    }
}
/*============================*/
// 修改用户
void User::update()
{
	int root=-1;
	if(txt_user->text()== tr("") || txt_password->text() == tr("")){
		QMessageBox::question(this, tr("提示信息"),tr("用户名密码都不能为空！"), tr("确定"), tr("取消"));
		return;
	}
	if(cmb_type->currentText() == tr("操作"))
		root = DO;
	else if(cmb_type->currentText() == tr("超级"))
		root = ROOT;
	if( user.checkName( txt_user->text()) ){
		if(QMessageBox::question(this, tr("提示信息"), tr("真的要修改用户：")+txt_user->text()+tr("吗？"), tr("确定"), tr("取消"))==0){
			if( user.updataUser(txt_user->text(),root,txt_password->text()) ){
				QMessageBox::question(this, tr("提示信息"), tr("修改用户：")+txt_user->text()+tr("成功！"), tr("确定"),tr("取消"));
				OptMsg::insertUserUpdate(); //添加修改操作记录
				del_qtw();
				init_table();
			}
			else 
				QMessageBox::question(this,tr("提示信息"),tr("修改用户：")+txt_user->text()+tr("失败！"), tr("确定"), tr("取消"));
			clear();
		}
	}
	else{
		QMessageBox::question(this,tr("提示信息"),tr("此用户不存在！"), tr("确定"), tr("取消"));
	}
}
/*============================*/
// 初始化用户表格
void User::init_table()
{
	QSqlQueryModel modelSql;
	user.getTable(Db::purview, & modelSql);
 	qtw = new QTableWidgetItem[2 * modelSql.rowCount() + 2];
	sizeqtw = 3 * modelSql.rowCount();
	qtw[0].setText(tr("用户名称"));
	qtw[1].setText(tr("用户类型"));

	tableWidget->setRowCount(modelSql.rowCount());
	tableWidget->setColumnCount(2);

	tableWidget->setHorizontalHeaderItem (0,&qtw[0]);
	tableWidget->setHorizontalHeaderItem (1,&qtw[1]);
	QSqlRecord re;
	for(int i = 0; i < modelSql.rowCount();i++){
		re = modelSql.record(i);
		qtw[(i+1)*2].setText(re.value(0).toString());
		tableWidget->setItem(i,0,&qtw[(i+1)*2]);
		if(re.value(2).toInt() == ROOT){
			qtw[(i+1)*2+1].setText(tr("超级用户"));
			tableWidget->setItem(i,1,&qtw[(i+1)*2+1]);
		}
		else{
			qtw[(i+1)*2+1].setText(tr("操作用户"));
			tableWidget->setItem(i,1,&qtw[(i+1)*2+1]);
		}
	}
}

/*============================*/
// 释放内存
void User::del_qtw()
{
	delete[] qtw;
}
/*============================*/
//选择用户
void User::itemSelectionChanged()
{
	int i_row = tableWidget->currentRow();
	QString cmt = qtw[(i_row+1)*2+1].text();
	txt_user->setText(qtw[(i_row+1)*2].text());
	txt_password->setText(user.getPwd(txt_user->text()));
	if(cmt == tr("超级用户")){
		cmb_type->setCurrentIndex(1);
	}
	else if(cmt == tr("操作用户")){
		cmb_type->setCurrentIndex(0);
	}
}
/*============================*/
// 控制字符串的长度
void User::txtChange(const QString &str)
{
	QLineEdit * txt=qobject_cast<QLineEdit*>(sender());
	if(str.length() > 6)
		txt->setText(str.left(6));
}
/*============================*/
// 清除文本数据
void User::clear()
{
	txt_user->setText(tr(""));
	txt_password->setText(tr(""));
}
bool User::eventFilter(QObject *obj, QEvent *event)
{
	QLineEdit *txt = (QLineEdit*)obj;
	QWidget* wid=(QWidget*)obj;
	QRect qr,qr1;
	if(event->type() == QEvent::FocusIn){
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
		imf->my_show(&qr,txt);
	}
	if(event->type() == QEvent::FocusOut){
		imf->my_hide();
	}
	return QWidget::eventFilter(obj, event);
}
