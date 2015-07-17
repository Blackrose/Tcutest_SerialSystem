/*==============================
	节点地址查询
==============================*/
#ifndef LINLONG_SqlNode
#define LINLONG_SqlNode
#include <QSqlDatabase>
#include <QString>
#include <QSqlQueryModel>
#include "db.h"

class  SqlNode
{
public :
	static QString getAddr(int net,int id,int nodeId);//用户登录
};
#endif
