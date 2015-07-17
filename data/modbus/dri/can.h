#ifndef LINLONG_CAN_LIN
#define LINLONG_CAN_LIN

#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>  
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "device/led/led.h"

struct mcpcan_data
{
	unsigned int net;
	unsigned int id;
	unsigned int DataLen;
	char data[9];
};
class Can
{
public:
	static int fd[3];
	static int open_flag;
	static int init();
	static int write(int fd, char *data, int len);
	static int read(int fd, char *data, int len);
//	static int write(struct mcpcan_data* arg);
//	static int read(struct mcpcan_data* arg);
	static int reSetNet(int net);
	static int fd_close();
//	static void sent_test();
//	static void rx_test();
};
#endif
