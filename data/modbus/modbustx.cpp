
#include "modbustx.h"
// 功能码0x03

unsigned int ModbusTx::startAddr[] = {0,0};
unsigned int ModbusTx::startSize[] = {0,0};
int ModbusTx::timer = 50;

/*int ModbusTx::readMem(int net,int id,unsigned int addr,unsigned int size)
{
	struct mcpcan_data data;
	unsigned int addrCpy = addr -1;
	unsigned int crc;
	
	ModbusTx::startAddr[net] = addr;
	ModbusTx::startSize[net] = size;
	data.net = net;
	data.id = id;
	data.data[0] = id;
	data.data[1] = 0x03;
	data.data[2] = addrCpy >> 8;
	data.data[3] = addrCpy % 256;
	data.data[4] = size >> 8;
	data.data[5] = size % 256;
	crc = Crc::CRC16(data.data, 6);
	data.data[6] = crc % 256;
	data.data[7] = crc >> 8;
	data.DataLen =  8;
	Can::write(&data);
	haveLoogTimerGetDat(0x03,size);
	return 0;
}
*/

int ModbusTx::readMem(int net,int id,unsigned int addr,unsigned int size)
{
	struct mcpcan_data data;
	unsigned int addrCpy = addr -1;
	unsigned int crc;
	
	ModbusTx::startAddr[net] = addr;
	ModbusTx::startSize[net] = size;
	data.net = net;
	data.id = id;
	data.data[0] = id;
	data.data[1] = 0x03;
	data.data[2] = addrCpy >> 8;
	data.data[3] = addrCpy % 256;
	data.data[4] = size >> 8;
	data.data[5] = size % 256;
	crc = Crc::CRC16(data.data, 6);
	data.data[6] = crc % 256;
	data.data[7] = crc >> 8;
	data.DataLen =  8;
	
	if (net == 0)
		Can::write(Can::fd[0], &data.data[0], data.DataLen);
	else if (net == 1)
		Can::write(Can::fd[1], &data.data[0], data.DataLen);
	haveLoogTimerGetDat(0x03,size);
	return 0;
}

/*
// 功能码 0x10
int ModbusTx::writeMem(int net,int id,unsigned int addr,unsigned int size,unsigned int* data)
{
	struct mcpcan_data tmcp;
	char send[200];
	int sendLen = 7;
	int crc;
	unsigned int addrCpy = addr -1;
	ModbusTx::startAddr[net] = addr;
	ModbusTx::startSize[net] = size;
	int j=0;
	int sum=0;

	tmcp.net = net;
	tmcp.id = id;
	send[0] = id;
	send[1] = 0x10;
	send[2] = addrCpy >> 8;
	send[3] = addrCpy % 256;
	send[4] = size >> 8;
	send[5] = size % 256;
	send[6] = size * 2;
	for(int i = 0 ; i < size; i++)
	{
		send[i*2 + 7] = data[i] >> 8;
		send[i*2 + 8] = data[i] % 256;
		sendLen += 2;
	}
	crc = Crc::CRC16( send, sendLen);
	send[sendLen++] = crc % 256;
	send[sendLen++] = crc >> 8;
	//计算包发送的次数
	if(sendLen % 8 > 0 )
	{
		sum = sendLen / 8 + 1;
	}
	else
	{
		sum = sendLen / 8;
	}
	for(int k = 0; k < sum ; k++)
	{//分包发送
		if( k == (sum - 1) && sendLen % 8 )
		{
			tmcp.DataLen = sendLen % 8;
		}
		else
		{
			tmcp.DataLen = 8;
		}
        	for(j = 0; j< tmcp.DataLen; j++)
		{
			tmcp.data[j]=send[j+k*8];
		}
		Can::write(&tmcp);
	}
	haveLoogTimerGetDat(0x10,0);
	return 0;
}
*/

int ModbusTx::writeMem(int net,int id,unsigned int addr,unsigned int size,unsigned int* data)
{
	struct mcpcan_data tmcp;
	char send[200];
	int sendLen = 7;
	int crc;
	unsigned int addrCpy = addr -1;
	ModbusTx::startAddr[net] = addr;
	ModbusTx::startSize[net] = size;
	int j=0;
	int sum=0;

	tmcp.net = net;
	tmcp.id = id;
	send[0] = id;
	send[1] = 0x10;
	send[2] = addrCpy >> 8;
	send[3] = addrCpy % 256;
	send[4] = size >> 8;
	send[5] = size % 256;
	send[6] = size * 2;
	for(int i = 0 ; i < size; i++)
	{
		send[i*2 + 7] = data[i] >> 8;
		send[i*2 + 8] = data[i] % 256;
		sendLen += 2;
	}
	crc = Crc::CRC16( send, sendLen);
	send[sendLen++] = crc % 256;
	send[sendLen++] = crc >> 8;
	
	if (net == 0)
		Can::write(Can::fd[0], send, sendLen);
	else if (net == 1)
		Can::write(Can::fd[1], send, sendLen);
		
	haveLoogTimerGetDat(0x10,0);
	return 0;
}

void ModbusTx::haveLoogTimerGetDat(int cmd,unsigned size)
{
	if(cmd == 0x3)
	{
        ModbusTx::timer =((5 + size * 2) % 8 ? (5 + size * 2) / 8 + 1 : (5 + size * 2) / 8 + 1 ) * PAKETIMER;
        //printf("ModbusTx::timer===%d\n",ModbusTx::timer);//三目运算符不起作用，考虑优先级 当size为1时为30
        ModbusTx::timer *= 3;
	}
	else if(cmd == 0x10)
	{
        ModbusTx::timer = PAKETIMER*2;
	}
}

