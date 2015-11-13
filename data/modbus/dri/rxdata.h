#ifndef LINLONG_PTH_RX
#define LINLONG_PTH_RX

#include "can.h"
#include "pake.h"
#include "modList.h"

#define NET   2
#define RXLEN 110
#define PAKELEN 100

//节点缓存结构体
struct NodeCache
{
	unsigned int len;	//数据尾
	char data[PAKELEN];//缓存数据
};

class RxThread
{
public:
	static void read();
	static struct NodeCache netData[2];
	static void clearNet0();
	static void clearNet1();
    static int WRONG1;
    static int WRONG2;
};
#endif
