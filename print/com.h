#ifndef LINLONG_COM
#define LINLONG_COM


#include     <QThread>
#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix 标准函数定义*/
#include     <sys/types.h>  
#include     <sys/stat.h>   
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX 终端控制定义*/
#include     <errno.h>      /*错误号定义*/

class Com
{
public:
	static int fd;
	static bool open(char *name); //初始化
	static bool set_speed(int speed);//设置波特率
	static bool set_Parity(int databits,int stopbits,int parity);
	static int read(void * read, int len);
	static int write(void * write, int len);
	static void close();
};
#endif
