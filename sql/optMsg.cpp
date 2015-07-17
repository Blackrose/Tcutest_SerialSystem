
#include "optMsg.h"

void OptMsg::insert(int id)
{
	QString sql = "select count(*) from optMsg";
	if( Db::selectCount(sql) > 500) 
	{
		return;
	}
	QString str(Db::username);
	sql = "INSERT INTO optMsg VALUES (NULL,'"+str+"', "+QString::number(id)+", '"+Db::newTime()+"')";
	Db::IDUdb(sql);
}
void OptMsg::insertUpataPwd()//修改密码
{
	OptMsg::insert(UPATA_PWD);
}
void OptMsg::insertUserLogin()//用户登录
{
	OptMsg::insert(USER_LOGIN);
}
void OptMsg::insertUserUpdate()//修改用户
{
	OptMsg::insert(USER_UPATA);
}
void OptMsg::insertUserDel()//删除用户
{
	OptMsg::insert(USER_DEL);
}
void OptMsg::insertUserInsert()//增加用户
{
	OptMsg::insert(USER_INSERT);
}
void OptMsg::insertSysTimeSet()//设置系统时间
{
	OptMsg::insert(SYS_TIME_SET);
}
void OptMsg::insertClearWarnDat()//清除报警数据
{
	OptMsg::insert(CLEAR_WARN_DAT);
}
void OptMsg::insertClearDoDat()//清除操作数据
{
	OptMsg::insert(CLEAR_DO_DAT);
}

void OptMsg::getTable(QString time_bg,QString timer_end,int big,QSqlQueryModel *model)
{
	QString sql="select * from OptMsg where OptTime > '"+time_bg+"' and OptTime <'"+timer_end+"'";
	sql += " ORDER BY id DESC limit 9 offset "+QString::number(big);
	Db::fillModel(sql,model);
}

int OptMsg::getCount(QString time_bg,QString timer_end)
{
	QString sql="select count(*) from OptMsg where OptTime > '"+time_bg+"' and OptTime <'"+timer_end+"'";
	return Db::selectCount(sql);
}

bool OptMsg::delAll()
{
	QString sql= "delete from OptMsg";
	return Db::IDUdb(sql);
}

