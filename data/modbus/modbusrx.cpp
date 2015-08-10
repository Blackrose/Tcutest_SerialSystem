#include "modbusrx.h"
#include "modbustx.h"
#include "crc.h"
#include "rxdata.h"
#include "pake.h"
#include "signals.h"

int ModbusRx::dataStatus = 0;

bool ModbusRx::sendDataToPake(int net,int id)
{
	unsigned int crc;
	bool ret = false; 
	ModbusRx::dataStatus = 0;
	if( RxThread::netData[net].len > 1)
	{
		crc = RxThread::netData[net].data[RxThread::netData[net].len-1]*256 
			+ RxThread::netData[net].data[RxThread::netData[net].len-2] ;
 		ModbusRx::dataStatus = 1;//crc error
		if( crc == Crc::CRC16(RxThread::netData[net].data, RxThread::netData[net].len-2) )
		{
 			ModbusRx::dataStatus = 2;//id error
			if(id == RxThread::netData[net].data[0] )
			{
				Pake::readBuf.net = net;
				Pake::readBuf.id = RxThread::netData[net].data[0];
				Pake::readBuf.cmd = 0;
				if(RxThread::netData[net].data[1] == 0x03 && ModbusTx::startSize[net]*2 == RxThread::netData[net].data[2] )
				{
 					ModbusRx::dataStatus = 4;//right
                    //printf("ModbusRx::dataStatus = 4\n");
					if( ModbusTx::startAddr[net] == 25)
					{//读取节点状态
						Pake::readBuf.cmd = QUE_MOD_STA;
						Pake::readBuf.data[0] = RxThread::netData[net].data[3]*256 + RxThread::netData[net].data[4];
						Pake::readBuf.data[1] = RxThread::netData[net].data[5]*256 + RxThread::netData[net].data[6];
                        //printf("testdata= %x ",Pake::readBuf.data[1]);
                        //Signals::errorFlag = Pake::readBuf.data[1];
                        //printf("\n");
                        //printf("net ==%d\n",net);
                        if(net == 0){
                            Signals::Flagerror[0] = Pake::readBuf.data[1];
                        }else{
                            Signals::Flagerror[1] = Pake::readBuf.data[1];
                        }

					}
					else if(ModbusTx::startAddr[net] == 1)
					{//读取报警信息
						Pake::readBuf.cmd = QUE_DEV_WAR;
						Pake::readBuf.data[0] = RxThread::netData[net].data[3]*256 +  RxThread::netData[net].data[4];
						Pake::readBuf.data[1] = RxThread::netData[net].data[5]*256 +  RxThread::netData[net].data[6];
						Pake::readBuf.data[2] = RxThread::netData[net].data[7]*256 +  RxThread::netData[net].data[8];
						Pake::readBuf.data[3] = RxThread::netData[net].data[9]*256 +  RxThread::netData[net].data[10];
						Pake::readBuf.data[4] = RxThread::netData[net].data[11]*256 +  RxThread::netData[net].data[12];
						Pake::readBuf.data[5] = RxThread::netData[net].data[13]*256 +  RxThread::netData[net].data[14];
						Pake::readBuf.data[6] = RxThread::netData[net].data[15]*256 +  RxThread::netData[net].data[16];
						Pake::readBuf.data[7] = RxThread::netData[net].data[17]*256 +  RxThread::netData[net].data[18];
						Pake::readBuf.data[8] = RxThread::netData[net].data[19]*256 +  RxThread::netData[net].data[20];
					}
					else if(ModbusTx::startAddr[net] == 201)
					{//读取SN
						Pake::readBuf.cmd = QUE_MOD_VAL;
						Pake::readBuf.data[0] = RxThread::netData[net].data[3]*256 +  RxThread::netData[net].data[4];
					}
					else if(ModbusTx::startAddr[net] == 17)
					{//读取当前数值
						Pake::readBuf.cmd = QUE_CUR_VAL;
						Pake::readBuf.data[0] = RxThread::netData[net].data[3]*256 +  RxThread::netData[net].data[4];
						Pake::readBuf.data[1] = RxThread::netData[net].data[5]*256 +  RxThread::netData[net].data[6];
						Pake::readBuf.data[2] = RxThread::netData[net].data[7]*256 +  RxThread::netData[net].data[8];
						Pake::readBuf.data[3] = RxThread::netData[net].data[9]*256 +  RxThread::netData[net].data[10];
						Pake::readBuf.data[4] = RxThread::netData[net].data[11]*256 +  RxThread::netData[net].data[12];
						Pake::readBuf.data[5] = RxThread::netData[net].data[13]*256 +  RxThread::netData[net].data[14];
						Pake::readBuf.data[6] = RxThread::netData[net].data[15]*256 +  RxThread::netData[net].data[16];
						Pake::readBuf.data[7] = RxThread::netData[net].data[17]*256 +  RxThread::netData[net].data[18];
					}
					else if(ModbusTx::startAddr[net] == 101 )
					{//读取设置的报警数值
						Pake::readBuf.cmd = QUE_WAR_VAL;
						Pake::readBuf.data[0] = RxThread::netData[net].data[3]*256 +  RxThread::netData[net].data[4];
                        Pake::readBuf.data[1] = RxThread::netData[net].data[5]*256 +  RxThread::netData[net].data[6];
						Pake::readBuf.data[2] = RxThread::netData[net].data[7]*256 +  RxThread::netData[net].data[8];
						Pake::readBuf.data[3] = RxThread::netData[net].data[9]*256 +  RxThread::netData[net].data[10];
						Pake::readBuf.data[4] = RxThread::netData[net].data[11]*256 +  RxThread::netData[net].data[12];
						Pake::readBuf.data[5] = RxThread::netData[net].data[13]*256 +  RxThread::netData[net].data[14];
						Pake::readBuf.data[6] = RxThread::netData[net].data[15]*256 +  RxThread::netData[net].data[16];
						Pake::readBuf.data[7] = RxThread::netData[net].data[17]*256 +  RxThread::netData[net].data[18];
						Pake::readBuf.data[8] = RxThread::netData[net].data[19]*256 +  RxThread::netData[net].data[20];
					}
					ret = true;
				}
				else if(RxThread::netData[net].data[1] == 0x10 
					&& ModbusTx::startSize[net] == (RxThread::netData[net].data[4]*256 +  RxThread::netData[net].data[5])
					&& ModbusTx::startAddr[net] - 1 ==  (RxThread::netData[net].data[2]*256 +  RxThread::netData[net].data[3]))
				{
					if( ModbusTx::startAddr[net] == 401)
					{//复位成功
						Pake::readBuf.cmd = ASN_RES_MOD;
					}
					else if( ModbusTx::startAddr[net] == 101)
					{//设置报警值成功
						Pake::readBuf.cmd = ASN_SET_WAR;
					}
					else if(ModbusTx::startAddr[net] == 402)
					{
						Pake::readBuf.cmd = ASN_MOD_TRY;
					}
                    ret = true;//printf("0x10 ModbusRx::dataStatus = 4\n");
 					ModbusRx::dataStatus = 4;//right
				}
				else
				{
 					ModbusRx::dataStatus = 3;//
				}
			}
		}
	}
	return ret;
}

