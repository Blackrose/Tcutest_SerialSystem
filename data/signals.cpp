#include "signals.h"
#include "main.h"
#include "nodeStatus.h"
#include "Mset.h"
#include "pake.h"
#include "modbustx.h"
#include "modbusrx.h"
#include "mater.h"
#include "modList.h"

//int dbuf[8]={0};
int Signals::netCount[] = {0,0};
int Signals::timer = 0;
unsigned int Signals::errorFlag = 0;
unsigned int Signals::Flagerror[] = {0,0};

Signals::Signals()
{
	netCurId[0] = 1;
	netCurId[1] = 1;
	netTimer[0] = 0; //网络0从发次数
	netTimer[1] = 0; //网络1从发次数
	timer = 0;
	insertTimer = 0;
	si_i = 0;
	isRun = true;
}
void Signals::send()
{
	RxThread::read();

	if(isRun == true)
	{//处理轮询信息
        //printf("enter doNet\n");
        doNet(1);
        doNet(0);
	}
	else
	{//处理插入需要发送的信息
        //printf("enter doInsert\n");
        doInsert();
	}		
	if( Pake::isHave() == false)
    {//没有插入的信息需要发送继续轮询
        //printf("enter sendNet\n");
		isRun = true;
        sendNet(1);
        sendNet(0);
	}
	else
	{//发送插入的信息
        //printf("enter sendInsert isRun = false\n");
		isRun = false;
		sendInsert();
	}
//printf("111ModbusRx::dataStatus==%d\n",ModbusRx::dataStatus);
    if(Main::com_led==1)
    {
        if (ModbusRx::dataStatus == 0)
        {//没数据
            Led::commLightOff();
        }
        else if (ModbusRx::dataStatus == 1)
        {//crc 错误
            si_i = ++ si_i % 2;
            if ( si_i == 1 )
                Led::commLightOn();
            else if(si_i == 0)
                Led::commLightOff();
        }
        else if (ModbusRx::dataStatus == 2)
        {//id error
            si_i = ++ si_i % 20;
            if ( si_i == 0)
                Led::commLightOn();
            else if(si_i == 2)
                Led::commLightOff();
        }
        else if (ModbusRx::dataStatus == 3)
        {//data error
            si_i = ++ si_i % 10;
            if ( si_i == 0)
                Led::commLightOn();
            else  if(si_i == 5)
                Led::commLightOff();
        }
        else if (ModbusRx::dataStatus == 4)
        {//right
        //	if(Main::com_led==1)
        //	{
            //printf("now ModbusRx led on or off\n");
                si_i = ++ si_i % 10;//原来为60
                if ( si_i == 1)
                    Led::commLightOn();
                else  if(si_i == 6)//原来为20
                    Led::commLightOff();
        //	}
        //	else
        //	{
        //		Led::commLightOn();
        //	}
        }
    }
	
}
void Signals::doNet(int net)
{//printf("enter doNet net==%d\n",net);
	//网络故障处理
	if(netCount[net] > 0)
	{//是否有节点
        //if((RxThread::WRONG1 == 0 && net == 0)|| (RxThread::WRONG2 == 0 && net == 1)){//printf("RxThread::WRONG == 0\n");
            if ( ModbusRx::sendDataToPake(net , netCurId[net]) == false)
            {//节点掉线处理
                Can::reSetNet(net);
                mo = ((Main*)p_main)->p_mod -> getNode( net, netCurId[net]);
                if(mo->flag == UNABLE)//ERROR
                {
                    netCurId[net] = ++netCurId[net] % netCount[net];
                    if(netCurId[net] == 0 ) netCurId[net] = netCount[net];
                    netTimer[net] = 0;
                }
                else if(netTimer[net]++ >= timer )
                {printf("net==%d netCurId[net]==%d\n",net,netCurId[net]);
                    ((Main*)p_main)->slot_error( net, netCurId[net]);//故障
                    netCurId[net] = ++netCurId[net] % netCount[net];
                    if(netCurId[net] == 0 ) netCurId[net] = netCount[net];
                    netTimer[net] = 0; //网络0从发次数
                }
            }
            else
            {
                ((Main*)p_main)->slot_reg( net, netCurId[net]);
                netCurId[net] = ++netCurId[net] % netCount[net];
                if(netCurId[net] == 0 ) netCurId[net] = netCount[net];
                netTimer[net] = 0;
                toDo();
            }
        }
    //}
}
void Signals::sendNet(int net)
{    
	if(netCount[net] > 0)
	{
		mo = ((Main*)p_main)->p_mod -> getNode( net, netCurId[net]);
		if(mo->sn == 0)
		{//读取SN
            //printf("------SN\n");
			ModbusTx::readMem( net, netCurId[net], 201, 1);
		}
		else if(mo->isReset == true)
		{//节点复位
			unsigned int data[1];
			data[0] = 1;
			ModbusTx::writeMem(net, netCurId[net], 401, 1, data);            
		}
		else 
		{//节点轮询
            //printf("sendNet  %d======\n",net);
			ModbusTx::readMem( net, netCurId[net], 25, 2);            
		}
	}
}
void Signals::doInsert()
{printf("enter doInsert pak->net==%d pak->id==%d\n",pak->net,pak->id);
    //if((RxThread::WRONG1 == 0 && pak->net == 0)|| (RxThread::WRONG2 == 0 && pak->net == 1)){//printf("RxThread::WRONG == 0\n");
        if ( ModbusRx::sendDataToPake( pak->net, pak->id) == false)
        {//节点掉线处理
            Can::reSetNet(pak->net);
            mo = ((Main*)p_main)->p_mod -> getNode( pak->net, pak->id);
            if(mo->flag == UNABLE)//ERROR
            {
                Pake::next();
                insertTimer = 0;
            }
            else if ( insertTimer++ >= timer)
            {
                Pake::next();
                insertTimer = 0;
                ((Main*)p_main)->slot_error( pak->net, pak->id);
            }
        }
        else
        {
            toDo();
            Pake::next();
            insertTimer = 0;
            ((Main*)p_main)->slot_reg(pak->net, pak->id);
        }
    //}
} 
void Signals::sendInsert()
{
	pak = &Pake::sendBuf[Pake::end];
	switch(pak -> cmd)
	{
		case QUE_DEV_WAR://读取设备的报警值
			ModbusTx::readMem( pak->net, pak->id, 1, 8);
			break;
		case QUE_CUR_VAL://读取设备的当前值
			ModbusTx::readMem( pak->net, pak->id, 17, 8);
			break;
		case SET_WAR_VAL://读取设备的报警值界限
			ModbusTx::writeMem( pak->net, pak->id, 101, 9, pak->data);
            Message::_show(QObject::tr(""));
            //Message::_show(QObject::tr("数据修改成功!"));
			break;
		case QUE_WAR_VAL:
			ModbusTx::readMem( pak->net, pak->id, 101, 9);
			break;
//		case QUE_MOD_STA:
//			ModbusTx::readMem( pak->net, pak->id, 25, 1);
//			break;
		case SET_MOD_TRY:
			unsigned int data[1];
			data[0] = 1;
			ModbusTx::writeMem( pak->net, pak->id, 402, 1, data);
			break;
	}
}
void Signals::toDo()
{
	switch( Pake::readBuf.cmd )
	{
		case QUE_DEV_WAR://报警信息
			((Main*)p_main)->slot_warn();
			break ;
		case QUE_CUR_VAL://当前信息
			((Main*)p_main)->slot_cur_val();
		    break ;
		case QUE_WAR_VAL://节点设置的数据
			((Mset*)p_Mset)->nodeGetParm();
			break ;
		case QUE_MOD_VAL://型号
			((Main*)p_main)->slot_mod(); 
			break ;
		case ASN_SET_WAR://系统参数读取成功
			Message::_show(QObject::tr("参数修改成功!"));
			break;
		case ASN_RES_MOD://复位
			((Main*)p_main)->slot_ans_reset();
			break;
		case QUE_MOD_STA://节点状态
            //Signals::errorFlag = Pake::readBuf.data[1];
            for (int i = 0; i < 8; i++) {                
                if (Module::getSubWarn(Pake::readBuf.net, Pake::readBuf.id , i) == false
                    && (Pake::readBuf.data[0] >> i & 0x01)) {
                    //Message::_show("warn!!!");
                    //Message::_show(QString::number(i));
                    printf("Pake::readBuf.data[0] = %x   ",Pake::readBuf.data[0]);
                    printf("warn!!!i==%d\n",i);
                    Pake::send(Pake::readBuf.net,Pake::readBuf.id, QUE_DEV_WAR, NULL, 0);
                    break;
                }else if(Module::getSubWarnRecovery(Pake::readBuf.net, Pake::readBuf.id , i) == true
                    && ((Pake::readBuf.data[0] >> i) == 0)){
                    if(Main::resetwarn == 1){
                        Pake::send(Pake::readBuf.net,Pake::readBuf.id, QUE_DEV_WAR, NULL, 0);
                        Main::resetwarn = 0;printf("resetwarn!!!!!!!!!");
                    }
                    printf("getSubWarnRecovery\n");
                    break;
                } else if (Module::getSubError(Pake::readBuf.net, Pake::readBuf.id , i) == false
                    && (Signals::Flagerror[Pake::readBuf.net] >> i & 0x01)) {
                    //Message::_show("故障！4444");                    
					//((Main*)p_main)->slot_warn_error();                    
                    printf("Signals::Flagerror[%d]= %x   ",Pake::readBuf.net,Signals::Flagerror[Pake::readBuf.net]);
                    printf("errorFlag Pake::readBuf.net==%d Pake::readBuf.id==%d i===%d \n",Pake::readBuf.net,Pake::readBuf.id,i);
                    if (Module::getSubWarn(Pake::readBuf.net, Pake::readBuf.id , i) == true
                        && (Pake::readBuf.data[0] >> i & 0x01)) {
                        printf("warn++++++++++++++++++++++++=\n");
                    }
                    else{
                        Pake::send(Pake::readBuf.net,Pake::readBuf.id, QUE_DEV_WAR, NULL, 0);
                    }
					break;
                }else if(Module::getSubErrorRecovery(Pake::readBuf.net, Pake::readBuf.id , i) == true
                    &&((Signals::Flagerror[Pake::readBuf.net] >> i) == 0)&& ((Pake::readBuf.data[0] >> i) == 0)){
                    //Message::_show("故障恢复！");                    
                    Pake::send(Pake::readBuf.net,Pake::readBuf.id, QUE_DEV_WAR, NULL, 0);
                    break;
                 }/*else if(Module::getSubErrorRecovery(Pake::readBuf.net, Pake::readBuf.id , i) == true){
                          if((Signals::Flagerror[Pake::readBuf.net] >> i & 0x01) == 0 && ((Pake::readBuf.data[0] >> i) == 0))
                          {
                              printf("111111111111111111111111i=====%d\n",i);
                              Pake::send(Pake::readBuf.net,Pake::readBuf.id, QUE_DEV_WAR, NULL, 0);
                              break;
                          }else{
                              printf("2222222222222222222 i===%d   %x\n",i,(Signals::Flagerror[Pake::readBuf.net] >> i));
                          }

                }*/

            }
		   	if (Pake::readBuf.data[0] >> 8 & 0x01) {
				((Main*)p_main)->slot_ans_try();
			}
			break;
		case ASN_MOD_TRY://试验回复
			((Main*)p_main)->slot_ans_try();
			break;
	}
}
