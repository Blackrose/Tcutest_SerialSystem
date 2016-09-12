/*=============================
	电流曲线设置界面
=============================*/
#include "electric_curve_set.h"

#include <QWidget>
#include <QMessageBox>
#include <time.h>
#include <QColorDialog>
#include <QChar>
#include <QString>
#include <QRgb>

ElectricCurveSet::ElectricCurveSet(QWidget *parent): QWidget(parent),Ui_ElectricCurveSetForm()
{
	setupUi(this);
	//setModal(true);  //对话框
        setWindowFlags(Qt::Dialog);//窗口没有没有边框  是 一个模太对话框Qt::FramelessWindowHint
	setGeometry(125,95,390,290);	
	connect(btn_close,SIGNAL(clicked()),this,SLOT(ElectricCurveSet_close()));
	connect(btn_A,SIGNAL(clicked()),this,SLOT(ElectricCurveSet_btnQuery())); //A 相电流
	connect(btn_B,SIGNAL(clicked()),this,SLOT(ElectricCurveSet_btnQuery())); //B 相电流
	connect(btn_C,SIGNAL(clicked()),this,SLOT(ElectricCurveSet_btnQuery())); //C 相电流
	connect(btn_N,SIGNAL(clicked()),this,SLOT(ElectricCurveSet_btnQuery())); //N 漏电电流

	setAttribute(Qt::WA_DeleteOnClose);
	printf("init ElectriCurveSet ok\n");
}
ElectricCurveSet::~ElectricCurveSet()
{
	printf("exit ElectriCurveSet\n");
}
void ElectricCurveSet::ElectricCurveSet_close()
{
	close();
}
void ElectricCurveSet::ElectricCurveSet_btnQuery()
{
	QPushButton* btn=qobject_cast<QPushButton*>(sender());
	QRgb rgb=QColorDialog::getRgba();

	int b=qBlue(rgb);
	int g=qGreen(rgb);
	int r=qRed(rgb);
	char crgb[50];
	sprintf(crgb,"background-color:rgb(%d,%d,%d);",r,g,b);
	if(btn == btn_A)
	{
		lbl_A->setStyleSheet(QString::fromUtf8(crgb));
	}
	else if(btn == btn_B)
	{
		lbl_B->setStyleSheet(QString::fromUtf8(crgb));
	}
	else if(btn == btn_C)
	{
		lbl_C->setStyleSheet(QString::fromUtf8(crgb));
	}
	else if(btn == btn_N)
	{
		lbl_N->setStyleSheet(QString::fromUtf8(crgb));
	}
}
