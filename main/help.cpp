/*=============================
	帮助界面
=============================*/
#include "help.h"

Help::Help(QWidget *parent) : QWidget(parent), Ui_HelpForm()
{
	setupUi(this);
	par = parent;
	setWindowFlags(Qt::Dialog
		| Qt::WindowCloseButtonHint);//窗口没有没有边框  是 一个模太对话框
	connect(btn_close,SIGNAL(clicked()),this,SLOT(hide()));
	setAttribute(Qt::WA_DeleteOnClose);
	printf("init Help ok\n");
}
void Help::closeEvent ( QCloseEvent * event )
{
	event->ignore(); 
	hide();
}
Help::~Help()
{
	printf("exit Help\n");
}
void Help::_show()
{	
	show();
	setGeometry(185, 145, 290, 190);
}

