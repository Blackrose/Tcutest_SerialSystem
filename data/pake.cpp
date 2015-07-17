#include "pake.h"

struct pake Pake::readBuf = { 0, 0, 0, 0,{0} };
struct pake Pake::sendBuf[] = { { 0, 0, 0, 0,{0}}};
int Pake::head = 0;
int Pake::end = 0;

//================= 发送包进入发送链表 ================
int Pake::send(int net,int id,char cmd,int ic[],int len)
{	
	sendBuf[head].net = net;
	sendBuf[head].id = id;
	sendBuf[head].cmd = cmd;
	for(int i = 0 ; i < len; i ++ )
	{
		sendBuf[head].data[i] = ic[i];
	}
	head = ++head % 50;
}
bool Pake::isHave()
{
	if(head != end ) return true;
	return false;
}
bool Pake::next()
{
	end = ++ end % 50;
}
