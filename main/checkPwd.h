/*==============================================
	密码检查界面
==============================================*/
#ifndef LINLONG_CHECKPWD
#define LINLONG_CHECKPWD

#include "ui_checkPwd.h"
#include <QDialog>
#include <QWidget>
#include <QPoint>
#include "keyboard/imframe.h"
#include "sql/optMsg.h"

class  CheckPwd:public QDialog,public Ui_CheckPwd
{
        Q_OBJECT
public :
        CheckPwd(IMFrame *im,QWidget* parent=NULL);
        virtual ~CheckPwd();
	IMFrame *p_imf;
	virtual bool eventFilter ( QObject * watched, QEvent * event );
private:
	virtual void closeEvent ( QCloseEvent * event );
	QWidget *par;
public slots:
	void txtChange(const QString &str);
	void clear_txt();
	void CheckPwd_ok();
	void _show();
	void _hide();
//signals:
//	void checkOk(); 
};
#endif
