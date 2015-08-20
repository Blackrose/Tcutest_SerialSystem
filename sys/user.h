/*==============================================
	 用户管理界面
==============================================*/
#ifndef LINLONG_User
#define LINLONG_User

#include "ui_user.h"
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QTableWidgetItem>
#include <QPoint>
#include <QRect>
#include<QPixmap>
#include <QDesktopWidget>

#include "keyboard/imframe.h"
#include "sql/dbuser.h"

class  User:public QWidget,public Ui_UserForm
{
        Q_OBJECT
public:
        User(IMFrame *im,QWidget* parent=NULL);
	virtual bool eventFilter( QObject * watched, QEvent *event);
        virtual ~User();
	void del_qtw();
private:
	QTableWidgetItem *qtw;
	int sizeqtw;
	IMFrame *imf;
	DbUser user;
public slots:
	void  insert();//添加用户
	void  txtChange(const QString &str);
	void  clear();
	void  init_table();
	void  _delete();
	void  itemSelectionChanged();
	void  update();
	void _show();
};
#endif
