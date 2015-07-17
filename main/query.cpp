/*=============================
	查询界面化界面
=============================*/
#include "query.h"
#include "define.h"

#include <stdio.h>
#include <QWidget>
#include <time.h>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlQuery>

Query::Query(QWidget *parent): QDialog(parent),Ui_QueryForm()
{
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose);
	countNumber = 0; 	//有几页
	currentNumber = 0; 	//当前页
	count = 0;		//数据条数	
	currentCount = 0;
	modelSql = new QSqlQueryModel;
	qtw = NULL;
	for(int i = 0 ; i < 110 ; i++)
	{
		cmb_node->insertItem(i+1,QString::number(i));
	}
        setWindowFlags(Qt::Dialog
			| Qt::FramelessWindowHint);//窗口没有没有边框
	tableWidget->setAlternatingRowColors(true);//设置背景交替使用

	connect(btn_close, SIGNAL(clicked()), this, SLOT(_hide()));
	connect(btn_query, SIGNAL(clicked()), this, SLOT(ok()));
	connect(btnBefore, SIGNAL(clicked()), this, SLOT(beforePage()));
	connect(btnNext, SIGNAL(clicked()), this, SLOT(nextPage()));
	connect(cmb_note_type, SIGNAL(currentIndexChanged(int)), this, SLOT(changedIndex(int)));

	connect(dte_begin,SIGNAL(dateTimeChanged ( const QDateTime&)),this,SLOT(datTimCha(const QDateTime &)));
	connect(dte_end,SIGNAL(dateTimeChanged ( const QDateTime&)),this,SLOT(datTimCha(const QDateTime &)));
	printf("init Query ok\n");
}
Query::~Query()
{
	delete modelSql;
	printf("exit Query\n");
}
void Query::_show()
{
	printf("1\n");
	init_time( *dte_end, 0);
	printf("2\n");
	init_time( *dte_begin, 10);
	printf("3\n");
	init_parameter();
	printf("4\n");
	init_table();
	printf("5\n");
	show();
	printf("6\n");
}
void Query::_hide()
{
	tableWidget->clearSelection();
	hide();
}
// 查询
void Query::ok()
{
	tableWidget->clearSelection();
	init_parameter();
	init_table();
}
// 上一页
void Query::beforePage()
{
	tableWidget->clearSelection();
	currentNumber = ( -- currentNumber ) % countNumber;
	if(currentNumber < 1)
		currentNumber = countNumber;
	init_table();
}
// 下一页
void Query::nextPage()
{
	tableWidget->clearSelection();
	currentNumber = (  ++currentNumber ) % countNumber;
	if(currentNumber == 0)
		currentNumber = countNumber;
	init_table();
}
// 加载数据
void Query::init_table()
{
	modelSql->clear();
	delete[] qtw;
	qtw = NULL;
	par[3] = (currentNumber - 1)  * 9 ;
        lblNumber -> setText(QString::number(currentNumber) + tr("/") + QString::number(countNumber));
	if( typeQuery == 0)
	{
		init_warn();
	}
	else if( typeQuery == 1 )
	{
		init_opt();
	}
}
// 初始化一些参数
void Query::init_parameter()
{
	typeQuery = cmb_note_type->currentIndex();
	timer_start = dte_begin->text();
	timer_end = dte_end->text();
	if( typeQuery == 0)
	{
		par[0] = cmb_net->currentIndex() - 1;
		par[1] = cmb_node->currentIndex() - 1;
		par[2] = cmb_sub_node->currentIndex() - 1;
		count = WarnMsg::getCount( timer_start, timer_end, par[0], par[1], par[2]);//一共有几条数据 
	}
	else
	{
		count = OptMsg::getCount( timer_start, timer_end); //一共有几条数据 
	}
	
	countNumber = count / 9;
	if( count % 9 )
		countNumber ++;

	if(countNumber == 0)
	{
		btnBefore->setEnabled(false);
		btnNext->setEnabled(false);
		currentNumber = 0;
	}
	else{
		currentNumber = 1;
		btnBefore->setEnabled(true);
		btnNext->setEnabled(true);
	}
	lblCount -> setText(QString::number(count));
}
void Query::init_warn()
{
	WarnMsg::getTable( timer_start, timer_end, par[0], par[1], par[2] , par[3], modelSql);
	currentCount = modelSql->rowCount();
 	qtw = new QTableWidgetItem[ 7 * (currentCount + 1) ];
	tableWidget->setColumnCount(7);
	tableWidget->setRowCount(currentCount);

	qtw[0].setText( tr("编号") );
	qtw[1].setText( tr("网络号") );
	qtw[2].setText( tr("节点号") );
	qtw[3].setText( tr("子节点") );
	qtw[4].setText( tr("报警类型") );
	qtw[5].setText( tr("数值") );
	qtw[6].setText( tr("报警时间") );

	tableWidget->setColumnWidth ( 0, 55);
	tableWidget->setColumnWidth ( 1, 55);
	tableWidget->setColumnWidth ( 2, 56);
	tableWidget->setColumnWidth ( 3, 56);
	tableWidget->setColumnWidth ( 4, 110);
	tableWidget->setColumnWidth ( 5, 72);
	tableWidget->setColumnWidth ( 6, 178);

	for(int i = 0; i < 7; i++)
		tableWidget->setHorizontalHeaderItem ( i, &qtw[i]);

	QSqlRecord re;
	int ind = 0;
	int c = 0;
	for(int i = 0; i < currentCount; i++)
	{
		re = modelSql->record(i);
		ind = (i + 1) * 7;
		c = 0;
		for( ; c < 4; c ++){
			qtw[ind].setText(re.value(c).toString());
			tableWidget->setItem( i, c, &qtw[ind++]);
		}

		qtw[ind].setText(  tr(Db::warnigData[re.value(c).toInt()].str) );
		tableWidget->setItem( i, c++, &qtw[ind++]);

		qtw[ind].setText(re.value(c).toString());
		tableWidget->setItem( i, c++, &qtw[ind++]);

		qtw[ind].setText(re.value(c).toString());
		tableWidget->setItem( i, c++, &qtw[ind++]);
	}
}
void Query::init_opt()
{
	OptMsg::getTable( timer_start, timer_end, par[3], modelSql);
	currentCount = modelSql->rowCount();
 	qtw = new QTableWidgetItem[ 4 * (currentCount + 1) ];
	tableWidget->setRowCount(currentCount);//数据行数
	tableWidget->setColumnCount (4);//数据列数

	qtw[0].setText(tr("编号"));
	qtw[1].setText(tr("用户名"));
	qtw[2].setText(tr("操作事件"));
	qtw[3].setText(tr("操作时间"));

	tableWidget->setColumnWidth ( 0, 72);
	tableWidget->setColumnWidth ( 1, 83);
	tableWidget->setColumnWidth ( 2, 227);
	tableWidget->setColumnWidth ( 3, 200);

	for(int i = 0; i < 4; i++)
		tableWidget->setHorizontalHeaderItem ( i, &qtw[i]);
	
	QSqlRecord re;
	int ind = 0;
	for(int i = 0 ; i < currentCount; i++)
	{
		re = modelSql->record(i);
		ind = (i + 1) * 4;
	
		qtw[ind].setText(re.value(0).toString());
		tableWidget->setItem( i, 0, &qtw[ind ++]);

		qtw[ind].setText(re.value(1).toString());
		tableWidget->setItem( i, 1, &qtw[ind ++]);

		qtw[ind].setText( tr(Db::doData[re.value(2).toInt()].str) );
		tableWidget->setItem( i, 2, &qtw[ind ++]);

		qtw[ind].setText(re.value(3).toString() );
		tableWidget->setItem( i, 3, &qtw[ind ++]);
	}
}
//比较所两个时间数值
void Query::datTimCha(const QDateTime & datetime)
{
	QDateTimeEdit* dte=qobject_cast<QDateTimeEdit*>(sender());
	if(dte == dte_begin)
	{
		if( datetime > dte_end-> dateTime() )
			dte_begin -> setDateTime(dte_b_time);
		else
			dte_b_time = dte_begin -> dateTime();
	}
	else if(dte == dte_end)
	{
		if( datetime < dte_begin -> dateTime() )
			dte_end -> setDateTime(dte_e_time);
		else
			dte_e_time = dte_end -> dateTime();
	}
}
//加载系统时间
void Query::init_time(QDateTimeEdit &dte,int day)
{
	time_t t;
	struct tm *p;
 	tzset();
	memset(&t, 0, sizeof(t));
	time(&t);
	p=localtime(&t);
	QTime qt(p->tm_hour,p->tm_min,p->tm_sec);
	QDate qd(1900+p->tm_year,1+p->tm_mon,p->tm_mday);
	if(p->tm_mday >= day ){
		qd.setDate (1900+p->tm_year  , 1+p->tm_mon, p->tm_mday-day);
	}
	else{
		if(1+p->tm_mon == 1){
			qd.setDate (1900+p->tm_year -1 , 12, 1);
			int d = qd.daysInMonth();
			qd.setDate (1900+p->tm_year -1 , 12,d-(day - p->tm_mday));
		}
		else{
			qd.setDate (1900+p->tm_year , p->tm_mon ,0);
			int d = qd.daysInMonth();
			qd.setDate(1900+p->tm_year , p->tm_mon ,d-(day - p->tm_mday));
		}
	}
	dte.setTime(qt);
	dte.setDate(qd);
}
void Query::changedIndex(int index)
{
	QComboBox* cmb = qobject_cast<QComboBox*>(sender());
	if(cmb_note_type == cmb)
	{
		if(index == 0)
		{//报警类型
			cmb_net->setEnabled( true );
			cmb_node->setEnabled( true );
			cmb_sub_node->setEnabled( true );			
		}
		else if(index == 1)
		{
			cmb_net->setEnabled( false );
			cmb_node->setEnabled( false );
			cmb_sub_node->setEnabled( false );
		}
	}
}
