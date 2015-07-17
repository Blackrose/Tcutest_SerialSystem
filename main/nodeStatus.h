/*======================================
	功能：显示节点的状态，报警、故障、
	          正常显示。记录报警故障信息。
	          时间 、 数值等。
	文件名：nodeStatus.h
=======================================*/

#ifndef LINLONG_nodeStatus
#define LINLONG_nodeStatus

#include "ui_nodeStatus.h"
#include "bell.h"
#include "power.h"
#include "led.h"
#include "sql/optMsg.h"
#include "modList.h"
#include "rxdata.h"
#include "signals.h"

#include <stdio.h>
#include <QString>
#include <QTableWidgetItem>
#include <QPoint>
#include <QRect>
#include <QTimer>
#include <QWidget>

#define NORMAL 	1
#define WARN	2
#define ERROR	0

class NodeStatus:public QWidget,public Ui_NodeStatus
{
        Q_OBJECT
public :
        NodeStatus(QWidget* parent = NULL);
        virtual ~NodeStatus();
	void _show(int net,int id,int mod,int stat);
	void fillRow(QLabel *lbl,QLabel *lblStats,int net, int id,int subId,int stat,bool isHave);
	void setCurVal(int* val,int sum);
	void setLblValue(QLabel *lbl,int value, int cora);

	int curNet;
	int curId;
	int curMod;
	int check;
private:
	void nodeWarn(QLabel *lbl);
	void nodeError(QLabel *lbl);
	void nodeNormal(QLabel *lbl);
    void nodeUnable(QLabel *lbl);
 	QWidget *par;
public slots:
	void slot_reset();
	void slot_try();
	void slot_hide();
	void slot_clear();
};

#endif
