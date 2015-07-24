//类型参数设置
#ifndef LINLONG_OPTMSG
#define LINLONG_OPTMSG

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <stdio.h>
#include "db.h"
#include <QSqlQueryModel>

class OptMsg
{
private:
	static void insert(int id);//插入操作
public:
	static int getCount(QString time_bg,QString timer_end);
	static void getTable(QString time_bg,QString timer_end,int big,QSqlQueryModel *model);
	static bool delAll();

	static void insertUpataPwd();//修改密码
	static void insertUserLogin();//用户登录
	static void insertUserUpdate();//修改用户
	static void insertUserDel();//删除用户
	static void insertUserInsert();//增加用户
	static void insertSysTimeSet();//设置系统时间
	static void insertClearWarnDat();//清除报警数据
    static void insertClearErrDat();//清除故障数据
	static void insertClearDoDat();//清除操作数据

};
#endif
