#ifndef SQL_MATER
#define SQL_MATER

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>  
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <QString>
#include <db.h>

class Mater
{
public:
	static int read();
	static bool write(QString str);

	static int readNet0Count();
	static int readNet1Count();
	static int readSendTimer();

	static bool writeNet0Count(QString str);
	static bool writeNet1Count(QString str);
	static bool writeSendTimer(QString str);

	/* USART1 database configuration */
	static bool writeUsart1Baudrate(QString str);
	static bool writeUsart1Parity(QString str);
	static bool writeUsart1Data(QString str);
	static bool writeUsart1Stop(QString str);
	static QString readUsart1Baudrate();
	static QString readUsart1Parity();
	static QString readUsart1Data();
	static QString readUsart1Stop();

	/* USART2 database configuration */
	static bool writeUsart2Baudrate(QString str);
	static bool writeUsart2Parity(QString str);
	static bool writeUsart2Data(QString str);
	static bool writeUsart2Stop(QString str);
	static QString readUsart2Baudrate();
	static QString readUsart2Parity();
	static QString readUsart2Data();
	static QString readUsart2Stop();

	/* USART3 database configuration */
	static bool writeUsart3Baudrate(QString str);
	static bool writeUsart3Parity(QString str);
	static bool writeUsart3Data(QString str);
	static bool writeUsart3Stop(QString str);
	static QString readUsart3Baudrate();
	static QString readUsart3Parity();
	static QString readUsart3Data();
	static QString readUsart3Stop();

	/* local modbus slave address database configuration */
	static bool writeLocalAddress(QString str);
	static int readLocalAddress();

    static QString read0address(int addr);
    static QString read1address(int addr);
    static QString read2address(int addr);
    static QString read3address(int addr);
    static QString read4address(int addr);
    static QString read5address(int addr);
    static QString read6address(int addr);
    static QString read7address(int addr);
    static bool write0address(QString str, int addr);
    static bool write1address(QString str,int addr);
    static bool write2address(QString str, int addr);
    static bool write3address(QString str,int addr);
    static bool write4address(QString str,int addr);
    static bool write5address(QString str,int addr);
    static bool write6address(QString str, int addr);
    static bool write7address(QString str,int addr);

};


#endif
