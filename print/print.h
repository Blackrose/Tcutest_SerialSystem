/*=======================================================
作用：打印信息的封装更好的控制打印机
版本：1.0V
作者：MU
=======================================================*/

#ifndef MU_PRINT
#define MU_PRINT
#include <QString>
#include <QTextCodec>
#include <QTimer>


class Print : public QObject
{
	Q_OBJECT
public:
	static int fd;
	static int fd1;
	static int enable_print;
	static int no_paper;
	static QTimer *timer;
	static Print *point;
	
	static bool init();
	//static void warn(int net,int node,int subNode,int value,char *timer,int size);
	//static void nodeError(int net,int node);
	//static void msg(char *msg,int size);
	/*================================
		作用：打印GB2312汉字
	================================*/
	static int GB2313(QString str);
	/*================================
		作用：清除缓存
	================================*/
	static void clear();
	/*=================================
		作用：打印完走纸
	=================================*/
	static void goPaper();
	/*=================================
		作用：自检
	=================================*/
	static void check();
	/*=================================
		作用：自检状态检查 true or false
	=================================*/
	static int status();
	/*=================================
	作用：温度报警
	=================================*/
	static void Talarm(int net, int device, int reg, int value, QString time);
	/*=================================
	作用：漏电报警
	=================================*/
	static void Calarm(int net, int device, int reg, int value, QString time);
	/*=================================
	作用：本地报警
	=================================*/
	static void Local_alarm(int alarm_type, QString time);
	
private slots:
	static void hanlde(void);
};

#endif
