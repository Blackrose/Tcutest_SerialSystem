
#include "mater.h"
#include <QString>
#include <string.h>

int Mater::read()
{
	QString sql = "select * from type where id = 1" ;
	sql = Db::getValue( sql, 1);
	return sql.toInt();
}
bool Mater::write(QString str)
{
	QString sql="update type set name='"+str+"' where id = 1";
	return  Db::IDUdb(sql);
}
int Mater::readNet0Count()
{
	QString sql = "select * from type where id = 2" ;
	sql = Db::getValue( sql, 1);
	return sql.toInt();
}
int Mater::readNet1Count()
{
	QString sql = "select * from type where id = 3" ;
	sql = Db::getValue( sql, 1);
	return sql.toInt();
}
int Mater::readSendTimer()
{
	QString sql = "select * from type where id = 4" ;
	sql = Db::getValue( sql, 1);
	return sql.toInt();
}
bool Mater::writeNet0Count(QString str)
{
	QString sql="update type set name='"+str+"' where id = 2";
	return  Db::IDUdb(sql);
}
bool Mater::writeNet1Count(QString str)
{
	QString sql="update type set name='"+str+"' where id = 3";
	return  Db::IDUdb(sql);
}
bool Mater::writeSendTimer(QString str)
{
	QString sql="update type set name='"+str+"' where id = 4";
	return  Db::IDUdb(sql);
}

/* USART1 database configuration */
bool Mater::writeUsart1Baudrate(QString str)
{
	QString sql="update type set name='"+str+"' where id = 5";
	return  Db::IDUdb(sql);
}

bool Mater::writeUsart1Parity(QString str)
{
    QString sql="update type set name='"+str+"' where id = 6";
    //QString sql = QString::fromUtf8("update type set name='") +str+ QString::fromUtf8("' where id = 6");
	return  Db::IDUdb(sql);
}

bool Mater::writeUsart1Data(QString str)
{
    QString sql="update type set name='"+str+"' where id = 7";
    //QString sql = QString::fromUtf8("update type set name='") +str+ QString::fromUtf8("' where id = 7");
	return  Db::IDUdb(sql);
}

bool Mater::writeUsart1Stop(QString str)
{
    QString sql="update type set name='"+str+"' where id = 8";
    //QString sql = QString::fromUtf8("update type set name='") +str+ QString::fromUtf8("' where id = 8");
	return  Db::IDUdb(sql);
}

QString Mater::readUsart1Baudrate()
{
    QString sql = "select * from type where id = 5" ;
    //QString sql = QString::fromUtf8("select * from type where id = 5") ;
	sql = Db::getValue( sql, 1);
	return sql;
}

QString Mater::readUsart1Parity()
{
    QString sql = "select * from type where id = 6" ;
    //QString sql =  QString::fromUtf8("select * from type where id = 6");
	sql = Db::getValue( sql, 1);
	return sql;
}

QString Mater::readUsart1Data()
{
    QString sql = "select * from type where id = 7" ;
    //QString sql = QString::fromUtf8("select * from type where id = 7") ;
	sql = Db::getValue( sql, 1);
	return sql;
}

QString Mater::readUsart1Stop()
{
    QString sql = "select * from type where id = 8" ;
    //QString sql = QString::fromUtf8("select * from type where id = 8") ;
	sql = Db::getValue( sql, 1);
	return sql;
}

/* USART2 database configuration */
bool Mater::writeUsart2Baudrate(QString str)
{
	QString sql="update type set name='"+str+"' where id = 9";
	return  Db::IDUdb(sql);
}

bool Mater::writeUsart2Parity(QString str)
{
	QString sql="update type set name='"+str+"' where id = 10";
	return  Db::IDUdb(sql);
}

bool Mater::writeUsart2Data(QString str)
{
	QString sql="update type set name='"+str+"' where id = 11";
	return  Db::IDUdb(sql);
}

bool Mater::writeUsart2Stop(QString str)
{
	QString sql="update type set name='"+str+"' where id = 12";
	return  Db::IDUdb(sql);
}

QString Mater::readUsart2Baudrate()
{
	QString sql = "select * from type where id = 9" ;
	sql = Db::getValue( sql, 1);
	return sql;
}

QString Mater::readUsart2Parity()
{
	QString sql = "select * from type where id = 10" ;
	sql = Db::getValue( sql, 1);
	return sql;
}

QString Mater::readUsart2Data()
{
	QString sql = "select * from type where id = 11" ;
	sql = Db::getValue( sql, 1);
	return sql;
}

QString Mater::readUsart2Stop()
{
	QString sql = "select * from type where id = 12" ;
	sql = Db::getValue( sql, 1);
	return sql;
}

/* USART3 database configuration */
bool Mater::writeUsart3Baudrate(QString str)
{
	QString sql="update type set name='"+str+"' where id = 13";
	return  Db::IDUdb(sql);
}

bool Mater::writeUsart3Parity(QString str)
{
	QString sql="update type set name='"+str+"' where id = 14";
	return  Db::IDUdb(sql);
}

bool Mater::writeUsart3Data(QString str)
{
	QString sql="update type set name='"+str+"' where id = 15";
	return  Db::IDUdb(sql);
}

bool Mater::writeUsart3Stop(QString str)
{
	QString sql="update type set name='"+str+"' where id = 16";
	return  Db::IDUdb(sql);
}

QString Mater::readUsart3Baudrate()
{
	QString sql = "select * from type where id = 13" ;
	sql = Db::getValue( sql, 1);
	return sql;
}

QString Mater::readUsart3Parity()
{
	QString sql = "select * from type where id = 14" ;
	sql = Db::getValue( sql, 1);
	return sql;
}

QString Mater::readUsart3Data()
{
	QString sql = "select * from type where id = 15" ;
	sql = Db::getValue( sql, 1);
	return sql;
}

QString Mater::readUsart3Stop()
{
	QString sql = "select * from type where id = 16" ;
	sql = Db::getValue( sql, 1);
	return sql;
}

/* local modbus slave address database configuration */
bool Mater::writeLocalAddress(QString str)
{
	QString sql="update type set name='"+str+"' where id = 17";
	return  Db::IDUdb(sql);
}

int Mater::readLocalAddress()
{
	QString sql = "select * from type where id = 17" ;
	sql = Db::getValue( sql, 1);
	return sql.toInt();
}


QString Mater::read0address(int addr)
{
    QString sql = "select * from address where id = '"+ QString::number(addr) +"'" ;
    sql = Db::getValue( sql, 1);
    return sql;
}

QString Mater::read1address(int addr)
{
    QString sql = "select * from address where id = '"+ QString::number(addr) +"'" ;
    sql = Db::getValue( sql, 2);
    return sql;
}

QString Mater::read2address(int addr)
{
    QString sql = "select * from address where id = '"+ QString::number(addr) +"'" ;
    sql = Db::getValue( sql, 3);
    return sql;
}

QString Mater::read3address(int addr)
{
    QString sql = "select * from address where id = '"+ QString::number(addr) +"'" ;
    sql = Db::getValue( sql, 4);
    return sql;
}

QString Mater::read4address(int addr)
{
    //QString sql = "select * from type where id = 22" ;
    QString sql = "select * from address where id = '"+ QString::number(addr) +"'" ;
    sql = Db::getValue( sql, 5);
    return sql;
}

QString Mater::read5address(int addr)
{
    QString sql = "select * from address where id = '"+ QString::number(addr) +"'" ;
    sql = Db::getValue( sql, 6);
    return sql;
}

QString Mater::read6address(int addr)
{
    QString sql = "select * from address where id = '"+ QString::number(addr) +"'" ;
    sql = Db::getValue( sql, 7);
    return sql;
}

QString Mater::read7address(int addr)
{
    QString sql = "select * from address where id = '"+ QString::number(addr) +"'" ;
    sql = Db::getValue( sql, 8);
    return sql;
}


bool Mater::write0address(QString str,int addr)
{
    QString sql="update address set addr0='"+str+"' where id = '"+QString::number(addr)+"'";
    return  Db::IDUdb(sql);
}

bool Mater::write1address(QString str,int addr)
{
    QString sql="update address set addr1='"+str+"' where id = '"+QString::number(addr)+"'";
    return  Db::IDUdb(sql);
}

bool Mater::write2address(QString str,int addr)
{
    QString sql="update address set addr2='"+str+"' where id = '"+QString::number(addr)+"'";
    return  Db::IDUdb(sql);
}

bool Mater::write3address(QString str,int addr)
{
    QString sql="update address set addr3='"+str+"' where id = '"+QString::number(addr)+"'";
    return  Db::IDUdb(sql);
}

bool Mater::write4address(QString str, int addr)
{
    QString sql="update address set addr4='"+str+"' where id = '"+QString::number(addr)+"'";
    return  Db::IDUdb(sql);
}

bool Mater::write5address(QString str,int addr)
{
    QString sql="update address set addr5='"+str+"' where id = '"+QString::number(addr)+"'";
    return  Db::IDUdb(sql);
}

bool Mater::write6address(QString str,int addr)
{
    QString sql="update address set addr6='"+str+"' where id = '"+QString::number(addr)+"'";
    return  Db::IDUdb(sql);
}

bool Mater::write7address(QString str,int addr)
{
    QString sql="update address set addr7='"+str+"' where id = '"+QString::number(addr)+"'";
    return  Db::IDUdb(sql);
}
