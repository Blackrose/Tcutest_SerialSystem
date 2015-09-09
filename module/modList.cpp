#include <modList.h>
#include <stdio.h>
#include <string.h>
#include "mater.h"
#include "main/main.h"

struct mod* Module::mod_list = NULL;
struct nodeModName* Module::moTyp = NULL;

Module::Module()
{
	mod_list = new struct mod[MODCOUNT];
	moTyp = new struct nodeModName[DL1T1+1];

	if(mod_list == NULL || moTyp == NULL)
	{
		printf("mod_list or moTyp new error !\n");
	}
	//sum = 0;
	for(int i = 0 ; i < MODCOUNT ; i++)
	{
		mod_list[i].isHave = false;
		mod_list[i].sn = NO_SN;
		mod_list[i].flag = NORMAL;//0 掉线  1 正常  2 报警 
		for(int j = 0; j < SUBNODECOUNT ; j++)
		{
			mod_list[i].subNodIsWar[j] = NORMAL;
		}
        for(int j = 0; j < SUBNODECOUNT ; j++)
        {
            mod_list[i].recovery[j] = NORMAL;
        }
		mod_list[i].isReset = false;
	}
   
 	strcpy( moTyp[MC].name, "MC");
 	strcpy( moTyp[ML1].name, "SL6010C");
 	strcpy( moTyp[MT1].name, "SL6001C");
 	strcpy( moTyp[ML1T1].name, "SL6F11");
 	strcpy( moTyp[ML2].name, "SL6020C");
 	strcpy( moTyp[MT2].name, "SL6002C");
 	strcpy( moTyp[ML2T2].name, "SL6022C");
 	strcpy( moTyp[ML4].name, "SL6040C");
 	strcpy( moTyp[MT4].name, "SL6004C");
	strcpy( moTyp[ML4T4].name, "SL6F44");
	strcpy( moTyp[ML8].name, "SL6F80");
 	strcpy( moTyp[MT8].name, "SL6008C");
	strcpy( moTyp[DL1T1].name, "SL6D11");

	net0All = Mater::readNet0Count();
    if (net0All > BtnNodeNUm)
        net0All = BtnNodeNUm;
	net1All = Mater::readNet1Count();
        if (net1All > BtnNodeNUm)
                net1All = BtnNodeNUm;
	int i ;
    for(i = 0; i < net0All && i < BtnNodeNUm; i++)
	{
		mod_list[i].isHave = true;
	}
    for(i = 0; i < net1All && i < BtnNodeNUm; i++)
	{
        mod_list[BtnNodeNUm + i].isHave = true;
	}
}
Module::~Module()
{
	delete[] mod_list;
	delete[] moTyp;
}
bool Module::nodeIsHave(int net, int id)//是否有节点
{
    int i = net * BtnNodeNUm + id-1;
	if( i >= MODCOUNT) return false;
	if(mod_list[i].isHave == true)
	{
		return true;
	}
	return false;
}
//返回sn
int Module::getSN(int net,int id)
{
    int i = net * BtnNodeNUm + id-1;
	if( i >= MODCOUNT) return 0;
	return mod_list[i].sn;
}
//==============注销=============
void Module::unreg(int net,int id)
{
    int i = net * BtnNodeNUm + id-1;
	if(i >= MODCOUNT) return;
	mod_list[i].isHave = true;
	mod_list[i].sn = NO_SN;
	mod_list[i].flag = ERROR;//0 掉线  1 正常 2 预警 3 报警 
	for(int j = 0 ; j < SUBNODECOUNT;  j++)
	{
		mod_list[i].subNodIsWar[j] = NORMAL ;
	}
}
//===============返回节点数==============
int Module::nodeCount(int net)
{
	int sum = 0;
    int count = ( net + 1 ) * BtnNodeNUm;
	if(count > MODCOUNT) return 0;
    for(int i = net*BtnNodeNUm ; i <  count; i++)
	{
		if(mod_list[i].isHave == true )
			 sum ++;
	}
	return sum;
}
//============返回一个节点指针============
struct mod* Module::getNode(int net,int id)
{
    int i = net * BtnNodeNUm + id-1;
	if( i >= MODCOUNT) return NULL;
	return &mod_list[i];
}
//================打印===============
void Module::display(int net,int id)
{
    int i = net * BtnNodeNUm + id-1;
	if( i >= MODCOUNT) return;
	//for(int i = 0; i < MODCOUNT; i ++)
	//{
	if(mod_list[i].isHave == true)
	{
		printf("mod_list[%d].isHave = %d \n", i,mod_list[i].isHave);//是否有这一个设备 false 没有 ,true 有
		printf("mod_list[%d].isReset = %d \n", i,mod_list[i].isReset);//是否复位过
		printf("mod_list[%d].sn= %d \n",i,mod_list[i].sn);//产品型号 0 没有注册型号
		printf("mod_list[%d].flag= %d \n",i,mod_list[i].flag);// 0 掉线  1 正常 2 预警 3 报警
	}
	//}
}
//=================清除报警===============
void Module::cleWarn(int net,int id)
{
    int i = net * BtnNodeNUm + id -1 ;
	if( i >= MODCOUNT ) return;
	mod_list[i].flag = NORMAL;
	for(int j = 0 ; j < SUBNODECOUNT;  j++)
	{
		mod_list[i].subNodIsWar[j] = NORMAL ;
	}
}
//=================清除报警===============
void Module::cleSubWarn(int net,int id)
{
    int i = net * BtnNodeNUm + id -1 ;
	if( i >= MODCOUNT ) return;
	for(int j = 0 ; j < SUBNODECOUNT;  j++)
	{
		mod_list[i].subNodIsWar[j] = NORMAL ;
	}
}
//================= 写下子节点报警 ===============
void Module::setSubWarn(int net,int id,int subId,int flag,int value)
{
    int i = net * BtnNodeNUm + id - 1;
	if( i >= MODCOUNT || subId >= SUBNODECOUNT) return;
	mod_list[i].subNodIsWar[subId] = flag;
	mod_list[i].flag = NORMAL;
	mod_list[i].subNodValue[subId] = value;
	Db::copyTime(mod_list[i].subNodTimer[subId].time);
	mod_list[i].flag = flag;
}
/*====================================
	功能：返回节点是否报警；
	net：网络号；
	id：节点号；
	subId：子节点号；
=====================================*/
bool Module::getSubWarn(int net, int id , int subId)
{
    int i = net* BtnNodeNUm + id -1 ;
	if( i >= MODCOUNT || subId >= SUBNODECOUNT) return false;
	if(mod_list[i].subNodIsWar[subId] == WARN)
	{
		return true;
	}
	return false;
}

//================= 写下子节点故障 ===============
void Module::setSubError(int net, int id, int subId, int flag)
{
    int i = net * BtnNodeNUm + id - 1;
	if( i >= MODCOUNT || subId >= SUBNODECOUNT) return;
	mod_list[i].subNodIsWar[subId] = flag;
	mod_list[i].flag = NORMAL;
    mod_list[i].subNodValue[subId] = ERROR;
	Db::copyTime(mod_list[i].subNodTimer[subId].time);
    mod_list[i].flag = flag;//WARN change by zhq 8.6
    mod_list[i].recovery[subId] = flag;
}

/*====================================
	功能：返回节点是否故障；
	net：网络号；
	id：节点号；
	subId：子节点号；
=====================================*/
bool Module::getSubError(int net, int id, int subId)
{
    int i = net* BtnNodeNUm + id -1 ;
	if( i >= MODCOUNT || subId >= SUBNODECOUNT) return false;
	if(mod_list[i].subNodIsWar[subId] == ERROR)
	{
		return true;
	}    
	return false;
}
/*====================================
    功能：返回节点是否恢复故障；
    net：网络号；
    id：节点号；
    subId：子节点号；
=====================================*/
bool Module::getSubErrorRecovery(int net, int id, int subId)
{
    int i = net* BtnNodeNUm + id -1 ;
    if( i >= MODCOUNT || subId >= SUBNODECOUNT) return false;
    if(mod_list[i].recovery[subId] == ERROR)
    {
        return true;
    }
    return false;
}

//=============== 返回报警的数量  ==============
int Module::warnCount(int net)
{
	int sum = 0;
    int i = net * BtnNodeNUm;
	if(i > MODCOUNT ) return 0;
    int count = (net + 1)*BtnNodeNUm;
	if(count > MODCOUNT ) return 0;
	for(; i < count ; i++)
	{
		if(mod_list[i].flag == WARN && mod_list[i].isHave == true)
		{
			sum++;
		}
	}
	return sum;
}
//========= 报警总算 =======
int Module::warnCount()
{
	int sum = 0;
	for(int i = 0; i < MODCOUNT; i++)
	{
        for(int j=0;j<SUBNODECOUNT;j++)
        {
            if(mod_list[i].subNodIsWar[j] == WARN && mod_list[i].isHave == true)
            {
                sum++;
            }
        }
	}
	return sum;
}
//============ 故障总数 ===============
int Module::errorCount()
{
	int sum = 0;
	for(int i=0; i < MODCOUNT; i++)
	{
        for(int j=0;j<SUBNODECOUNT;j++)
        {
            if(mod_list[i].subNodIsWar[j] == ERROR  && mod_list[i].isHave == true)
            {
                sum++;
            }
        }
        if(mod_list[i].flag == UNABLE && mod_list[i].isHave == true)
        {
            sum++;
        }
	}
    if( Main::mainpower || Main::prepower || Main::onStat || Main::offStat )
    {
        sum++;
    }
	return sum;
}

//============ 报警故障总数 ===============
int Module::warnerrorCount(int net)
{
    int sum = 0;
    int i = net * BtnNodeNUm;
    if(i > MODCOUNT ) return 0;
    int count = (net + 1)*BtnNodeNUm;
    if(count > MODCOUNT ) return 0;
    for(; i < count; i++)
    {
        for(int j=0;j<SUBNODECOUNT;j++)
        {
            if(mod_list[i].subNodIsWar[j] == WARN  && mod_list[i].isHave == true)
            {
                sum++;
            }
            if(mod_list[i].subNodIsWar[j] == ERROR  && mod_list[i].isHave == true)
            {
                sum++;
            }
        }
        if(mod_list[i].flag == UNABLE && mod_list[i].isHave == true)
        {
            sum++;
        }
    }
    if( Main::mainpower || Main::prepower || Main::onStat || Main::offStat )
    {
        sum++;
    }
    return sum;
}


//============ 报警故障总数 ===============
int Module::warnerrorCount()
{
    int sum = 0;
    for(int i=0; i < MODCOUNT; i++)
    {
        for(int j=0;j<SUBNODECOUNT;j++)
        {
            if(mod_list[i].subNodIsWar[j] == WARN  && mod_list[i].isHave == true)
            {
                sum++;
            }
            if(mod_list[i].subNodIsWar[j] == ERROR  && mod_list[i].isHave == true)
            {
                sum++;
            }
        }
        if(mod_list[i].flag == UNABLE && mod_list[i].isHave == true)
        {
            sum++;
        }
    }
    if( Main::mainpower || Main::prepower || Main::onStat || Main::offStat )
    {
        sum++;
    }
    return sum;
}

//================返回 sn=============
int Module::getNodeSN(int net,int id)
{
    int i = net * BtnNodeNUm + id - 1 ;
	if( i >= MODCOUNT ) return NO_SN;
	return mod_list[i].sn;
}
//================== 注册 sn===================
bool Module::regSN(int net,int id,int sn)
{
    int i = net * BtnNodeNUm + id -1;
	if (i >= MODCOUNT) return false;
	if (sn >= MC && sn <= DL1T1)//新修改
	{
		mod_list[i].sn = sn;
	}
	return true;
}
// -1 没有网络,0 只有 0 网络, 1 只有 1 网络,2 两个网络都有 ,
int Module::getNet()
{
	int ret = -1;
	for(int i = 0; i < MODCOUNT ; i++)
	{
		if(mod_list[i].isHave == true)
		{
            if( i < BtnNodeNUm)
			{
				ret = 0;
			}
			else
			{
				if(ret == 0)
				{
				 	ret = 2;
					return ret;
				}
				else
				{ 
					ret = 1;
					return ret;
				}
			}
		}
	}
	return ret;
}
int  Module::getNodeStats(int net,int id)//返回节点的状态 
{
    int i = net * BtnNodeNUm + id -1;
	if(i >= MODCOUNT ) return -1;
	return mod_list[i].flag;
}
 int  Module::s_getNodeStats(int net,int id)//返回节点的状态 
{
    int i = net * BtnNodeNUm + id -1 ;
	if(i >= MODCOUNT ) return -1;
	return mod_list[i].flag;
}
bool Module::getIsReset(int net, int id)
{
    int i = net * BtnNodeNUm + id -1;
	if(i >= MODCOUNT ) return false;
	return mod_list[i].isReset;
}
//写下复位状态
void Module::setIsReset(int net, int id,bool val)
{
    int i = net * BtnNodeNUm + id -1 ;
	if(i >= MODCOUNT ) return;
	mod_list[i].isReset = val;
}
/*====================================
	功能：返回报警的类型；
	net：网络号；
	id：节点号；
	subId：子节点号；
	返回值：0 ＝ 温度；1＝电流；2＝漏电
=====================================*/
int Module::getWhatWarn(int net,int id,int subId)
{
    int i = net * BtnNodeNUm + id - 1;
	if(i >= MODCOUNT ) return 0;
	if(mod_list[i].isHave == true)
	{
		if(mod_list[i].sn == MC)
		{
			switch(subId)
			{
				case 0:
				case 1:
				case 2:
					return 1;
				case 3:
					return 2;
				case 4:
				case 5:
					return 0;
			}
		}
		else if ((mod_list[i].sn == ML4T4) || (mod_list[i].sn == ML1T1) || (mod_list[i].sn == DL1T1))
		{
			if(subId > 0x03)
			{ 
				return 0;
			}
			else
			{
				return 2;
			}
		}
		else if(mod_list[i].sn == ML8)
		{
			return 2;
		}
	}
	return -1;
}
/*====================================
    功能：返回故障的类型；
    net：网络号；
    id：节点号；
    subId：子节点号；
    返回值：0 ＝ 温度；1＝电流；2＝漏电
=====================================*/
int Module::getWhatErr(int net,int id,int subId)
{
    int i = net * BtnNodeNUm + id - 1;
    if(i >= MODCOUNT ) return 0;
    if(mod_list[i].isHave == true)
    {
        if(mod_list[i].sn == MC)
        {
            switch(subId)
            {
                case 0:
                case 1:
                case 2:
                    return 1;
                case 3:
                    return 2;
                case 4:
                case 5:
                    return 0;
            }
        }
        else if ((mod_list[i].sn == ML4T4) || (mod_list[i].sn == ML1T1) || (mod_list[i].sn == DL1T1))
        {
            if(subId > 0x03)
            {
                return 0;
            }
            else
            {
                return 2;
            }
        }
        else if(mod_list[i].sn == ML8)
        {
            return 2;
        }
    }
    return -1;
}

/*====================================
	功能：返回节点的报警信息；
	net：网络号；
	id：节点号；
	subId：子节点号；
	time：传递报警时间的参数；
	value：报警的数值；
=====================================*/
void Module::getWarnTimeAndVal(int net,int id,int subId,char** time,int* value)
{
    int i = net * BtnNodeNUm + id -1;
	if( i >= MODCOUNT || subId >= SUBNODECOUNT) return;
	*time = mod_list[i].subNodTimer[subId].time;
	*value = mod_list[i].subNodValue[subId];
}

//=============== 试验  ==============
int Module::TryAllNode(int net)
{
    if(net == 0)
    {
        for(int i = 0; i < BtnNodeNUm; i++)
        {
            if(mod_list[i].flag != UNABLE && mod_list[i].isHave == true)
            {
                Pake::send( net, i+1, SET_MOD_TRY, NULL, 0);
            }
        }
    }
    else
    {
        for(int i = BtnNodeNUm; i < MODCOUNT; i++)
        {
            if(mod_list[i].flag != UNABLE && mod_list[i].isHave == true)
            {
                Pake::send( net, (i+1)%BtnNodeNUm, SET_MOD_TRY, NULL, 0);
            }
        }
    }

    return 1;
}
