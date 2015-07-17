/*==============================================
	 系统设置界面
==============================================*/
#ifndef LINLONG_SysSet
#define LINLONG_SysSet

#include "ui_sys_set.h"

#include "sql/mater.h"
#include "keyboard/imframe.h"

#include <QWidget>
#include <QMessageBox>
#include <time.h>
#include <QDate>
#include <QTime>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <QTimer>
#include <QProcess>

enum BADU_RATE_TYPE {
	BAUD1200 = 1200,
	BAUD2400 = 2400,
	BAUD4800 = 4800,
	BAUD9600 = 9600,
	BAUD19200 = 19200,
	BAUD38400 = 38400,
	BAUD57600 = 57600,
	BAUD115200 = 115200
};

enum PARITY_TYPE {
	PARITY_NONE = 0,
	PARITY_ODD = 1,
	PARITY_EVEN = 2
};

enum DATA_TYPE {
	DATA_EIGHT = 0,
	DATA_SEVEN = 1,
	DATA_SIX = 2
};

enum STOP_TYPE {
	STOP_ONE = 0,
	STOP_ONE_FIVE = 1,
	STOP_TWO = 2
};

class  SysSet:public QWidget,public Ui_SysSetForm
{
        Q_OBJECT
public :
	IMFrame *imf;
        SysSet(IMFrame *im,QWidget* parent = NULL);
	virtual bool eventFilter( QObject * watched, QEvent *event);
        virtual ~SysSet();
	void initSystime();
	void setSysTime();
	void _show();
	bool isAbigB(struct tm* a,struct tm* b);
	void usart_reset(QComboBox *usart, const QString &text);
	void usart1_reset(const QString &baudrate, const QString &parity, const QString &data, const QString &stop);
	void usart2_reset(const QString &baudrate, const QString &parity, const QString &data, const QString &stop);
	void usart3_reset(const QString &baudrate, const QString &parity, const QString &data, const QString &stop);
	void usart_set_common(QComboBox *usart, const QString &text);
	void usart1_set(const QString &baudrate, const QString &parity, const QString &data, const QString &stop);
	void usart2_set(const QString &baudrate, const QString &parity, const QString &data, const QString &stop);
	void usart3_set(const QString &baudrate, const QString &parity, const QString &data, const QString &stop);
	static void usart_config_common(
                int fd, const QString &baudrate, const QString &parity,
                const QString &data, const QString &stop);
        static void usart1_config(int fd);
        static void usart2_config(int fd);
        static void usart3_config(int fd);
public slots:
	void usart_set();
	void reset();
	void ok();
	void clear_warn();
	void clear_opt();
	void touch_calibration();
	void txtChange(const QString &str);
	void txtChange_(const QString &str);
	void set();
	void resend();
//	void on_pushbutton_clicked();
};
#endif
