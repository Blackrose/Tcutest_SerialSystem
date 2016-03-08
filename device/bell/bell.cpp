#include "bell.h"
#include "main.h"

int Bell::fd = 0;
int Bell::flag = 0;
QTimer *Bell::timer;
Bell *Bell::point;
char Bell::warn_flag = 0;
char Bell::error_flag = 0;

int Bell::init()
{
	Bell::fd = open("/dev/pwm", O_RDWR);
	if (fd < 0)
	{
		printf("Open bell device failed.\n");
		return fd;
	}

	Bell::timer = new QTimer();
	Bell::point = new Bell;
	Bell::timer->start(HANDLE_MS);
	connect(Bell::timer, SIGNAL(timeout()), Bell::point, SLOT(hanlde()));
	Bell::warn_flag = 0;
	Bell::error_flag = 0;

	Bell::flag = 0;
    ::ioctl(Bell::fd, 0, 199);//199
	printf("---bell init ok---\n");
	return 1;
}
void Bell::write(char arg )
{
	int cmd;
	
	if (arg == '1')
		cmd = 1;
	else if (arg == '2')
		cmd = 0;
	else {
		printf("bell write failed, arg.\n");
		return;
	}
	if (Bell::fd < 0) {
		printf("bell write failed, fd.\n");
		return;
	}
	Bell::flag = cmd;
    ::ioctl(Bell::fd, cmd, 199);//199
}
void Bell::on()
{
    //printf("bell on\n");
	Bell::write('1');
}
void Bell::off()
{
     //printf("bell off\n");
	Bell::write('2');
}
void Bell::error()//故障
{
	Bell::error_flag = 1;
//	Bell::on();
	//Bell::write(2);
}
void Bell::warn()//报警
{
	Bell::warn_flag = 1;
//	Bell::on();
}
bool Bell::stats()
{
	if (Bell::flag > 0)
		return true;
	return false;
}
void Bell::hanlde()
{
	static unsigned long count = 0;

	count++;
	
    if (Bell::warn_flag && (!Main::flagnosound)) {//&& (!Main::flagnosound)
		Bell::on();
    } else if (Bell::error_flag && (!Main::flagnosound)) {
		if (count % 2)
			Bell::off();
		else
			Bell::on();
	} else {
		Bell::off();
		count = 0;
	}
}

