
#include "dbuser.h"
#include "main/main.h"
#include "define/define.h"

#include <QSqlQuery>
#include <QString>
#include <string.h>

bool DbUser::login(QString name,QString pwd)//用户登录
{
	bool ret;
	QString sql= QString::fromUtf8("select * from user where name='")+name+QString::fromUtf8("' and pwd='")+pwd+QString::fromUtf8("'");
	Db::isOpen();
	QSqlQuery query;
	query.exec(sql);
	if(query.next())
	{
		Db::purview = query.value(2).toString().toInt();
		strcpy(Db::username,  (const char*)query.value(0).toString().data());
		ret = true;
	}
	else
	{
		ret = false;
	}
	return ret;
}
bool DbUser::checkPwd(QString pwd)//检测密码
{
	QString str(Db::username);
	QString sql= QString::fromUtf8("select * from user where name = '")
			+str+QString::fromUtf8("' and pwd='")+pwd+QString::fromUtf8("'");
	return Db::isHave(sql);
}
bool DbUser::check(QString name,QString pwd)//检查用户
{
	QString sql= QString::fromUtf8("select * from user where name='")+name+QString::fromUtf8("' and pwd='")+pwd+QString::fromUtf8("'");
	return Db::isHave(sql);
}
bool DbUser::updataPwd(QString name,QString pwd)//修改密码
{
	QString sql=QString::fromUtf8("update user set pwd='")+pwd+QString::fromUtf8("' where name='")+name+QString::fromUtf8("'");
	return  Db::IDUdb(sql);
}
bool DbUser::checkName(QString name)//检测用户
{
	QString sql= QString::fromUtf8("select count(*) from user where name='")+name+QString::fromUtf8("'");
	if(Db::selectCount(sql) > 0)
		return true;
	return false;
}
int DbUser::count()//用户的个数
{
	QString sql= QString::fromUtf8("select count(*) from user");
	return Db::selectCount(sql);
}
bool DbUser::insert(QString name,QString pwd,int root)
{
	QString sql = QString::fromUtf8("insert into user VALUES ('")+
				name+QString::fromUtf8("','")+pwd+QString::fromUtf8("','")+QString::number(root)+QString::fromUtf8("')");
	return  Db::IDUdb(sql);
}
void DbUser::getTable(int root,QSqlQueryModel* model)
{
	QString sql = QString::fromUtf8("select * from user ") ;
	if(root == DO){
		sql += QString::fromUtf8(" where auth='")+QString::number(QUERY)+QString::fromUtf8("'");
	}
	Db::fillModel(sql,model);
}
bool DbUser::del(QString name)
{
	QString sql = QString::fromUtf8("delete from user where name='")+name+QString::fromUtf8("'") ;
	return  Db::IDUdb(sql);
}
QString DbUser::getPwd(QString name)
{
	QString sql = QString::fromUtf8("select * from user where name= '")+name+QString::fromUtf8("'") ;
	return Db::getValue( sql, 1);
}
bool DbUser::updataUser(QString name,int root,QString pwd)
{
	QString sql = QString::fromUtf8("update user set pwd='")+pwd+QString::fromUtf8("',auth='")
			+QString::number(root)+QString::fromUtf8("' where name='")+name+QString::fromUtf8("'");
	return  Db::IDUdb(sql);
}
