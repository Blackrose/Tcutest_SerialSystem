//属性参数设置
#include "warnMsg.h"
#include <QVariant>
#include <QMessageBox>
#include "modList.h"
#include "print.h"
#include "pic/pic_communication.h"

static int flagdelete = 0;

int WarnMsg::insert(int netId,int nodeId,int subNodeId,int warn,int value)
{//插入节点
	int sn = Module::getNodeSN( netId, nodeId);
	QString strSubId = QString::number(subNodeId);
	QString dan;
	QString time_str = Db::newTime();
	if(warn == T_ALARM)
	{
		PicProtocol::pic_t_alarm(netId, nodeId, subNodeId, time_str);
		dan = "℃";
		Print::Talarm(netId, nodeId, subNodeId, value, time_str);
	}
	else
	{
		PicProtocol::pic_c_alarm(netId, nodeId, subNodeId, time_str);
		dan = "mA";
		Print::Calarm(netId, nodeId, subNodeId, value, time_str);
	}
	QString sql = "select count(*) from WarnMsg";
    if( Db::selectCount(sql) > SQLMAX)
	{
        //sql = "delete from WarnMsg where id >'1' and id < "+ (Db::selectCount(sql) - SQLMAX + 1) +"'";
        return 0;
	}
	sql = "insert into WarnMsg values(NULL,'"+QString::number(netId)+"','"+
			QString::number(nodeId)+"','"+strSubId+"','"+QString::number(warn)+"','"+
			QString::number(value)+dan+"','"+time_str+"');";
	return Db::IDUdb(sql);
}
void WarnMsg::insertMainNo()//主电欠压
{
	QString sql = "select count(*) from WarnMsg";
	QString time_str = Db::newTime();

	PicProtocol::pic_main_error(time_str);
	Print::Local_alarm(MAIN_NO, time_str);
    if( Db::selectCount(sql) > SQLMAX)
	{
		return;
	}
	sql = "insert into WarnMsg values(NULL,' ',' ',' ','"+QString::number(MAIN_NO)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);
}
void WarnMsg::insertPreMainNo()//备电欠压
{
	QString sql = "select count(*) from WarnMsg";
        QString time_str = Db::newTime();

        PicProtocol::pic_premain_error(time_str);
	Print::Local_alarm(PREMAIN_NO, time_str);
    if( Db::selectCount(sql) > SQLMAX)
	{
		return ;
	}
	sql = "insert into WarnMsg values(NULL,' ',' ',' ','"+QString::number(PREMAIN_NO)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);
}
void WarnMsg::insertMainOk()//主电正常
{
	QString sql = "select count(*) from WarnMsg";
        QString time_str = Db::newTime();

        PicProtocol::pic_main_restore(time_str);
    if( Db::selectCount(sql) > SQLMAX)
	{
		return;
	}
	sql = "insert into WarnMsg values(NULL,' ',' ',' ','"+QString::number(MAIN_OK)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);
}
void WarnMsg::insertPreMainOk()//备电正常
{
	QString sql = "select count(*) from WarnMsg";
        QString time_str = Db::newTime();

        PicProtocol::pic_premain_restore(time_str);
    if( Db::selectCount(sql) > SQLMAX)
	{
		return;
	}
	sql = "insert into WarnMsg values(NULL,' ',' ',' ','"+QString::number(PREMAIN_OK)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);
}
void WarnMsg::insertPreMainOn()//备电短路
{
	QString sql = "select count(*) from WarnMsg";
        QString time_str = Db::newTime();

        PicProtocol::pic_premain_error(time_str);
	Print::Local_alarm(PREMAIN_ON, time_str);
    if( Db::selectCount(sql) > SQLMAX)
	{
		return;
	}
	sql = "insert into WarnMsg values(NULL,' ',' ',' ','"+QString::number(PREMAIN_ON)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);
}
void WarnMsg::insertPreMainOff()//备电断路
{
	QString sql = "select count(*) from WarnMsg";
        QString time_str = Db::newTime();

	PicProtocol::pic_premain_error(time_str);
        Print::Local_alarm(PREMAIN_OFF, time_str);
    if( Db::selectCount(sql) > SQLMAX)
	{
		return;
	}
	sql = "insert into WarnMsg values(NULL,' ',' ',' ','"+QString::number(PREMAIN_OFF)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);
}
void WarnMsg::insertCAlarm(int netId,int nodeId,int subNodeId,int value)//电流报警
{
	WarnMsg::insert( netId, nodeId, subNodeId, C_ALARM, value);
}
void WarnMsg::insertTAlarm(int netId,int nodeId,int subNodeId,int value)//温度报警
{
	WarnMsg::insert( netId, nodeId, subNodeId, T_ALARM, value);
}
void WarnMsg::insertMAlarm(int netId,int nodeId,int subNodeId,int value)//漏电报警
{
	WarnMsg::insert( netId, nodeId, subNodeId, M_ALARM, value);
}

void WarnMsg::insertTError(int netId, int nodeId, int subNodeId)//温度故障
{printf("enter insertTError\n");
    //int sn = Module::getNodeSN( netId, nodeId);
    QString strSubId = QString::number(subNodeId);
    int warn = SUB_ERROR;
    int value = 0;

        QString time_str = Db::newTime();

        PicProtocol::pic_t_error(netId, nodeId, subNodeId, time_str);//温度故障
        //PicProtocol::pic_t_restore(netId, nodeId, subNodeId, time_str);
    QString sql = "select count(*) from ErrMsg";
    if( Db::selectCount(sql) > SQLMAXDATA)//SQLMAX
    {
        printf("insertTError Db::selectCount(sql)===%d\n",Db::selectCount(sql));
        sql = "delete from ErrMsg where id between '"+ QString::number(1) +"' and '"+ QString::number(Db::selectCount(sql) - SQLMAXDATA) +"'";
        if(Db::IDUdb(sql)){printf("insertTError\n");}
        //return;
    }
    //QString sql1 = "select count(*) from ErrMsg";
//    sql = "insert into WarnMsg values(NULL,'"+QString::number(netId)+"','"+
//            QString::number(nodeId)+"','"+strSubId+"','"+QString::number(warn)+"','"+
//            QString::number(value)+"','"+time_str+"');";
    sql = "insert into ErrMsg values(NULL,'"+QString::number(netId)+"','"+
            QString::number(nodeId)+"','"+strSubId+"','"+QString::number(warn)+"','"+
            QString::number(value)+"','"+time_str+"');";
    Db::IDUdb(sql);
}
void WarnMsg::insertCError(int netId, int nodeId, int subNodeId)//漏电故障
{printf("enter insertCError\n");
    //int sn = Module::getNodeSN( netId, nodeId);
    QString strSubId = QString::number(subNodeId);
    int warn = SUB_ERROR;
    int value = 0;

        QString time_str = Db::newTime();

        PicProtocol::pic_c_error(netId, nodeId, subNodeId, time_str);//漏电故障
        //PicProtocol::pic_c_restore(netId, nodeId, subNodeId, time_str);
    QString sql = "select count(*) from ErrMsg";
    if( Db::selectCount(sql) > SQLMAXDATA)//SQLMAX
    {
        printf("insertCError Db::selectCount(sql)===%d\n",Db::selectCount(sql));
        sql = "delete from ErrMsg where id between '"+ QString::number(1) +"' and '"+ QString::number(Db::selectCount(sql) - SQLMAXDATA) +"'";

        if(Db::IDUdb(sql)){printf("insertCError\n");}
        //return;
    }
    //QString sql1 = "select count(*) from ErrMsg";
//    sql = "insert into WarnMsg values(NULL,'"+QString::number(netId)+"','"+
//            QString::number(nodeId)+"','"+strSubId+"','"+QString::number(warn)+"','"+
//            QString::number(value)+"','"+time_str+"');";
    sql = "insert into ErrMsg values(NULL,'"+QString::number(netId)+"','"+
            QString::number(nodeId)+"','"+strSubId+"','"+QString::number(warn)+"','"+
            QString::number(value)+"','"+time_str+"');";
    Db::IDUdb(sql);
}

void WarnMsg::insertCrestore(int netId, int nodeId, int subNodeId)//漏电故障恢复
{    
    QString time_str = Db::newTime();
    PicProtocol::pic_c_restore(netId, nodeId, subNodeId, time_str);//漏电故障
}

void WarnMsg::insertTrestore(int netId, int nodeId, int subNodeId)//温度故障恢复
{
    QString time_str = Db::newTime();
    PicProtocol::pic_t_restore(netId, nodeId, subNodeId, time_str);//温度故障
}

void WarnMsg::insertSubError(int netId, int nodeId, int subNodeId)
{
    //int sn = Module::getNodeSN( netId, nodeId);
	QString strSubId = QString::number(subNodeId);
	int warn = SUB_ERROR;
	int value = 0;

        QString time_str = Db::newTime();

        //PicProtocol::pic_channel_error(netId, nodeId, subNodeId, time_str);//通道故障
	QString sql = "select count(*) from WarnMsg";
    if( Db::selectCount(sql) > SQLMAX)
	{
		return;
	}
	sql = "insert into WarnMsg values(NULL,'"+QString::number(netId)+"','"+
			QString::number(nodeId)+"','"+strSubId+"','"+QString::number(warn)+"','"+
			QString::number(value)+"','"+time_str+"');";
	Db::IDUdb(sql);
}

int WarnMsg::insertNodeDo(int netId, int nodeId, int wDo)
{
    QString sql = "select count(*) from ErrMsg";
        QString time_str = Db::newTime();
	
    //if (wDo == E_ALARM)
            //PicProtocol::pic_communication_error(netId, nodeId, 99, time_str);//故障
            //PicProtocol::pic_channel_error(netId, nodeId, subNodeId, time_str);//通道故障    
    if( Db::selectCount(sql) >= SQLMAXDATA)//SQLMAX
    {
        printf("insertNodeDo Db::selectCount(sql)===%d\n",Db::selectCount(sql));
        //sql = "delete from ErrMsg where id between '"+ QString::number(1) +"' and '"+ QString::number(Db::selectCount(sql) - SQLMAXDATA) +"'";
        //sql = "delete from ErrMsg where id = '"+ QString::number(Db::selectCount(sql) - SQLMAXDATA) +"'";
        sql = "delete from ErrMsg where id = '"+ QString::number(++flagdelete) +"'";
        //sql = "delete from ErrMsg limit 1";

        if(Db::IDUdb(sql)){printf("insertNodeDo ok\n");}
        //return;
    }
    sql = "select count(*) from ErrMsg";
    printf("insertNodeDo 222222222222222Db::selectCount(sql)===%d\n",Db::selectCount(sql));
//	sql = "insert into WarnMsg values(NULL,'"+QString::number(netId)+"','"+
//			QString::number(nodeId)+"',' ','"+QString::number(wDo)+"',' ','"+time_str+"');";
    sql = "insert into ErrMsg values(NULL,'"+QString::number(netId)+"','"+
            QString::number(nodeId)+"',' ','"+QString::number(wDo)+"',' ','"+time_str+"');";
	return Db::IDUdb(sql);
}
//模块故障报警
void WarnMsg::insertEAlarm(int netId,int nodeId)
{
	WarnMsg::insertNodeDo( netId, nodeId,  E_ALARM);
}
//设置节点
void WarnMsg::insertNodeSet(int netId,int nodeId)
{
	WarnMsg::insertNodeDo( netId, nodeId, NODE_SET);
}
//脱扣节点
void WarnMsg::insertNodeCut(int netId,int nodeId)
{
	WarnMsg::insertNodeDo( netId, nodeId, NODE_CUT);
}
//复位节点
void WarnMsg::insertNodeReset(int netId,int nodeId)
{
	WarnMsg::insertNodeDo( netId, nodeId, NODE_RESET);
}
//注销节点
void WarnMsg::insertNodeRemove(int netId,int nodeId)
{
	WarnMsg::insertNodeDo( netId, nodeId, NODE_REMOVE);
}
void WarnMsg::getTable(QString time_bg,QString timer_end, int net,int id, int subId, int big , QSqlQueryModel *model)
{
	QString sql="select * from warnmsg where  _warntime > '"+time_bg+"' and _warntime <'"+timer_end+"'";
	if( net != ALL)
	{
		sql += " and NetId = '"+QString::number(net)+"'";		
	}
	if(id != ALL)
	{
		sql += " and NodeId = '"+QString::number(id)+"'";	
	}
	if(subId != ALL)
	{
		sql += " and SubNodeId = '"+QString::number(subId)+"'";
	}
	sql += " ORDER BY id DESC limit 9 offset "+ QString::number(big);
	Db::fillModel(sql,model);
}

void WarnMsg::geterrTable(QString time_bg,QString timer_end, int net,int id, int subId, int big , QSqlQueryModel *model)
{
    QString sql="select * from errmsg where  _warntime > '"+time_bg+"' and _warntime <'"+timer_end+"'";
    if( net != ALL)
    {
        sql += " and NetId = '"+QString::number(net)+"'";
    }
    if(id != ALL)
    {
        sql += " and NodeId = '"+QString::number(id)+"'";
    }
    if(subId != ALL)
    {
        sql += " and SubNodeId = '"+QString::number(subId)+"'";
    }
    sql += " ORDER BY id DESC limit 9 offset "+ QString::number(big);
    Db::fillModel(sql,model);
}

int WarnMsg::getCount(QString time_bg,QString timer_end,int net,int id, int subId)
{
	QString sql = "select count(*) from warnmsg where  _warntime > '"+ time_bg +"' and _warntime <'"+timer_end+"'";
	if( net != ALL)
	{
		sql += " and NetId = '"+QString::number(net)+"'";		
	}
	if(id != ALL)
	{
		sql += " and NodeId = '"+QString::number(id)+"'";	
	}
	if(subId != ALL)
	{
		sql += " and SubNodeId = '"+QString::number(subId)+"'";
	}
	return Db::selectCount(sql);
}
int WarnMsg::geterrCount(QString time_bg,QString timer_end,int net,int id, int subId)
{
    QString sql = "select count(*) from errmsg where  _warntime > '"+ time_bg +"' and _warntime <'"+timer_end+"'";
    if( net != ALL)
    {
        sql += " and NetId = '"+QString::number(net)+"'";
    }
    if(id != ALL)
    {
        sql += " and NodeId = '"+QString::number(id)+"'";
    }
    if(subId != ALL)
    {
        sql += " and SubNodeId = '"+QString::number(subId)+"'";
    }
    return Db::selectCount(sql);
}
bool WarnMsg::delAll()
{
	QString sql= "delete from warnmsg";
	return Db::IDUdb(sql);
}

bool WarnMsg::delerrAll()
{
    QString sql= "delete from errmsg";
    return Db::IDUdb(sql);
}
