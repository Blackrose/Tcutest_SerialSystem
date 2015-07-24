/*=============================
	脱扣界面
=============================*/

#include "put_off.h"
#include <stdio.h>
#include <QWidget>
#include <QCloseEvent>
PutOff::PutOff(Signals *p_rx,QWidget *parent): QWidget(parent),Ui_PutOffForm()
{
	setupUi(this);
        setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);//窗口没有没有边框  是 一个模太对话框| Qt::FramelessWindowHint
	setGeometry(185,150,270,180);
	connect(btn_close,SIGNAL(clicked()),this,SLOT(hide()));
	connect(btn_ok,SIGNAL(clicked()),this,SLOT(ok()));
	setAttribute(Qt::WA_DeleteOnClose);
	//connect(p_rx, SIGNAL( ansThrOff(int )),this,SLOT( getOk(int )));//复位试验
	connect(cbNet,SIGNAL(currentIndexChanged( const QString &)),SLOT(currentTextCh(const QString &)));
	printf("init PutOff ok\n");
}
void PutOff::_show()
{
	int net = Module::getNet();//-1 没有网络,0 只有 0 网络, 1 只有 1 网络,2 两个网络都有
	if(net == 0){
		cbNet->insertItem(0,"0");
	}
	else if(net == 1){
		cbNet->insertItem(0,"1");
	}
	else if(net == 2){
		cbNet->insertItem(0,"0");
		cbNet->insertItem(1,"1");
	}
	setGeometry(185,150,270,180);
	show();
}
void PutOff::closeEvent ( QCloseEvent * event )
{
	event->ignore(); 
	hide();
}
void PutOff::ok()
{
	int send[1];
	send[0] = cbNode->currentText().toInt();
	if(cbNet->count() > 0 && cbNode->count() > 0){
	}
}
void PutOff::getOk(int i)
{
}
void PutOff::currentTextCh(const QString & text)
{
	int sn;
	int index=0;
	int i=0;
	//写下C型的节点
	cbNode->clear();
    for(i = 0; i < 128 ;i ++)
	{
		sn = Module::getNodeSN( text.toInt(), i);
		if( sn == MC)
		{
			cbNode->insertItem(index,QString::number(i));
			index++;
		}
	}
}
PutOff::~PutOff()
{
	printf("exit PutOff\n");
}
