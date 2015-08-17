/*=============================
	 M型节点设置
===============================*/
#ifndef LINLONG_MSET
#define LINLONG_MSET
#include "ui_Mset.h"

#include <QString>
#include <QPoint>
#include <QRect>
#include "keyboard/imframe.h"
#include "module/modList.h"
#include "rxdata.h"
#include "signals.h"
#include <QTimer>
#include <QMessageBox>
#include <time.h>
#include <QTimer>

class  Mset:public QWidget,public Ui_MSetForm
{
        Q_OBJECT
public :
        Mset(IMFrame *im, QWidget* parent=NULL);
	virtual bool eventFilter( QObject * watched, QEvent *event);
        virtual ~Mset();
	void insertSubItem(int count);
    void insertNewSubItem(int flag, int count);
	void cleanData();
	QTimer timer;
	static int nodeParm[16];
private:
    IMFrame *imf;
	int sn;//型号
	//static int nodeParm[16];//参数数据
	int isLorT; // 1＝漏电，2 = 温度 
	static bool isReadData;

public slots:
	void _show();

	void net_currentIndexChanged (int index);//网络改变
	void node_currentIndexChanged (int index);//节点改变
	void subNode_currentIndexChanged (int index);//子节点改变
	void warn_valueChanged ( const QString & text);
	void resetCmd();//重置
	void setParm();//设置
	void delChange(const QString &str);
	void nodeGetParm();//读取parm
	void slot_timer();
};
#endif
