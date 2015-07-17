
#include "com.h"

int Com::fd = -1;
// 初始化串口
bool Com::open(char *name)
{
	Com::fd = ::open( name, O_RDWR);
	if (-1 == Com::fd){
	/* 不能打开串口一*/ 
		return false;
	}
	return true;
}
//写下波特率
bool Com::set_speed(int speed)
{
	int status;
	struct termios Opt;

	::tcgetattr( Com::fd, &Opt);
	::tcflush( Com::fd, TCIOFLUSH);
	::cfsetispeed( &Opt, speed);
	::cfsetospeed( &Opt, speed);
	status = ::tcsetattr(Com::fd, TCSANOW, &Opt);
	if  (status != 0) {
		return false;
	}    
	::tcflush( Com::fd, TCIOFLUSH);
	return true;
}
/*
*@brief   设置串口数据位，停止位和效验位
*@param  databits 类型  int 数据位   取值 为 7 或者8
*@param  stopbits 类型  int 停止位   取值为 1 或者2
*@param  parity  类型  int  效验类型 取值为N,E,O,S
*/
bool Com::set_Parity(int databits,int stopbits,int parity)
{ 
	struct termios options; 
	if  ( tcgetattr( Com::fd, &options) != 0)
	{
		return false;  
	}
	options.c_cflag &= ~CSIZE; 
	switch (databits)
	{
		case 8:
			options.c_cflag |= CS8;
			break;
	}
	switch (parity)
	{
		case 'n':
		case 'N':    
			options.c_cflag &= ~PARENB;   /* Clear parity enable */
			options.c_iflag |= INPCK;     /* Enable parity checking */ 
			break;
	}  
	/* 设置停止位*/  
	switch (stopbits)
	{   
		case 1:    
			options.c_cflag &= ~CSTOPB;  
			break;
	}
	//tcflush( Com::fd, TCIFLUSH);
	options.c_cc[VTIME] = 0; /* 设置超时15 seconds*/
	options.c_cc[VMIN] = 0; /* Update the options and do it NOW */

	options.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);/*Input*/
	options.c_oflag  &= ~OPOST;/*Output*/

	if (tcsetattr(Com::fd, TCSANOW, &options) != 0)
	{ 
		return false;  
	} 
	return true;
}
int Com::read(void * read, int len)
{
	return ::read(Com::fd, read, len);
}
int Com::write(void * write, int len)
{
	return ::write(Com::fd, write, len);
}
void Com::close()
{
	if( Com::fd != -1)
		::close(Com::fd);
	Com::fd = -1;
}

