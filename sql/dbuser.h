/*==============================
	用户信息数据库统一接口
==============================*/
#ifndef LINLONG_DBUSER
#define LINLONG_DBUSER
#include <QSqlDatabase>
#include <QString>
#include <QSqlQueryModel>
#include "db.h"

class  DbUser
{
public :
	bool login(QString name,QString pwd);//用户登录
	bool check(QString name,QString pwd);//检查用户
	bool checkPwd(QString pwd);//检测密码
	bool updataPwd(QString name,QString pwd);//修改密码
	bool checkName(QString name);
	bool insert(QString name,QString pwd,int root);
	void getTable(int root,QSqlQueryModel* model);
	bool del(QString name);
	QString getPwd(QString name);
	bool updataUser(QString name,int root,QString pwd);
	int count();//用户的个数
};
#endif
