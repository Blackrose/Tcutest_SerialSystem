/*==============================================
	 打印设置界面
==============================================*/
#ifndef MHW_PRINTER
#define MHW_PRINTER

#include "ui_printer.h"
#include <QCloseEvent>
#include <QWidget>
#include <stdio.h>

class Printer : public QWidget, public Ui_PrinterForm
{
	Q_OBJECT
public :
	Printer(QWidget *parent = NULL);
	virtual ~Printer();
	void _show();
private:
	virtual void closeEvent(QCloseEvent * event);
	QWidget *par;
public slots:
	void radioOpen();
	void radioClose();
};
#endif
