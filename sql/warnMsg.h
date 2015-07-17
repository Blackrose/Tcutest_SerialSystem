//属性参数设置
#ifndef LINLONG_WARNMSG
#define LINLONG_WARNMSG

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <stdio.h>
#include <QObject>
#include <QSqlQueryModel>

#include "db.h"



class WarnMsg
{
public:
	static int insert(int netId,int nodeId,int subNodeId,int warn,int value);
	static int insertNodeDo(int netId, int nodeId, int wDo);
	static void getTable(QString time_bg,QString timer_end, int net,int id, int subId, int big , QSqlQueryModel *model);
	static int getCount(QString time_bg,QString timer_end, int net,int id, int subId);
	static bool delAll();
	
	static void insertCAlarm(int netId,int nodeId,int subNodeId,int value);//电流报警
	static void insertTAlarm(int netId,int nodeId,int subNodeId,int value);//温度报警
	static void insertMAlarm(int netId,int nodeId,int subNodeId,int value);//漏电报警
    static void insertTError(int netId, int nodeId, int subNodeId);//温度故障
    static void insertCError(int netId, int nodeId, int subNodeId);//漏电故障
    static void insertTrestore(int netId, int nodeId, int subNodeId);//温度故障恢复
    static void insertCrestore(int netId, int nodeId, int subNodeId);//漏电故障恢复
	static void insertSubError(int netId, int nodeId, int subNodeId);
	static void insertEAlarm(int netId,int nodeId);//模块故障报警
	static void insertNodeSet(int netId,int nodeId);//设置节点
	static void insertNodeCut(int netId,int nodeId);//脱扣节点
	static void insertNodeReset(int netId,int nodeId);//复位节点
	static void insertNodeRemove(int netId,int nodeId);//注销节点

	static void insertMainNo();//主电欠压
	static void insertPreMainNo();//备电欠压
	static void insertPreMainOn();//备电短路
	static void insertPreMainOff();//备电断路

	static void insertMainOk();//主电正常
	static void insertPreMainOk();//备电正常
};
#endif
