#ifndef LINLONG_DATA_UP
#define LINLONG_DATA_UP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>

#define DL 100

//=======    命令      ==== 数值 ==== 解析 =====
#define  QUE_CUR_VAL	0X10	// r 当前数值命令
#define  QUE_WAR_VAL	0X11	// r 读取系统参数命令
#define  QUE_MOD_VAL	0x12	// r 设备型号信息命令
#define  QUE_DEV_WAR	0X13	// r 查询报警信息
#define  QUE_MOD_STA	0x14	// r 读取节点的状态
#define  SET_WAR_VAL 	0X51 	// w 设置模块参数
#define  SET_MOD_TRY	0x52	// w 需要模块试验
#define  ASN_CUR_VAL	0x70	// a 当前电流读取成功
#define  ASN_WAR_VAL    0x71    // a 系统参数读取成功
#define  ASN_MOD_VAL	0x72    // a 设备型号成功
#define  ASN_SET_WAR 	0X73 	// w 设置参数成功
#define  ASN_RES_MOD	0x74    // a 模块复位成功
#define  ASN_MOD_TRY    0x75    // a 模块试验成功



struct pake
{//接收数据的包
	unsigned int net;	//网络号
	unsigned int id;	//节点号
	unsigned int len;	//数据的长度
	unsigned char cmd;	//命令字节
	unsigned int  data[DL];	//数据
};

class Pake
{
public:
	//接收到的命令缓存
	static struct pake readBuf;
	//发送到的命令缓存
	static int head;
	static int end;
	static struct pake sendBuf[50];
	//填充包到链表 id id号 、cmd 命令、ic 数据的数组、len 数据的长度
	static int send(int net,int id,char cmd,int ic[],int len);
	static bool isHave();
	static bool next();
};

#endif
