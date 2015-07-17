/*==============================================
	 帮助界面
==============================================*/
#ifndef MHW_HELP
#define MHW_HELP

#include "ui_help.h"
#include <QWidget>
#include <QCloseEvent>


class Help : public QWidget, public Ui_HelpForm
{
	Q_OBJECT
public :
	Help(QWidget *parent = NULL);
	virtual ~Help();
	void _show();
private:
	virtual void closeEvent ( QCloseEvent * event );
	QWidget *par;
};
#endif
