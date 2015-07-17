#include "can.h"
#include "sys_set.h"

int Can::fd[3] = {-1, -1, -1};
int Can::open_flag = 0;

/*
void Can::sent_test()
{
	static unsigned char data1[13] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa};
	static unsigned char data2[13] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa};
	static unsigned char data3[13] = {0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xff, 0xee, 0xdd, 0xcc, 0xbb, 0xaa};

	if ((Can::fd[0] > 0) && (Can::fd[1] > 0) && (Can::fd[2] > 0) && (Can::open_flag == 1)) {
		::write(Can::fd[0], data1, 13);
		::write(Can::fd[1], data2, 13);
		::write(Can::fd[2], data3, 13);
	}
}

void Can::rx_test()
{
	unsigned char data[20];
	int len;
	
	if (Can::fd[0] > 0) {
		len = ::read(Can::fd[0], data, 20);
		if (len > 0) {
			printf("usart1 rx data is: ");
			for (int i = 0; i < len; i++)
				printf("%02x", data[i] );
			printf("\n");
		}
	}

	if (Can::fd[1] > 0) {
		len = ::read(Can::fd[1], data, 20);
       		if (len > 0) {
               		printf("usart2 rx data is: ");
                	for (int i = 0; i < len; i++)
                        	printf("%02x", data[i] );
                	printf("\n");
		}
        }
	
	if (Can::fd[0] > 0) {
		len = ::read(Can::fd[2], data, 20);
        	if (len > 0) {
                	printf("usart3 rx data is: ");
                	for (int i = 0; i < len; i++)
                        	printf("%02x", data[i] );
                	printf("\n");
		}
        }
}
*/

int Can::init()
{
	Can::fd[0] = ::open("/dev/ttySAC1",O_RDWR);
	Can::fd[2] = ::open("/dev/ttySAC2",O_RDWR);
	Can::fd[1] = ::open("/dev/ttySAC3",O_RDWR);
	if ((Can::fd[0] < 0) || (Can::fd[1] < 0) || (Can::fd[2] < 0))
	{
		printf("Open can device failed.\n");
		Can::fd_close();
		return -1;
	}
	SysSet::usart1_config(Can::fd[0]);
	SysSet::usart2_config(Can::fd[1]);
	SysSet::usart3_config(Can::fd[2]);
	Can::open_flag = 1;
	printf("---can ok---\n");
	return 1;
}
/*
int  Can::write(struct  mcpcan_data* arg )
{
	//int ret = ::write(Can::fd, arg, sizeof(struct mcpcan_data));
	int ret = -1;
	if( ret == -1)
	{ 
		return ret;
	}
	printf("ret = %d write net = %d, id = %d, len = %d, data = ", ret ,arg -> net , arg ->id , arg -> DataLen);
	for ( int i  = 0 ; i < arg -> DataLen ; i ++)
	{
		printf("%x ",arg->data[i]);
	}
	printf("\n");
	return ret;
}*/

int  Can::write(int fd, char *data, int len)
{
	int ret = -1;
	if ((fd > 0) && (data != NULL) && (len > 0))
		ret = ::write(fd, data, len);
	
	return ret;
}

int Can::reSetNet(int net)
{
	struct mcpcan_data arg;
	arg.net = net + 2;
	arg.id = 0;
	arg.DataLen = 0;
//	::write(Can::fd, &arg, sizeof(struct mcpcan_data));
}

/*
int Can::read(struct mcpcan_data* arg)
{	
	//int ret = ::read(Can::fd, arg, sizeof(struct mcpcan_data));
	int ret = -1;
	if(ret == 1)
	{
		printf("net = %d; id = %d; len = %d; data = ", arg -> net , arg ->id , arg -> DataLen);
		for ( int i  = 0 ; i < arg -> DataLen ; i ++)
		{
			printf("%x ",arg->data[i]);
		}
		printf("\n");
	}
	return ret;
}
*/

int Can::read(int fd, char *data, int len)
{
	int ret = -1;
	
	if ((fd > 0) && (data != NULL) && (len > 0))
		ret = ::read(fd, data, len);
	
	return ret;
}

int Can::fd_close()
{
	if (fd[0] > 0) {
		::close(fd[0]);
		fd[0] = -1;
	}
	
        if (fd[1] > 0) {
                ::close(fd[1]);
                fd[1] = -1;
        }

        if (fd[2] > 0) {
                ::close(fd[2]);
                fd[2] = -1;
        }

	Can::open_flag = 0;
}

