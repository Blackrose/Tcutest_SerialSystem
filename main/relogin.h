/*==============================================
	密码检查界面
==============================================*/
#ifndef LINLONG_PwdCheck
#define LINLONG_PwdCheck

#include "ui_relogin.h"
#include <QDialog>
#include <QWidget>
#include <QPoint>
#include "keyboard/imframe.h"
#include "sql/optMsg.h"

class  Relogin:public QDialog,public Ui_ReloginDialog
{
        Q_OBJECT
public :
        Relogin(IMFrame *im,QWidget *main,QWidget* parent=NULL);
        virtual ~Relogin();
	IMFrame *p_imf;
	virtual bool eventFilter ( QObject * watched, QEvent * event );
	
	void _show();
private:
	virtual void closeEvent ( QCloseEvent * event );
	QWidget *p_main;
public slots:
	void txtChange(const QString &str);
	void clear_txt();
	void Relogin_ok();
};
#endif
