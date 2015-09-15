//属性参数设置
#include "warnMsg.h"
#include <QVariant>
#include <QMessageBox>
#include "modList.h"
#include "print.h"
#include "pic/pic_communication.h"
#include "main/main.h"
#include "mater.h"

static int flagerrdelete = 0;
static int flagwarndelete = 0;
static int flagnowerrdelete = 0;
static int flagnowwarndelete = 0;


int WarnMsg::insert(int netId, int nodeId, int subNodeId, int warn, float value)
{//插入节点
	int sn = Module::getNodeSN( netId, nodeId);
	QString strSubId = QString::number(subNodeId);
	QString dan;
    QString addr = Mater::readaddress(netId,nodeId,subNodeId);
	QString time_str = Db::newTime();
    Main::flagreset = 1;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
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
    Main::flagreset = 0;

	QString sql = "select count(*) from WarnMsg";
    if( Db::selectCount(sql) >= SQLMAXDATA)
	{
        sql = "delete from WarnMsg where id = '"+ QString::number(++flagwarndelete) +"'";
        Db::IDUdb(sql);
        //return 0;
    }
	sql = "insert into WarnMsg values(NULL,'"+QString::number(netId)+"','"+
			QString::number(nodeId)+"','"+strSubId+"','"+QString::number(warn)+"','"+
            QString::number(value)+dan+"','"+time_str+"', '"+addr+"');";
	return Db::IDUdb(sql);
}

int WarnMsg::insertnow(int netId,int nodeId,int subNodeId,int warn,float value)
{//插入节点    
    QString dan;
    QString addr = Mater::readaddress(netId,nodeId,subNodeId);
    QString time_str = Db::newTime();
    Main::flagreset = 1;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    if(warn == T_ALARM)
    {
        dan = "℃";
    }
    else
    {
        dan = "mA";
    }
    Main::flagreset = 0;

    QString sql = "select count(*) from WarnNowMsg";
    if( Db::selectCount(sql) >= SQLMAXDATA)
    {
        sql = "delete from WarnNowMsg where id = '"+ QString::number(++flagnowwarndelete) +"'";
        Db::IDUdb(sql);
        //return 0;
    }
    sql = "delete from WarnNowMsg where netid = '"+ QString::number(netId) +"' \
                                    and nodeid = '"+ QString::number(nodeId) +"' \
                                    and subnodeid = '"+ QString::number(subNodeId) +"'";
    Db::IDUdb(sql);//删除报警记录中的报警

    sql = "delete from ErrNowMsg where netid = '"+ QString::number(netId) +"' \
                                    and nodeid = '"+ QString::number(nodeId) +"' \
                                    and subnodeid = '"+ QString::number(subNodeId) +"'";
    Db::IDUdb(sql);//删除故障记录中的故障报警

    sql = "delete from ErrNowMsg where netid = '"+ QString::number(netId) +"' \
                                    and nodeid = '"+ QString::number(nodeId) +"' \
                                    and typeid = '"+ QString::number(E_ALARM) +"'";
    Db::IDUdb(sql);//删除故障报警记录中的模块故障


    sql = "insert into WarnNowMsg values(NULL,'"+QString::number(netId)+"',\
                                                '"+QString::number(nodeId)+"',\
                                                  '"+QString::number(subNodeId)+"',\
                                                    '"+QString::number(warn)+"',\
                                                     '"+QString::number(value)+dan+"',\
                                                       '"+time_str+"',\
                                                          '"+addr+"'); ";
    printf("enter insertnow\n");
    return Db::IDUdb(sql);
}

void WarnMsg::insertMainNo()//主电欠压
{
    QString sql = "select count(*) from ErrMsg";
	QString time_str = Db::newTime();

	PicProtocol::pic_main_error(time_str);
	Print::Local_alarm(MAIN_NO, time_str);
    if( Db::selectCount(sql) > SQLMAXDATA)
	{
        sql = "delete from ErrMsg where id = '"+ QString::number(++flagerrdelete) +"'";
        Db::IDUdb(sql);
        //return;
	}
    sql = "insert into ErrMsg values(NULL,' ',' ',' ','"+QString::number(MAIN_NO)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);

    sql = "select count(*) from ErrNowMsg";
    if( Db::selectCount(sql) > SQLMAXDATA)
    {
        sql = "delete from ErrNowMsg where id = '"+ QString::number(++flagnowerrdelete) +"'";
        Db::IDUdb(sql);
    }
    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(MAIN_NO) +"'";
    Db::IDUdb(sql);

    sql = "insert into ErrNowMsg values(NULL,' ',' ',' ','"+QString::number(MAIN_NO)+"',' ','"+time_str+"');";
    Db::IDUdb(sql);

}
void WarnMsg::insertPreMainNo()//备电欠压
{
    QString sql = "select count(*) from ErrMsg";
        QString time_str = Db::newTime();

        PicProtocol::pic_premain_error(time_str);
	Print::Local_alarm(PREMAIN_NO, time_str);
    if( Db::selectCount(sql) >= SQLMAXDATA)
    {
        sql = "delete from ErrMsg where id = '"+ QString::number(++flagerrdelete) +"'";
        Db::IDUdb(sql);
        //return ;
	}
    sql = "insert into ErrMsg values(NULL,' ',' ',' ','"+QString::number(PREMAIN_NO)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);

    sql = "select count(*) from ErrNowMsg";
    if( Db::selectCount(sql) >= SQLMAXDATA)
    {
        sql = "delete from ErrNowMsg where id = '"+ QString::number(++flagnowerrdelete) +"'";
        Db::IDUdb(sql);
    }
    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_NO) +"'";
    Db::IDUdb(sql);

    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_ON) +"'";
    Db::IDUdb(sql);

    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_OFF) +"'";
    Db::IDUdb(sql);

    sql = "insert into ErrNowMsg values(NULL,' ',' ',' ','"+QString::number(PREMAIN_NO)+"',' ','"+time_str+"');";
    Db::IDUdb(sql);

}
void WarnMsg::insertMainOk()//主电正常
{
	QString sql = "select count(*) from WarnMsg";
        QString time_str = Db::newTime();

        PicProtocol::pic_main_restore(time_str);
    if( Db::selectCount(sql) >= SQLMAXDATA)
	{
        sql = "delete from WarnMsg where id = '"+ QString::number(++flagwarndelete) +"'";
        Db::IDUdb(sql);
        //return;
	}
	sql = "insert into WarnMsg values(NULL,' ',' ',' ','"+QString::number(MAIN_OK)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);

    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(MAIN_NO) +"'";
    Db::IDUdb(sql);
}
void WarnMsg::insertPreMainOk()//备电正常
{
	QString sql = "select count(*) from WarnMsg";
        QString time_str = Db::newTime();

        PicProtocol::pic_premain_restore(time_str);
    if( Db::selectCount(sql) >= SQLMAXDATA)
	{
        sql = "delete from WarnMsg where id = '"+ QString::number(++flagwarndelete) +"'";
        Db::IDUdb(sql);
        //return;
	}
	sql = "insert into WarnMsg values(NULL,' ',' ',' ','"+QString::number(PREMAIN_OK)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);

    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_NO) +"'";
    Db::IDUdb(sql);

    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_ON) +"'";
    Db::IDUdb(sql);

    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_OFF) +"'";
    Db::IDUdb(sql);
}
void WarnMsg::insertPreMainOn()//备电短路
{
    QString sql = "select count(*) from ErrMsg";
        QString time_str = Db::newTime();

        PicProtocol::pic_premain_error(time_str);
	Print::Local_alarm(PREMAIN_ON, time_str);
    if( Db::selectCount(sql) >= SQLMAXDATA)
	{
        sql = "delete from ErrMsg where id = '"+ QString::number(++flagerrdelete) +"'";
        Db::IDUdb(sql);//return;
	}
    sql = "insert into ErrMsg values(NULL,' ',' ',' ','"+QString::number(PREMAIN_ON)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);

    sql = "select count(*) from ErrNowMsg";
    if( Db::selectCount(sql) >= SQLMAXDATA)
    {
        sql = "delete from ErrNowMsg where id = '"+ QString::number(++flagnowerrdelete) +"'";
        Db::IDUdb(sql);
    }
    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_ON) +"'";
    Db::IDUdb(sql);

    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_NO) +"'";
    Db::IDUdb(sql);

    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_OFF) +"'";
    Db::IDUdb(sql);

    sql = "insert into ErrNowMsg values(NULL,' ',' ',' ','"+QString::number(PREMAIN_ON)+"',' ','"+time_str+"');";
    Db::IDUdb(sql);

}
void WarnMsg::insertPreMainOff()//备电断路
{
    QString sql = "select count(*) from ErrMsg";
        QString time_str = Db::newTime();

	PicProtocol::pic_premain_error(time_str);
        Print::Local_alarm(PREMAIN_OFF, time_str);
    if( Db::selectCount(sql) >= SQLMAXDATA)
	{
        sql = "delete from ErrMsg where id = '"+ QString::number(++flagerrdelete) +"'";
        Db::IDUdb(sql);//return;
	}
    sql = "insert into ErrMsg values(NULL,' ',' ',' ','"+QString::number(PREMAIN_OFF)+"',' ','"+time_str+"');";
	Db::IDUdb(sql);

    sql = "select count(*) from ErrNowMsg";
    if( Db::selectCount(sql) >= SQLMAXDATA)
    {
        sql = "delete from ErrNowMsg where id = '"+ QString::number(++flagnowerrdelete) +"'";
        Db::IDUdb(sql);
    }
    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_OFF) +"'";
    Db::IDUdb(sql);

    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_NO) +"'";
    Db::IDUdb(sql);

    sql = "delete from ErrNowMsg where typeid = '"+ QString::number(PREMAIN_ON) +"'";
    Db::IDUdb(sql);

    sql = "insert into ErrNowMsg values(NULL,' ',' ',' ','"+QString::number(PREMAIN_OFF)+"',' ','"+time_str+"');";
    Db::IDUdb(sql);

}
void WarnMsg::insertCAlarm(int netId,int nodeId,int subNodeId,int value)//电流报警
{
	WarnMsg::insert( netId, nodeId, subNodeId, C_ALARM, value);
}
void WarnMsg::insertTAlarm(int netId,int nodeId,int subNodeId,float value)//温度报警
{printf("enter insertTAlarm\n");
	WarnMsg::insert( netId, nodeId, subNodeId, T_ALARM, value);
    WarnMsg::insertnow( netId, nodeId, subNodeId, T_ALARM, value);
}
void WarnMsg::insertMAlarm(int netId, int nodeId, int subNodeId, float value)//漏电报警
{//printf("enter insertMAlarm\n");
	WarnMsg::insert( netId, nodeId, subNodeId, M_ALARM, value);
    WarnMsg::insertnow( netId, nodeId, subNodeId, M_ALARM, value);
}

void WarnMsg::insertNowTorCError(int netId, int nodeId, int subNodeId)//温度漏电故障
{
    int warn = SUB_ERROR;
    int value = 0;
    QString time_str = Db::newTime();
    QString addr = Mater::readaddress(netId,nodeId,subNodeId);
    QString sql = "select count(*) from ErrNowMsg";

    if( Db::selectCount(sql) >= SQLMAXDATA)//SQLMAX
    {
        sql = "delete from ErrNowMsg where id = '"+ QString::number(++flagnowerrdelete) +"'";
        if(Db::IDUdb(sql)){printf("insertCError\n");}
    }

    sql = "delete from ErrNowMsg where netid = '"+ QString::number(netId) +"' \
                                    and nodeid = '"+ QString::number(nodeId) +"' \
                                    and subnodeid = '"+ QString::number(subNodeId) +"'";
    Db::IDUdb(sql);//删除故障记录中的故障报警

    sql = "delete from WarnNowMsg where netid = '"+ QString::number(netId) +"' \
                                    and nodeid = '"+ QString::number(nodeId) +"' \
                                    and subnodeid = '"+ QString::number(subNodeId) +"'";
    Db::IDUdb(sql);//删除报警记录中的报警

    sql = "delete from ErrNowMsg where netid = '"+ QString::number(netId) +"' \
                                    and nodeid = '"+ QString::number(nodeId) +"' \
                                    and typeid = '"+ QString::number(E_ALARM) +"'";
    Db::IDUdb(sql);//删除故障报警记录中的模块故障

    sql = "insert into ErrNowMsg values(NULL,'"+QString::number(netId)+"',\
                                               '"+QString::number(nodeId)+"',\
                                                '"+QString::number(subNodeId)+"',\
                                                 '"+QString::number(warn)+"',\
                                                   '"+QString::number(value)+"',\
                                                    '"+time_str+"',\
                                                      '"+addr+"');";

    Db::IDUdb(sql);
}

void WarnMsg::insertTError(int netId, int nodeId, int subNodeId)//温度故障
{//printf("enter insertTError\n");
    //int sn = Module::getNodeSN( netId, nodeId);
    QString strSubId = QString::number(subNodeId);
    int warn = SUB_ERROR;
    int value = 0;
    QString addr = Mater::readaddress(netId,nodeId,subNodeId);
    QString time_str = Db::newTime();

        PicProtocol::pic_t_error(netId, nodeId, subNodeId, time_str);//温度故障
        //PicProtocol::pic_t_restore(netId, nodeId, subNodeId, time_str);
    QString sql = "select count(*) from ErrMsg";
    if( Db::selectCount(sql) >= SQLMAXDATA)//SQLMAX
    {
        printf("insertTError Db::selectCount(sql)===%d\n",Db::selectCount(sql));
        sql = "delete from ErrMsg where id = '"+ QString::number(++flagerrdelete) +"'";
        if(Db::IDUdb(sql)){printf("insertTError\n");}
        //return;
    }
    sql = "insert into ErrMsg values(NULL,'"+QString::number(netId)+"','"+
            QString::number(nodeId)+"','"+strSubId+"','"+QString::number(warn)+"','"+
            QString::number(value)+"','"+time_str+"','"+addr+"');";
    Db::IDUdb(sql);
}
void WarnMsg::insertCError(int netId, int nodeId, int subNodeId)//漏电故障
{//printf("enter insertCError\n");
    //int sn = Module::getNodeSN( netId, nodeId);
    QString strSubId = QString::number(subNodeId);
    int warn = SUB_ERROR;
    int value = 0;
    QString addr = Mater::readaddress(netId,nodeId,subNodeId);
    QString time_str = Db::newTime();

        PicProtocol::pic_c_error(netId, nodeId, subNodeId, time_str);//漏电故障
        //PicProtocol::pic_c_restore(netId, nodeId, subNodeId, time_str);
    QString sql = "select count(*) from ErrMsg";
    if( Db::selectCount(sql) >= SQLMAXDATA)//SQLMAX
    {
        printf("insertCError Db::selectCount(sql)===%d\n",Db::selectCount(sql));
        sql = "delete from ErrMsg where id = '"+ QString::number(++flagerrdelete) +"'";
        if(Db::IDUdb(sql)){printf("insertCError\n");}
        //return;
    }
    sql = "insert into ErrMsg values(NULL,'"+QString::number(netId)+"','"+
            QString::number(nodeId)+"','"+strSubId+"','"+QString::number(warn)+"','"+
            QString::number(value)+"','"+time_str+"','"+addr+"');";
    Db::IDUdb(sql);
}

void WarnMsg::insertCrestore(int netId, int nodeId, int subNodeId)//漏电故障恢复
{    
    QString time_str = Db::newTime();
    PicProtocol::pic_c_restore(netId, nodeId, subNodeId, time_str);//漏电故障

    QString sql = "delete from ErrNowMsg where netid = '"+ QString::number(netId) +"' \
                                    and nodeid = '"+ QString::number(nodeId) +"' \
                                    and subnodeid = '"+ QString::number(subNodeId) +"'";
    Db::IDUdb(sql);//删除故障记录中的故障报警

    sql = "delete from ErrNowMsg where netid = '"+ QString::number(netId) +"' \
                                    and nodeid = '"+ QString::number(nodeId) +"' \
                                    and typeid = '"+ QString::number(E_ALARM) +"'";
    Db::IDUdb(sql);//删除故障报警记录中的模块故障
}

void WarnMsg::insertTorCrestore(int netId, int nodeId, int subNodeId)//温度漏电报警恢复
{
    QString sql = "delete from WarnNowMsg where netid = '"+ QString::number(netId) +"' \
                                    and nodeid = '"+ QString::number(nodeId) +"' \
                                    and subnodeid = '"+ QString::number(subNodeId) +"'";
    Db::IDUdb(sql);//删除报警记录中的温度漏电报警

    sql = "delete from ErrNowMsg where netid = '"+ QString::number(netId) +"' \
                                    and nodeid = '"+ QString::number(nodeId) +"' \
                                    and typeid = '"+ QString::number(E_ALARM) +"'";
    Db::IDUdb(sql);//删除故障报警记录中的模块故障
}

void WarnMsg::insertTrestore(int netId, int nodeId, int subNodeId)//温度故障恢复
{
    QString time_str = Db::newTime();
    PicProtocol::pic_t_restore(netId, nodeId, subNodeId, time_str);//温度故障

    QString sql = "delete from ErrNowMsg where netid = '"+ QString::number(netId) +"' \
                                    and nodeid = '"+ QString::number(nodeId) +"' \
                                    and subnodeid = '"+ QString::number(subNodeId) +"'";
    Db::IDUdb(sql);//删除故障记录中的故障报警
}

void WarnMsg::insertSubError(int netId, int nodeId, int subNodeId)
{
    //int sn = Module::getNodeSN( netId, nodeId);
	QString strSubId = QString::number(subNodeId);
	int warn = SUB_ERROR;
	int value = 0;

        QString time_str = Db::newTime();

        //PicProtocol::pic_channel_error(netId, nodeId, subNodeId, time_str);//通道故障
    QString sql = "select count(*) from ErrMsg";
    if( Db::selectCount(sql) >= SQLMAXDATA)
	{
        sql = "delete from ErrMsg where id = '"+ QString::number(++flagerrdelete) +"'";
        if(Db::IDUdb(sql)){printf("insertSubError ok\n");}
        //return;
	}
    sql = "insert into ErrMsg values(NULL,'"+QString::number(netId)+"','"+
			QString::number(nodeId)+"','"+strSubId+"','"+QString::number(warn)+"','"+
			QString::number(value)+"','"+time_str+"');";
	Db::IDUdb(sql);
}

int WarnMsg::insertNodeDo(int netId, int nodeId, int wDo)
{
    QString sql = "select count(*) from ErrMsg";
        QString time_str = Db::newTime();
	
    if (wDo == E_ALARM)
            //PicProtocol::pic_communication_error(netId, nodeId, 99, time_str);//故障
            PicProtocol::pic_channel_error(netId, nodeId, 99, time_str);//通道故障
    if(wDo == E_ALARM)
    {
        if( Db::selectCount(sql) >= SQLMAXDATA)//SQLMAX
        {
            printf("insertNodeDo Db::selectCount(sql)===%d\n",Db::selectCount(sql));
            sql = "delete from ErrMsg where id = '"+ QString::number(++flagerrdelete) +"'";
            //sql = "delete from ErrMsg limit 1";//不起作用
            if(Db::IDUdb(sql)){printf("insertNodeDo ok\n");}
            //return;
        }
        sql = "select count(*) from ErrMsg";
        //printf("insertNodeDo 222222222222222Db::selectCount(sql)===%d\n",Db::selectCount(sql));
        sql = "insert into ErrMsg values(NULL,'"+QString::number(netId)+"','"+
                QString::number(nodeId)+"',' ','"+QString::number(wDo)+"',' ','"+time_str+"',' ');";
    }
    else
    {
        sql = "select count(*) from WarnMsg";
        if( Db::selectCount(sql) >= SQLMAXDATA)//SQLMAX
        {
            printf("insertNodeDo Db::selectCount(sql)===%d\n",Db::selectCount(sql));
            sql = "delete from WarnMsg where id = '"+ QString::number(++flagwarndelete) +"'";
            if(Db::IDUdb(sql)){printf("insertNodeDo ok\n");}
            //return;
        }
        sql = "select count(*) from WarnMsg";
        //printf("insertNodeDo 222222222222222Db::selectCount(sql)===%d\n",Db::selectCount(sql));
        sql = "insert into WarnMsg values(NULL,'"+QString::number(netId)+"','"+
                QString::number(nodeId)+"',' ','"+QString::number(wDo)+"',' ','"+time_str+"',' ');";
    }
	return Db::IDUdb(sql);
}

//模块故障报警
int WarnMsg::insertNowNodeDo(int netId, int nodeId, int wDo)
{
    QString sql = "select count(*) from ErrNowMsg";
    QString time_str = Db::newTime();

    if(wDo == E_ALARM)
    {
        if( Db::selectCount(sql) >= SQLMAXDATA)//SQLMAX
        {
            sql = "delete from ErrNowMsg where id = '"+ QString::number(++flagnowerrdelete) +"'";
            if(Db::IDUdb(sql)){printf("insertNodeDo ok\n");}
        }

        sql = "delete from WarnNowMsg where netid = '"+ QString::number(netId) +"' \
                                        and nodeid = '"+ QString::number(nodeId) +"' ";
        Db::IDUdb(sql);//删除报警记录中的报警

        sql = "delete from ErrNowMsg where netid = '"+ QString::number(netId) +"' \
                                        and nodeid = '"+ QString::number(nodeId) +"' ";
        Db::IDUdb(sql);//删除故障报警记录中的故障

        sql = "insert into ErrNowMsg values(NULL,'"+QString::number(netId)+"','"+
                QString::number(nodeId)+"',' ','"+QString::number(wDo)+"',' ','"+time_str+"',' ');";
    }
    return Db::IDUdb(sql);
}

//模块故障报警恢复
int WarnMsg::insertNowNodeDorestore(int netId, int nodeId, int wDo)
{
    QString sql = "select count(*) from ErrNowMsg";
    QString time_str = Db::newTime();

    if(wDo == E_ALARM)
    {
        if( Db::selectCount(sql) >= SQLMAXDATA)//SQLMAX
        {
            sql = "delete from ErrNowMsg where id = '"+ QString::number(++flagnowerrdelete) +"'";
            if(Db::IDUdb(sql)){printf("insertNodeDo ok\n");}
        }

        sql = "delete from ErrNowMsg where netid = '"+ QString::number(netId) +"' \
                                        and nodeid = '"+ QString::number(nodeId) +"' \
                                        and typeid = '"+ QString::number(E_ALARM) +"'";
        //Db::IDUdb(sql);//删除故障报警记录中的模块故障
    }
    return Db::IDUdb(sql);
}

//模块故障报警
void WarnMsg::insertEAlarm(int netId,int nodeId)
{
	WarnMsg::insertNodeDo( netId, nodeId,  E_ALARM);
    WarnMsg::insertNowNodeDo( netId, nodeId,  E_ALARM);
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

void WarnMsg::getNowTable(QString time_bg,QString timer_end, int net,int id, int subId, int big , QSqlQueryModel *model)
{
    QString sql="select * from WarnNowMsg where  _warntime > '"+time_bg+"' and _warntime <'"+timer_end+"'";
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
    sql += " ORDER BY id DESC limit 9 offset "+ QString::number(big);//按照数据库id降序排列取出9条记录

    //QString sql="select distinct NetId,NodeId,SubNodeId from warnmsg";
    //QString sql="select substring_index(group_concat(_warntime order by _warntime desc),",",1) as _warntime from warnmsg group by netid";
    //QString sql="select substring_index(group_concat(_warntime order by _warntime desc),',',1) as _warntime from warnmsg group by netid";

    Db::fillModel(sql,model);
}

void WarnMsg::getNowErrTable(QString time_bg,QString timer_end, int net,int id, int subId, int big , QSqlQueryModel *model)
{
    QString sql="select * from ErrNowMsg where  _warntime > '"+time_bg+"' and _warntime <'"+timer_end+"'";
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
    sql += " ORDER BY id DESC limit 9 offset "+ QString::number(big);//按照数据库id降序排列取出9条记录 跳过big条记录
    //sql += " ORDER BY id DESC";
    Db::fillModel(sql,model);
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
    sql += " ORDER BY id DESC limit 9 offset "+ QString::number(big);//按照数据库id降序排列取出9条记录
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

int WarnMsg::getNowCount(QString time_bg,QString timer_end,int net,int id, int subId)
{
    QString sql = "select count(*) from WarnNowMsg where  _warntime > '"+ time_bg +"' and _warntime <'"+timer_end+"'";
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

int WarnMsg::getNowerrCount(QString time_bg,QString timer_end,int net,int id, int subId)
{
    QString sql = "select count(*) from ErrNowMsg where  _warntime > '"+ time_bg +"' and _warntime <'"+timer_end+"'";
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
    flagwarndelete = 0;
    flagnowwarndelete = 0;
	return Db::IDUdb(sql);
}

bool WarnMsg::delerrAll()
{
    QString sql= "delete from errmsg";
    flagerrdelete = 0;
    flagnowerrdelete = 0;
    return Db::IDUdb(sql);
}
