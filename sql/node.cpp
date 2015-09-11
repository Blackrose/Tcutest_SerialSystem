/*==============================
	节点地址查询
==============================*/
#include "node.h"
#include "main/main.h"
#include "define/define.h"

#include <QSqlQuery>
#include <QString>

QString SqlNode::getAddr(int net,int id,int nodeId)
{	
	QString sql= "select * from node where net= "+QString::number(net)+" and id= "+QString::number(id)+" and subId = "+QString::number(nodeId);
	return Db::getValue(sql,3);
}


