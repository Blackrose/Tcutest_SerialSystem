#ifndef LINLONG_MODLINS
#define LINLONG_MODLINS

#include <QString>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include "pake.h"
#include "rxdata.h"
#include "sql/db.h"
#include <QDateTime>

#define TIME (18)
#define MODCOUNT 220
#define SUBNODECOUNT 8

#define NORMAL 	1
#define WARN	2
#define ERROR	0

#define NO_SN	0x00

#define MC  	0x01
#define ML1     0x02
#define MT1     0x03
#define ML1T1   0x04
#define ML2     0x05
#define MT2     0x06
#define ML2T2   0x07
#define ML4     0x08
#define MT4     0x09
#define ML4T4	0x0A
#define ML8     0x0B
#define MT8     0x0C
#define DL1T1   0x0D

struct myTime
{
	char time[50];
};
struct mod
{
	bool isHave;//是否有这一个设备 false 没有 ,true 有
	bool isReset;//是否需要复位
	int sn;//产品型号 0 没有注册型号
	int flag;// 0 掉线  1 正常 2 预警 3 报警
	int subNodIsWar[SUBNODECOUNT];//子节点状态
	struct myTime subNodTimer[SUBNODECOUNT];//报警时间
	int subNodValue[SUBNODECOUNT];//报警数值
    int recovery[SUBNODECOUNT];//恢复
};
/*========================
 型号结构体
========================*/
struct nodeModName
{
	char name[40];
};
class Module
{
public:
	int net0All ;
	int net1All ;
	
	Module();
	virtual ~Module();
	void unreg(int net,int id);//注销
	int warnCount(int net); //返回指定网络报警的数量
	int errorCount(); //故障总数
	int warnCount(); //报警总算
	int nodeCount(int net);//返回节点数
	int getNodeStats(int net,int id); //返回节点的状态 
	static int s_getNodeStats(int net,int id);//返回节点的状态 
	/*================================================
		功能：清除报警
		net: 网络号
		id：节点号
	================================================*/
	void cleWarn(int net,int id);
	void cleSubWarn(int net,int id);
	/*================================================
		功能：写下子节点状态
		net: 网络号 id：节点号 subId:子节点 
		w：状态 （ 1:正常) (2:预警) (3:报警)
	================================================*/
	void setSubWarn(int net,int id,int subId,int flag,int value);
	/*====================================
		功能：返回节点是否报警；
		net：网络号；
		id：节点号；
		subId：子节点号；
	=====================================*/
	static bool getSubWarn(int net, int id , int subId);


	void setSubError(int net, int id, int subId, int flag);
	static bool getSubError(int net, int id, int subId);

    /*====================================
        功能：返回节点是否恢复故障；
        net：网络号；
        id：节点号；
        subId：子节点号；
    =====================================*/
    static bool getSubErrorRecovery(int net, int id, int subId);

	/*====================================
		功能：返回节点的报警信息；
		net：网络号；
		id：节点号；
		subId：子节点号；
		time：传递报警时间的参数；
		value：报警的数值；
	=====================================*/
	static void getWarnTimeAndVal(int net,int id,int subId,char** time,int* value);
	/*====================================
		功能：注册型号；
		net：网络号；
		id：节点号；
		sn：型号代码；
	=====================================*/
	bool regSN(int net,int id,int sn);
	/*====================================
		功能：返回报警的类型；
		net：网络号；
		id：节点号；
		subId：子节点号；
		返回值：0 ＝ 温度；1＝电流；2＝漏电
	=====================================*/
	int  getWhatWarn(int net,int id,int subId);

    /*====================================
        功能：返回故障的类型；
        net：网络号；
        id：节点号；
        subId：子节点号；
        返回值：0 ＝ 温度；1＝电流；2＝漏电
    =====================================*/
    int  getWhatErr(int net,int id,int subId);

	/*====================================
		功能：打印节点的信息；
	=====================================*/
	void display(int net,int id);
	/*====================================
		功能：返回节点上线或是故障
		         后是否复位过；
		返回值：ture 是；false 不是
	=====================================*/
	bool getIsReset(int net, int id);
	/*====================================
		功能：写下节点的复位
		net：网络号；
		id：节点号；
		val：true = 是；false＝不是；
	=====================================*/
	void setIsReset(int net, int id,bool val);
	//返回节点型号
	int getSN(int net,int id);
public:
	static int getNet();//-1 没有网络,0 只有 0 网络, 1 只有 1 网络,2 两个网络都有
	static int getNodeSN(int net,int id);//返回sn地址
	struct mod* getNode(int net,int id);//返回指定的节点
	static bool nodeIsHave(int net, int id);//是否有节点
	static struct nodeModName *moTyp;
private:
	static struct mod* mod_list;
	//int sum;
};
#endif
