#include "print.h"
#include "com.h"
#include "db.h"
#include "message.h"
#include <string.h>
#include <termios.h>
#include <QString>
#include <QMessageBox>
/*
0123456789#0123456789#0123456789
-----------网络1 报警-----------
设备号##节点号##报警类型##报警值
##01##  ##01##  超温报警  100#℃
                          2000mA
------#2014-11-28#13:34:06#-----
*/

#define LINE_SIZE 32

int Print::fd = -1;
int Print::fd1 = -1;
int Print::enable_print = 0;
int Print::no_paper = -1;
QTimer *Print::timer;
Print *Print::point;

bool Print::init()
{
#if 0
    //fd = open("/dev/null", O_RDWR);
    fd1 = open("/dev/ttySAC0",O_RDWR | O_NOCTTY);
    if (fd1 < 0) {
        printf("open dev null failure\n");
        return false;
    }
    dup2(fd1, 0);
    dup2(fd1, 1);
    dup2(fd1, 2);
#else
	struct termios newtio;
    char start[2] = {0x1c, 0x26};//汉字字模
	char on_off = 1;

    fd = open("/dev/ttySAC0",O_RDWR | O_NOCTTY);
    if (fd < 0) {
        printf("open ttySAC0 failure\n");
        return false;
    }
//    dup2(fd, 0);
//    dup2(fd, 1);
//    dup2(fd, 2);

    fd1 = open("/dev/e17printer",O_RDWR);
    if (fd1 < 0) {
		printf("open e17printer failure\n");
		return false;
	}
	::bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    //newtio.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
	/* Raw input */
	newtio.c_iflag = 0;
	/* Raw output */
	newtio.c_oflag = 0;
	/* no processing */
	newtio.c_lflag = 0;
	/* activate the settings for the port after flushing I/O */
	tcsetattr(fd, TCSAFLUSH, &newtio);
	/* flush any data waiting */
	::usleep(200000);
	::tcflush(fd, TCIOFLUSH);

	
//	QString head_str = "-----------网络1 报警-----------";
//	QString menu_str = "设备号  节点号  报警类型  报警值";
//	QString value_str = "  01      01    超温报警  100 ℃";
//	QString value1_str = "  01      01    漏电报警  2000mA";
//	QString end_str;
//	QString t_head_str = "------ ";
//	QString t_end_str = " -----";
//	QString time_str = Db::newTime();
//	end_str = t_head_str + time_str + t_end_str;
//	Print::GB2313(head_str);
//	Print::clear();
//	Print::GB2313(menu_str);
//	Print::clear();
//      Print::GB2313(value_str);
//        Print::clear();
//        Print::GB2313(value1_str);
//        Print::clear();
//	Print::GB2313(end_str);
//	Print::clear();
//	Print::goPaper();
    ::write(fd1, &on_off, 1);
    ::write(fd, start, 2);
	Print::check();
	::usleep(50000);
	no_paper = Print::status();
	enable_print = 0;

//	QString time_str = Db::newTime();
//	Print::Talarm(0, 1, 1, 120, time_str);
//	Print::Calarm(1, 110, 8, 3200, time_str);
//	Print::Local_alarm(MAIN_NO, time_str);
	
	Print::timer = new QTimer();
	Print::point = new Print;
	Print::timer->start(1000);
	connect(Print::timer, SIGNAL(timeout()), Print::point, SLOT(hanlde()));
#endif
	return true;
}

/*=================================
	作用：打印完走纸
=================================*/
void Print::goPaper()
{
	unsigned char send_go[] = {27, 100, 5};
	::write(fd, send_go, 3);
}

/*================================
	作用：打印换行
================================*/
void Print::clear()
{
	unsigned char send_clear[] = {10};
	::write(fd, send_clear, 1);
}

/*================================
	作用：打印GB2312汉字
================================*/
int Print::GB2313(QString str)
{
	return	::write(fd, QTextCodec::codecForName("GB2312")->fromUnicode(str).data(), 
			QTextCodec::codecForName("GB2312")->fromUnicode(str).count()); 
}

/*=================================
	作用：自检
=================================*/
void Print::check()
{
	unsigned char send_check[] = {0x1c, 0x76, 0x00};
	::write(fd, send_check, 3);
}

/*=================================
	作用：自检状态检查 true or false
=================================*/
int Print::status()
{
	unsigned char read_status[10];
	int ret = -1;

	if (::read(fd, read_status, 10) > 0) {
        	if (read_status[0] == 0x04)
                	ret = 0;
		else if (read_status[0] == 0x55)
			ret = 1;
	}
    //printf("ret ===%d\n",ret);
//char temp_str[40];
//char value_str[10];
//sprintf(value_str, "%03d", read_status[len - 1]);
//sprintf(temp_str, "%03d", len);
//QMessageBox::information(NULL, QObject::tr(value_str), QObject::tr(temp_str));

	return ret;
}

/*=================================
	作用：温度报警
=================================*/
void Print::Talarm(int net, int device, int reg, int value, QString time)
{
	char temp_str[40];

	if (enable_print != 1)
		return;
	if (no_paper == 1) {
		Message::_show(QObject::tr("打印机缺纸!"));
		return;
	} else if (no_paper == -1) {
		Message::_show(QObject::tr("打印机异常!"));
                return;
	}
	
	sprintf(temp_str, "%01d", net);
	QString net_str(temp_str);
//  QString head_str = "-----------网络1 报警-----------";	
	QString head_str = "-----------网络" + net_str + " 报警-----------";
	QString menu_str = "设备号  节点号  报警类型  报警值";
	
	sprintf(temp_str, "%03d", device);
//	QString value_str = "  01      01    超温报警  100 ℃";
	QString device_str(temp_str);
	QString value_str = "  " + device_str + "     ";
	sprintf(temp_str, "%02d", reg);
	QString reg_str(temp_str);
	value_str += reg_str;
	value_str += "    超温报警  ";
	sprintf(temp_str, "%03d", value);
	QString t_str(temp_str);
	value_str += t_str;
	value_str += " ℃";
//	QString value1_str = "  01      01    漏电报警  2000mA";
	QString end_str;
	QString t_head_str = "------ ";
	QString t_end_str = " -----";
	QString time_str = time;
	end_str = t_head_str + time_str + t_end_str;
	Print::GB2313(head_str);
	Print::clear();
	Print::GB2313(menu_str);
	Print::clear();
	Print::GB2313(value_str);
	Print::clear();
	Print::GB2313(end_str);
	Print::clear();
	Print::goPaper();
}

/*=================================
	作用：漏电报警
=================================*/
void Print::Calarm(int net, int device, int reg, int value, QString time)
{
	char temp_str[40];

	if (enable_print != 1)
		return;

        if (no_paper == 1) {
                Message::_show(QObject::tr("打印机缺纸!"));
                return;
        } else if (no_paper == -1) {
                Message::_show(QObject::tr("打印机异常!"));
                return;
        }

	
	sprintf(temp_str, "%01d", net);
        QString net_str(temp_str);
//	QString head_str = "-----------网络1 报警-----------";
	QString head_str = "-----------网络" + net_str + " 报警-----------";
	QString menu_str = "设备号  节点号  报警类型  报警值";
	
	sprintf(temp_str, "%03d", device);
        QString device_str(temp_str);
//	QString value_str = "  01      01    漏电报警  2000mA";
	QString value_str = "  " + device_str + "     ";
	sprintf(temp_str, "%02d", reg);
        QString reg_str(temp_str);
	value_str += reg_str;
	value_str += "    漏电报警  ";
	sprintf(temp_str, "%04d", value);
        QString c_str(temp_str);
	value_str += c_str;
	value_str += "mA";
	QString end_str;
	QString t_head_str = "------ ";
	QString t_end_str = " -----";
	QString time_str = time;
	end_str = t_head_str + time_str + t_end_str;
	Print::GB2313(head_str);
	Print::clear();
	Print::GB2313(menu_str);
	Print::clear();
	Print::GB2313(value_str);
	Print::clear();
	Print::GB2313(end_str);
	Print::clear();
	Print::goPaper();
}

/*=================================
	作用：本地报警
=================================*/
void Print::Local_alarm(int alarm_type, QString time)
{
	if (enable_print != 1)
		return;

        if (no_paper == 1) {
                Message::_show(QObject::tr("打印机缺纸!"));
                return;
        } else if (no_paper == -1) {
                Message::_show(QObject::tr("打印机异常!"));
                return;
        }
        

	QString head_str = "------------本地报警------------";
	QString menu_str = "设备号  节点号  报警类型  报警值";
	
	QString value_str;
	
	if (alarm_type == MAIN_NO)
		value_str = "  无      无    主电欠压    无  ";
	else if (alarm_type == PREMAIN_NO)
		value_str = "  无      无    备电欠压    无  ";
	else if (alarm_type == PREMAIN_ON)
		value_str = "  无      无    备电短路    无  ";
	else if (alarm_type == PREMAIN_OFF)
		value_str = "  无      无    备电断路    无  ";

	QString end_str;
	QString t_head_str = "------ ";
	QString t_end_str = " -----";
	QString time_str = time;
	end_str = t_head_str + time_str + t_end_str;
	Print::GB2313(head_str);
	Print::clear();
	Print::GB2313(menu_str);
	Print::clear();
	Print::GB2313(value_str);
	Print::clear();
	Print::GB2313(end_str);
	Print::clear();
	Print::goPaper();
}

void Print::hanlde()
{
	static int send_flag = 0;
	static int lost_times = 0;
	static int paper_times = 0;
	int temp;
	
	if (send_flag == 0) {
		Print::check();
		send_flag = 1;
	} else if (send_flag == 1) {
		send_flag = 0;
		temp = Print::status();
		if (temp == 0) {
			no_paper = 0;
			lost_times = 0;
			paper_times = 0;
		} else if (temp == 1) {
			paper_times++;
			lost_times = 0;
		} else if (temp == -1) {
			lost_times++;
			paper_times = 0;
		}
			
		if (lost_times == 3) {
			no_paper = -1;
			lost_times = 0;
		} else if (paper_times == 3) {
			no_paper = 1;
			paper_times = 0;
		}
	}

}
