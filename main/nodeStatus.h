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
#include "SYSZUXpinyin/syszuxim.h"
#include "SYSZUXpinyin/syszuxpinyin.h"
#include "keyboard/imframe.h"
#include "mylineedit.h"
#include "sql/mater.h"

#include <stdio.h>
#include <QString>
#include <QTableWidgetItem>
#include <QPoint>
#include <QRect>
#include <QTimer>
#include <QWidget>
#include <QWSServer>
#include<QPixmap>
#include <QDesktopWidget>

#define NORMAL 	1
#define WARN	2
#define ERROR	0

class NodeStatus:public QWidget,public Ui_NodeStatus
{
        Q_OBJECT
public :
        NodeStatus(IMFrame *im,QWidget* parent = NULL);
        IMFrame *p_imf;
        static SyszuxIM* imf_my;
        virtual ~NodeStatus();
	void _show(int net,int id,int mod,int stat);
	void fillRow(QLabel *lbl,QLabel *lblStats,int net, int id,int subId,int stat,bool isHave);
    void setCurVal(float *val, int sum);
    void setLblValue(QLabel *lbl, float value, int cora);
    void changeaddr();

	int curNet;
	int curId;
	int curMod;
    int check;
    //static int changeaddr;
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
    void slot_ok();
    void slot_change();
    void txt0Change();
    void txt1Change();
    void txt2Change();
    void txt3Change();
    void txt4Change();
    void txt5Change();
    void txt6Change();
    void txt7Change();
};

#endif
