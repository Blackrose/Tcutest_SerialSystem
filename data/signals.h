#ifndef LINLONG_signals_LIN
#define LINLONG_signals_LIN

#include <QObject>
#include "pake.h"
#include "modList.h"
#include "rxdata.h"
//#include "main.h"
class Signals
{
public:
    static unsigned int errorFlag;
    static unsigned int Flagerror[2];
        static int netCount[2];//网络总节点数
	int  netCurId[2] ;//网络当前节点
	int netTimer[2];//网络从发次数
	static int timer;//最多从发次数
	int insertTimer;//插入发送包的重发
	bool isRun;
	unsigned int sendData[100];
	Signals();
	void send();
	void doNet(int net);
	void sendNet(int net);
	void doInsert();
	void sendInsert();
	
	void toDo();
	QObject *p_main;
    //QObject *p_putOff;
	QObject *p_nodeStatus;
	QObject *p_Mset;
	struct  mod* mo;
	struct pake *pak;
//	Module *module;
//	int warn_flag;
	int si_i;
};
#endif
