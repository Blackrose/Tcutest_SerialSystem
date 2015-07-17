/*===============================
作用：处理串行接收的数据
作者：林龙
版本：1.0v
===============================*/

#ifndef LINLONG_MODBUSRX
#define LINLONG_MODBUSRX


class ModbusRx
{
public :
	static int dataStatus;
	static bool sendDataToPake(int net,int id);
};

#endif
