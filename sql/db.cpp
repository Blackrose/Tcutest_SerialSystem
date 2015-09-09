/*========================
	数据库同一接口
========================*/
#include "db.h"
#include <string.h>
#include <QMessageBox>
#include <QObject>

char* Db::username  = NULL; //用户名
int Db::purview = 2; //权限 0 1 2

QSqlDatabase Db::db = QSqlDatabase::addDatabase("QSQLITE");
struct MyString* Db::warnigData = NULL;
struct MyString* Db::doData = NULL;
struct MyString* Db::errData = NULL;

void Db::init()
{
	Db::username  = new char[20]; //用户名
 	Db::warnigData = new struct MyString[15];
    Db::errData = new struct MyString[7];
	Db::doData = new struct MyString[8];
	Db::db.setDatabaseName("./db.db"); //数据库名与路径
	if(!Db::db.isOpen())
		if(!Db::db.open())
			QMessageBox::question(NULL,QObject::tr("提示信息"), QObject::tr("数据库打开失败！"), QObject::tr("确定"));
	strcpy(doData[0].str, "修改密码");
	strcpy(doData[1].str, "用户登录");
	strcpy(doData[2].str, "修改用户");
	strcpy(doData[3].str, "删除用户");
	strcpy(doData[4].str, "增加用户");
	strcpy(doData[5].str, "设置系统时间");
	strcpy(doData[6].str, "清除报警数据"); 
	strcpy(doData[7].str, "清除操作数据");//操作类型

   	strcpy(warnigData[0].str,"电流报警");
	strcpy(warnigData[1].str, "温度报警");
	strcpy(warnigData[2].str, "漏电报警");
	strcpy(warnigData[3].str, "模块故障");
	strcpy(warnigData[4].str, "设置节点");
	strcpy(warnigData[5].str, "脱扣节点");
	strcpy(warnigData[6].str, "复位节点");
	strcpy(warnigData[7].str, "注销节点"); 
	strcpy(warnigData[8].str, "主电欠压");
	strcpy(warnigData[9].str, "备电欠压"); 
	strcpy(warnigData[10].str, "备电短路"); 
	strcpy(warnigData[11].str, "备电断路");
	strcpy(warnigData[12].str, "主电正常了");
	strcpy(warnigData[13].str, "备电正常了");//报警类型
	strcpy(warnigData[14].str, "传感器故障");

//    strcpy(errData[0].str,"模块故障");
//    strcpy(errData[1].str, "传感器故障");
//    strcpy(errData[2].str, "漏电报警");
//    strcpy(errData[3].str, "主电欠压");
//    strcpy(errData[4].str, "备电欠压");
//    strcpy(errData[5].str, "备电短路");
//    strcpy(errData[6].str, "备电断路");
}
void Db::isOpen()
{
	if(!db.isOpen())
	{
		QMessageBox::question(NULL,QObject::tr("提示信息"),QObject::tr("数据库打开失败，请重新启动！"),
					 QObject::tr("确定"), QObject::tr("取消"));
	}
}
void Db::close()
{
	Db::db.close();
}
bool Db::IDUdb(QString &sql)//数据库操作
{
	Db::isOpen();
	QSqlQuery query;
	if(query.exec(sql)){
        query.finish();
        //printf("IDUdb  true\n");
		return true;
	}
    query.finish();//printf("IDUdb  false\n");
	return false;
}
bool Db::isHave(QString &sql)//数据库操作
{
	Db::isOpen();
	QSqlQuery query;
	query.exec(sql);
	if(query.next()){
		return true;
	}
	return false;
}
int Db::selectCount(QString& sql)//返回查询条数
{
	int numRows = 0;
	Db::isOpen();
	QSqlQuery query;
	query.exec(sql);
	if(query.next()){
      		numRows = query.value(0).toString().toInt();
	}
	return numRows;
}
void Db::fillModel(QString &sql,QSqlQueryModel *model)
{
	Db::isOpen();
	model->setQuery(sql);
}
QString Db::getValue(QString &sql,int c)
{
	Db::isOpen();
	QSqlQuery query;
	query.exec(sql);
	if(query.next())
	{
	 	return query.value(c).toString();
	}
	return "";
}
QString Db::newTime()
{
	long ct;
	char ch[50];
	struct  tm *p;
	ct = time(&ct);
	p = (struct tm *)localtime(&ct);
	sprintf(ch,"%04d-%02d-%02d %02d:%02d:%02d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
	QString time(ch);
	return time;
}
void Db::copyTime(char* ch)
{
	long ct;
	struct tm *p;
	ct = time(&ct);
	p = (struct tm *)localtime(&ct);
	sprintf(ch,"%04d-%02d-%02d %02d:%02d:%02d",1900+p->tm_year,1+p->tm_mon,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
}
void Db::newTimeNoSec(QLabel* lbl,int *fen)
{
	long ct;
	char ch[50];
	struct  tm *p;
	ct = time(&ct);
	p = (struct tm *)localtime(&ct);
	if(*fen == p->tm_min) return;
	sprintf(ch,"%04d-%02d-%02d %02d:%02d", 1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min);
	lbl->setText(ch);
	*fen = p->tm_min;
}
void Db::vacuum()
{
	QString sql = QString::fromUtf8("VACUUM");
	Db::IDUdb(sql);
}
