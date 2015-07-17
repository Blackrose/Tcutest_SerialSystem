#ifndef MHW_BELL
#define MHW_BELL

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>  
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h> 
#include <QTimer>
#include <QObject>

#define HANDLE_MS 1000

class Bell : public QObject
{
	Q_OBJECT

public:
	static QTimer *timer;
	static Bell *point;
	static char warn_flag;
	static char error_flag;
	static int fd;
	static int flag;
	static int init(); //初始化
	/*   arg = ’1‘   响
	     arg = ‘2’   停止响
	*/
	static void write(char arg);
	static bool stats();
	static void on();//响
	static void off();//停止响
	static void error();//故障
	static void warn();//报警 

private slots:
	static void hanlde(void);
};
#endif

