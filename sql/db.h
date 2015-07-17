/*========================
	数据库同一接口
========================*/
#ifndef LINLONG_DB
#define LINLONG_DB

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>
#include <QLabel>
#define C_ALARM	0	//电流报警
#define T_ALARM	1	//温度报警
#define M_ALARM	2	//漏电报警
#define E_ALARM	3	//模块故障报警
#define NODE_SET	4 //设置节点
#define NODE_CUT	5 //脱扣节点
#define NODE_RESET	6 //复位节点
#define NODE_REMOVE	7 //注销节点
#define MAIN_NO		8 //主电欠压
#define PREMAIN_NO	9//备电欠压
#define PREMAIN_ON	10//备电短路
#define PREMAIN_OFF	11//备电断路
#define MAIN_OK		12 //主电正常
#define PREMAIN_OK	13//备电正常
#define SUB_ERROR       14

#define UPATA_PWD	0 	//修改密码
#define USER_LOGIN	1 	//用户登录
#define USER_UPATA	2 	//修改用户
#define USER_DEL	3 	//删除用户
#define USER_INSERT	4 	//增加用户
#define SYS_TIME_SET	5 	//设置系统时间
#define CLEAR_WARN_DAT	6 	//清除报警数据
#define CLEAR_DO_DAT	7 	//清除操作数据


#define ALL -1

struct MyString
{
	char str[30];
};

class  Db
{
public:
	static struct MyString *warnigData;
	static struct MyString *doData;
	static QSqlDatabase db;
	static char* username;//登录名称
	static int purview;//登录的权限

       	static void init();//加载 数据库
	static void isOpen();//判断数据库是否打开
	static void close();//关闭数据库
	static bool IDUdb(QString &sql);//数据库操作
	static bool isHave(QString &sql);//查询是否有记录
	static int selectCount(QString &sql);//返回查询条数
	static void fillModel(QString &sql,QSqlQueryModel *model);
	static QString getValue(QString &sql,int c);
	static QString newTime();
	static void copyTime(char* ch);
	static void newTimeNoSec(QLabel* lbl,int *fen);
	static void vacuum();
};
#endif
