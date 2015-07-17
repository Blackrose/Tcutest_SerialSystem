/*===============================
作用：处理发送的数据
作者：林龙
版本：1.0v
===============================*/

#ifndef LINLONG_MODBUSTX
#define LINLONG_MODBUSTX

#include "can.h"
#include "crc.h"
#define PAKETIMER 30
class ModbusTx
{
public:
	static int timer;
	static unsigned int startAddr[2];
	static unsigned int startSize[2];
	// 功能码0x03
	static int readMem(int net,int id,unsigned int addr,unsigned int size);
	// 功能码 0x10 16 
	static int writeMem(int net,int id,unsigned int addr,unsigned int size,unsigned int* data);
	//计算需要多长时间才能有数据的返回
	static void haveLoogTimerGetDat(int cmd,unsigned size);
};

#endif

