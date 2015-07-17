/*==============================
	修改密码界面
=================================*/
#ifndef LINLONG_UpdatePwd
#define LINLONG_UpdatePwd

#include "ui_update_pwd.h"
#include <QWidget>
#include <QPoint>
#include <QRect>
#include "../keyboard/imframe.h"

class  UpdatePwd:public QWidget,public Ui_UpdatePwdForm
{
        Q_OBJECT
public :
        UpdatePwd(IMFrame *im,QWidget* parent=NULL);
        virtual ~UpdatePwd();	
	bool check();
	virtual bool eventFilter( QObject * watched, QEvent *event);
	IMFrame *imf;
public slots:
	void clear();
	void update();
	void txtChange(const QString &str);
};
#endif
