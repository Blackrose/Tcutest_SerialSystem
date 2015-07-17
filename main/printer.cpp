/*=============================
	打印设置界面
=============================*/
#include "printer.h"
#include "print.h"


Printer::Printer(QWidget *parent) : QWidget(parent), Ui_PrinterForm()
{
	setupUi(this);
	par = parent;
	setWindowFlags(Qt::Dialog
		| Qt::WindowCloseButtonHint);//窗口没有没有边框  是 一个模太对话框
	if (Print::enable_print == 1)
		radiobutton_open->setChecked(true);
	else if (Print::enable_print == 0)
		radiobutton_close->setChecked(true);
	connect(btn_close, SIGNAL(clicked()), this, SLOT(hide()));
	connect(radiobutton_open, SIGNAL(toggled(bool)), this, SLOT(radioOpen()));
	connect(radiobutton_close, SIGNAL(toggled(bool)), this, SLOT(radioClose()));
	setAttribute(Qt::WA_DeleteOnClose);
	printf("init Printer ok\n");
}
void Printer::closeEvent ( QCloseEvent * event )
{
	event->ignore(); 
	hide();
}
Printer::~Printer()
{
	printf("exit Printer\n");
}
void Printer::_show()
{	
	show();
	setGeometry(185, 145, 290, 190);
}
//void Printer::ch()
//{
//	Main::whoChePwd=6;
//	((Main*)par)->check_pwd();
//}

void Printer::radioOpen()
{
	if (radiobutton_open->isChecked())
		Print::enable_print = 1;
}

void Printer::radioClose()
{
	if (radiobutton_close->isChecked())
		Print::enable_print = 0;
}
