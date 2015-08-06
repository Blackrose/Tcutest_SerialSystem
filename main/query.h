/*=========================
	查询界面
=========================*/
#ifndef LINLONG_QUERY
#define LINLONG_QUERY

#include <QWidget>
#include "ui_query.h"
#include <QString>
#include <QTableWidgetItem>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QKeyEvent>
#include <QObject>
#include <QDateTime>
#include "keyboard/imframe.h"
#include "sql/warnMsg.h"
#include "sql/optMsg.h"

class  Query:public QDialog,public Ui_QueryForm
{
        Q_OBJECT
public :
        Query(QWidget* parent=NULL);
        virtual ~Query();
	void init_time(QDateTimeEdit &dte,int day);
	void init_table();
	void init_opt();
    void init_warn();
	void init_parameter();
	void _show();
private:
	QTableWidgetItem *qtw;
	QSqlQueryModel *modelSql;
	QDateTime	 dte_b_time,
			 dte_e_time;
	int 		typeQuery;
	int 		countNumber;	//有几页
	int 		currentNumber;	//当前页
	int 		count;		//数据条数
	int 		currentCount;	//当前页几条数据
	int 		par[4];
	QString 	timer_start;
    QString 	timer_end;
public slots:
	void changedIndex(int index);
	void ok();
	void datTimCha(const QDateTime & datetime);
	void beforePage();
	void nextPage();
	void _hide();
};
#endif
