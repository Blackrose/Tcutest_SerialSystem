#include "rxdata.h"
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int RxThread::WRONG1 = 0;
int RxThread::WRONG2 = 0;
struct NodeCache RxThread::netData[] = {{0,{0}},{0,{0}}};
/*
void RxThread::read()
{
	//循环读取数据
	struct mcpcan_data pake;
	int i = 0;
	clearNet0();
 	clearNet1();
	while( Can::read(&pake) && i++ < 30 )
	{
		if(pake.net == 0)
		{
			for(int i = 0 ; i < pake.DataLen && netData[0].len < PAKELEN; i ++)
			{
				netData[0].data[netData[0].len++] = pake.data[i];
			}
		}
		else if(pake.net == 1)
		{
			for(int i = 0 ; i < pake.DataLen && netData[1].len < PAKELEN; i++)
			{
				netData[1].data[netData[1].len++] = pake.data[i];
			}
		}
	}
}
*/

void RxThread::read()
{
	struct mcpcan_data pake;
	char data[PAKELEN];
	int i = 0;
	int len;
	clearNet0();
 	clearNet1();
	
    len = Can::read(Can::fd[0], data, PAKELEN);WRONG1 = 0;
    if (len) {
        //printf("usart1 rx len is %d, data is:", len);
		for(int i = 0; i < len && netData[0].len < PAKELEN; i++) {
            /*if(data[1] > 0x10 || data[3] == 0xfd){
                WRONG1 = 1;
                printf("wrong1\n");
            }else*/{
                netData[0].data[netData[0].len++] = data[i];
            }
            //printf(" %02x", data[i]);
		}
        //printf("\n");
	}
	
    len = Can::read(Can::fd[1], data, PAKELEN);WRONG2 = 0;
    if (len) {
        //printf("usart2 rx len is %d, data is:", len);
		for(int i = 0; i < len && netData[1].len < PAKELEN; i++) {
            /*if(data[1] > 0x10 || data[3] == 0xfd){
                WRONG2 = 1;
                printf("wrong2\n");
            }else*/{
                netData[1].data[netData[1].len++] = data[i];
            }
            //printf(" %02x", data[i]);
		}
        //printf("\n");
	}
}

void RxThread::clearNet0()
{
	netData[0].len = 0;
}
void RxThread::clearNet1()
{
	netData[1].len = 0;
}
