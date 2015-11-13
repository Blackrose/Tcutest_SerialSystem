/*=============================
	      主界面
=============================*/
#include "main.h"
#include "startUpFrm.h"
#include "modbustx.h"
#include "modbusrx.h"
#include "Mset.h"
#include "can.h"
#include "pic/pic_communication.h"

int Main::screenWaitTime = 600; //屏幕保护时间s
int Main::whoChePwd = NONE;
int Main::com_led = 1;
int Main::flagnosound = 0;
int Main::flagreset = 0;
int Main::mainpower = 0;
int Main::prepower = 0;
int Main::onStat = 0;
int Main::offStat = 0;
int Main::WarnSumOne = 0;

Main::Main(QProgressBar *proBar,QWidget *parent): QWidget(parent),Ui_MainForm()
{
	setupUi(this);
        setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
	setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存        
    p_imf = new IMFrame();	//键盘
	proBar->setValue(8);
	Message::static_msg = new Message();

	Print::init();

	Db::init();		//加载数据库
	p_mod = new Module();	//初始化模块:
	proBar->setValue(16);
    QWSServer::setCurrentInputMethod(p_imf);
//	Watchdog::init();//初始化看门狗

	Can::init();		//初始化can设备
	Bell::init();		//初始化蜂鸣器设备
	Led::init();		//初始化指示灯设备
    Led::relayinit();   //初始化relay
	Power::init();		//初始化电源设备
	Watchdog::kellLive();	//喂狗
	PicProtocol::pic_port_init(&PicProtocol::pic_port, Can::fd[2]);

	Bell::on();
	Bell::off();
	Led::mainLightOff();
	Led::preMainLightOff();
	Led::commLightOff();
	Led::modErrorLightOff(); 
	Led::warnLightOff();
    Led::CtlOff();

	proBar->setValue(24);
	p_timer	= new QTimer(this);	//初始化定时器
    //led_timer = new QTimer(this);
    //pic_rebuild_timer = new QTimer(this);
	pic_timer = new QTimer(this); 
    s_timer = new QTimer(this);
	proBar->setValue(32);
	Watchdog::kellLive();//喂狗
	p_sys 	= new Sys(p_imf);//系统管理sig
	proBar->setValue(40);
	p_chePwd = new CheckPwd(p_imf, this);	//密码检测
	proBar->setValue(48);
	Watchdog::kellLive();//喂狗
	p_putOff= new PutOff( &sig, this); //脱扣
	proBar->setValue(56);
	p_relog	= new Relogin( p_imf, this, this); //重新登录
	proBar->setValue(64);
	Watchdog::kellLive();//喂狗
	p_check	= new Check(this); //自检
	proBar->setValue(72);
	p_printer = new Printer();
    proBar->setValue(80);
	p_help = new Help();
	p_query = new Query();//报警、操作记录查询
    proBar->setValue(88);
	Watchdog::kellLive();//喂狗
    p_nodeStatus = new NodeStatus(p_imf,this);//详细记录的状态
    //QWSServer::setCurrentInputMethod(p_imf);
	proBar->setValue(96);


	sig.p_main = this;
	sig.p_putOff = p_putOff;
	sig.p_nodeStatus = p_nodeStatus;

    curNet = 0;		//当前显示的网络 默认0
	curNode = -1;		//当前选择的节点 默认0
	whoReset = 0;		//谁复位 :0 启动复位 1 按钮复位
    //mainpower = 0;		//主电源
	errorLed = 0;		//节点故障灯
	warnLed = 0;		//led报警灯
    warnRelay = 0;
	error = 0;		//故障
	warn = 0;		//报警
	screenCount = 0;	//计算器
	whoChePwd = NONE;	//检测密码
	time_min = -1;		//分
    //offStat = 0;
    //onStat = 0;
    preStat = 0;
    mainStat = 0;
	off = 0;		//短路断路
	on = 0;
	preJ4 = 0;		//j4电平
	relayStats = 0;		//继电器状态
    //prepower = 0;		//备电源
	timer_count = 0 ;
	timer_countPower = 3000;
    colorcount = 0;//add by 7.16
    flagcolor = 0;   

	Message::static_msg = new Message();
	for(int i = 0 ; i < DATCOU ; i++)
		dataA[i] = -1;	//当前电流值
	showCrurrent = 0;	//当前显示的页
	AruCount = 0;		//延时计数器
	screenWaitTime = Mater::read() * 60 * 1000;//屏幕保护时间s
    lblWarnSum->setVisible(false);
	initBtnNode();		//初始化节点按钮
	initSubNode();		//初始化子节点
	initConnect();		//连接信号于槽

	//p_rx->start();	//现在
	if(NET == 1)
		showHowNet();
	proBar->setValue(100);
	Watchdog::kellLive();//喂狗

	show();
    deleteall();
	setLblNodSum();
	for(int i = 0; i < p_mod->net0All; i++)
	{
		btn_node[i].btn.setVisible(true);
	}

    Signals::netCount[0] =  p_mod->net0All;
	Signals::netCount[1] = p_mod->net1All;
	Signals::timer = Mater::readSendTimer();
	Db::newTimeNoSec(lblLocalTime,&time_min);//界面时钟
	p_timer->start(3000);//启动定时器
	pic_timer->start(50);
    //pic_rebuild_timer->start(1000);
    //led_timer->start(500);//0.5s
	newErrorTest();
	printf("init Main ok\n");

}
/*void Main::set_pwd(int a)
{
	whoChePwd=a;
}*/
//================ 注册信息 =================
void Main::slot_reg(int net,int id)
{
	struct  mod* mo = p_mod -> getNode( net, id);
    QString time_str = Db::newTime();
    //printf("注册信息 \n");
//    if(mo->sn == 0)
//    {//读取SN
//        //printf("注册信息 mo->sn==%d\n",mo->sn);
//        ModbusTx::readMem( net, id, 201, 1);
//    }//add by zhq
    //Main::slot_mod();//型号    
    if(mo->flag == UNABLE)//ERROR
    {
        mo->flag = NORMAL;
		if(curNet != net)
		{
			showCurrentNet(net);//显示当前网络
		}
		else
		{
            setBtnFalg( id, NORMAL);
		}
		checkError();
		checkWarn();
        checkRelayWarn();
		setBellAndLedStatus();
		Led::LCDLightOn();
		if(p_nodeStatus -> curNet == net && p_nodeStatus-> curId == id )
		{
			p_nodeStatus->_show( net, id, mo->sn, NORMAL);
		}
        PicProtocol::pic_channel_restore(net, id, 99, time_str);//通道故障恢复
        WarnMsg::insertNowNodeDorestore(net, id, E_ALARM );
	}
}
//===== 故障  ==================
void Main::slot_error(int net,int id)
{
	struct  mod* mo = p_mod -> getNode( net, id);

    if (mo->flag != UNABLE)//ERROR
	{
        mo->flag = UNABLE;//ERROR
		p_mod -> cleSubWarn( net , id);
		if(curNet != net)
		{
			showCurrentNet(net);//显示当前网络
		}
		else
		{
            //setBtnFalg( id, ERROR);
            setBtnFalg( id, UNABLE);//掉线
		}
		WarnMsg::insertEAlarm( net, id);
		setLblWarnSum();
		error = 1;
		errorLed = 1;
		warn = 0;//20121203-16:33--modified
		warnLed = 0;//20121203-16:33--modified
		setBellAndLedStatus();
		lblNode->setText("");//20121203-16:29--modified
		lblXing->setText("");//20121203-16:30--modified
		clearSubNodeDat();//20121130-16:55--modified
		if(p_nodeStatus -> curNet == net && p_nodeStatus-> curId == id )
		{
            p_nodeStatus->_show( net, id, mo->sn, UNABLE);
		}
        mo->sn = NO_SN;//掉线
	}
}
//================ 报警 ==================
void Main::slot_warn()
{
	struct pake* dat = &Pake::readBuf;
	int is, net, id, sudId;
	//QString str;
	struct mod* mo;
	net = dat->net;
	id = dat->id;
	mo = p_mod -> getNode( net, id);
	for( sudId = 0 ; sudId < 8 ; sudId++)
	{
        if(p_mod -> getSubWarn( net, id, sudId) == false && dat->data[sudId] > 0)
        {
            //printf("getSubWarn net==%d id==%d sudId==%d\n",net,id,sudId);
            mo->flag = WARN;
            if(curNet !=  net)
            {
                showCurrentNet(net);//显示当前网络
            }
            else
            {
                setBtnFalg(id, WARN);
            }
            is = p_mod->getWhatWarn( net, id, sudId);
            if( is == 2)
            {//漏电
                WarnMsg::insertMAlarm( net, id, sudId, dat->data[sudId]);
            }
            else if( is == 0)
            {//温度
                WarnMsg::insertTAlarm( net, id, sudId, ((float)dat->data[sudId])/10);
            }
            //显示模块节点号
            curNode = id;
            clearSubNodeDat();
            if(is == 2)
            {
                p_mod->setSubWarn( net, id, sudId, WARN, dat->data[sudId]);//写下子节点报警
            }
            if(is == 0)
            {

                p_mod->setSubWarn( net, id, sudId, WARN, ((float)dat->data[sudId])/10);//写下子节点报警
            }

            warn = 1;
            warnLed = 1;
            warnRelay = 1;
            setBellAndLedStatus();
            Led::LCDLightOn();
            if(p_nodeStatus->curNet == net && p_nodeStatus->curId == id )
            {
                p_nodeStatus->_show(curNet,curNode,mo->sn,WARN);
            }
            setLblWarnSum();
            //显示模块型号
            lblXing->setText(tr(Module::moTyp[mo->sn].name));
            //显示模块节点号
            curNode = id;
            lblNode->setText(QString::number(id));
        }else if(p_mod->getSubWarnRecovery(net, id, sudId) == true &&(dat->data[sudId] == 0)){
            //printf("getSubWarnRecovery1111111111111111111\n");
            //if(dat->data[sudId] == 0){
                 //printf("getSubWarnRecovery222222222222222222222222\n");
                 is = p_mod->getWhatWarn( net, id, sudId);
                 if( is == 2)
                 {//漏电
                     WarnMsg::insertTorCrestore(net, id, sudId);
                 }
                 else if( is == 0)
                 {//温度
                     WarnMsg::insertTorCrestore(net, id, sudId);
                 }
            //}
             p_mod->setSubWarn(net, id, sudId, NORMAL,0);//
        }
        else if (p_mod->getSubError(net, id, sudId) == false && (Signals::Flagerror[net] >> sudId & 0x01)) {

            mo->flag = ERROR;
//            printf("11111Signals::Flagerror[%d]= %x ",net,Signals::Flagerror[net]);
//            printf("\n");
//            printf("getSubError net ==%d id ===%d sudId===%d\n",net,id,sudId);

            if (curNet !=  net) {
                showCurrentNet(net);//显示当前网络
            } else {
                setBtnFalg(id, ERROR);//err  ???不起作用
            }
            //=============================================================
            is = p_mod->getWhatErr( net, id, sudId);
            if( is == 2)
            {//漏电故障
                WarnMsg::insertCError( net, id, sudId);
                WarnMsg::insertNowTorCError( net, id, sudId);                
            }
            else if( is == 0)
            {//温度故障
                WarnMsg::insertTError( net, id, sudId);
                WarnMsg::insertNowTorCError( net, id, sudId);                
            }
            //==============================================================
            //WarnMsg::insertSubError(net, id, sudId);
            //显示模块节点号
            curNode = id;
            clearSubNodeDat();
            p_mod->setSubError(net, id, sudId, ERROR);//写下子节点故障
            error = 1;
            errorLed = 1;
            setBellAndLedStatus();
            if (p_nodeStatus->curNet == net && p_nodeStatus->curId == id)
            {
                p_nodeStatus->_show(curNet, curNode, mo->sn, ERROR);
            }
            setLblWarnSum();
            //显示模块型号
            lblXing->setText(tr(Module::moTyp[mo->sn].name));
            //显示模块节点号
            curNode = id;
            lblNode->setText(QString::number(id));
        }
        else if(p_mod->getSubErrorRecovery(net, id, sudId) == true && ((Signals::Flagerror[net] >> sudId) == 0)){//没有故障
                //Message::_show(tr("没有故障！"));
            mo->flag = NORMAL;
            printf("enter getSubErrorRecovery id ===%d\n",id);
            if (curNet !=  net) {
                showCurrentNet(net);//显示当前网络
            } else {
                setBtnFalg(id, NORMAL);//
            }
            //=============================================================
            is = p_mod->getWhatErr( net, id, sudId);
            if( is == 2)
            {//漏电故障
                WarnMsg::insertCrestore(net, id, sudId);
            }
            else if( is == 0)
            {//温度故障
                WarnMsg::insertTrestore(net, id, sudId);
            }
            //==============================================================
            //WarnMsg::insertCrestore(net, id, sudId);
            //显示模块节点号
            curNode = id;
            clearSubNodeDat();
            p_mod->setSubError(net, id, sudId, NORMAL);//
            error = 0;
            errorLed = 0;
            setBellAndLedStatus();
            if (p_nodeStatus->curNet == net && p_nodeStatus->curId == id)
            {
                p_nodeStatus->_show(curNet, curNode, mo->sn, NORMAL);
            }
            setLblWarnSum();
            //显示模块型号
            lblXing->setText(tr(Module::moTyp[mo->sn].name));
            //显示模块节点号
            curNode = id;
            lblNode->setText(QString::number(id));
        }
    }
    for( sudId = 0 ; sudId < 8 ; sudId++)
    {
//        if(p_mod -> getSubError( net, id, sudId) == true)
//        {
//            mo->flag = ERROR;
//            if (curNet !=  net) {
//                showCurrentNet(net);//显示当前网络
//            } else {
//                setBtnFalg(id, ERROR);//
//            }
//        }

        if(p_mod -> getSubWarn( net, id, sudId) == true)
        {
            mo->flag = WARN;
            if (curNet !=  net) {
                showCurrentNet(net);//显示当前网络
            } else {
                setBtnFalg(id, WARN);//
            }
        }
    }
}
//========== 模块当前数据 (电流漏电 温度) ================
void Main::slot_cur_val()
{
	struct pake* dat = &Pake::readBuf;
	struct  mod* mo = NULL;
	int net, id;
	net = dat->net;
	id = dat->id;
	mo  = p_mod -> getNode( net, id);
	if(mo == NULL) return ;
	if( mo->sn != NO_SN && id == curNode)
	{
		for(int i=0;i<DATCOU;i++)
		{
			if((mo->sn==MC)||(mo->sn==ML8))
			{
				dataA[i]=dat->data[i];
			}
			if ((mo->sn==ML4T4) || (mo->sn==ML1T1) || (mo->sn==DL1T1))
			{
				if(i>3)
				{
                    dataA[i]=((float)dat->data[i])/10;
				}
				else
				{
					dataA[i]=dat->data[i];
				}
			}
		}
		if( p_nodeStatus->isHidden() )
		{
			lblNode->setText(QString::number(id));
			//显示数据
			showNOPagSubNode(mo);
		}
		else
		{
			p_nodeStatus->setCurVal(dataA, 8);
		}
	}
}
//========== 显示第一页子点号 ===========
void Main::showNOPagSubNode(struct mod *mo)
{
	switch( mo->sn)
	{
		case ML1T1:
			lblXing->setText(tr(Module::moTyp[ML1T1].name));
			for(int i=0;i<8;i++)
			{
				if(i<4)
				{
					setSubNodeStat(dataA[i],&lbl_subNode[i],1);
				}
				else
				{
					setSubNodeStat(dataA[i],&lbl_subNode[i],0);
				}
			}
			break;
        case DL1T1://只显示一路电流和温度
			lblXing->setText(tr(Module::moTyp[DL1T1].name));
            for(int i=0;i<8;i++)
            {
                if(i<4)
                {
                    setSubNodeStat(dataA[i],&lbl_subNode[i],1);
                }
                else
                {
                    setSubNodeStat(dataA[i],&lbl_subNode[i],0);
                }
            }
            //setSubNodeStat(dataA[0],&lbl_subNode[0],1);//ma
            //setSubNodeStat(dataA[4],&lbl_subNode[4],0);//C
			break;
		case ML4T4:
		//SL6044c
			lblXing->setText(tr(Module::moTyp[ML4T4].name));
			for(int i=0;i<8;i++)
			{
				if(i<4)
				{
					setSubNodeStat(dataA[i],&lbl_subNode[i],1);
				}
				else
				{
					setSubNodeStat(dataA[i],&lbl_subNode[i],0);
				}
			}
			break;
		case ML8:
        //SL6080c
			lblXing->setText(tr(Module::moTyp[ML8].name));//型号
			for(int i=0;i<8;i++)
			{
				setSubNodeStat(dataA[i],&lbl_subNode[i],1);
			}
			break;
	}
}
/*=============清空子节点数据===============*/
void Main::clearSubNodeDat()
{
	for(int i=0;i<8;i++)
	{
		lbl_subNode[i].lblValue.setText(tr(""));
	}
}
/*=================显示子节点的颜色 =================*/
void Main::setSubNodeStat(float value, struct LblSubNode *sudNode,int cora)
{
    if(sudNode->lbl.isHidden())
	{
		sudNode->lbl.show();
	}
	if(cora == 0)
	{//温度
        sudNode->lblValue.setText(QString::number(value)+tr("℃"));
	}
	else if( cora == 1)
	{//mA
		sudNode->lblValue.setText(QString::number(value)+tr("mA"));
	}
}
//写下蜂鸣器状态
void Main::setBellAndLedStatus()
{
	//报警 故障 蜂鸣器控制
	if(errorLed == 1)
	{
		Led::modErrorLightOn();
	}
	else
	{
		Led::modErrorLightOff();
	}
	if(warnLed == 1)
	{
		Led::warnLightOn();
        //Led::CtlOn();
	}
	else
	{ 	
		Led::warnLightOff();
        //Led::CtlOff();
	}
    if(warnRelay == 1)
    {
        Led::CtlOn();
    }
    else
    {
        Led::CtlOff();
    }
	if(warn == 1)
	{
	//	Bell::on();
		Bell::warn();
	}
	else if(error == 1)
	{
		Bell::error();
	}
	else
	{
		Bell::off();
		Bell::warn_flag = 0;
		Bell::error_flag = 0;
	}
    setLblWarnSum();
}
// ================ 定时器  ================== 
void Main::slot_timer()
{
	p_timer->stop();
	timer_count += ModbusTx::timer;
	timer_countPower += ModbusTx::timer;
	screenCount += ModbusTx::timer;

	Watchdog::kellLive();//喂狗
	//屏保
	if(Led::LCDStats())
	{
		if(screenCount  >= screenWaitTime)
		{
			screenCount = 0;		
			Led::LCDLightOff();
		}
	}
	else
	{
		screenCount = 0;
	}
    if( timer_countPower >= 3500)//3500//愿为3500
    {//printf("timer_countPower==%d\n",timer_countPower);
		timer_countPower = ModbusTx::timer;
		powerCheck();

//		Can::sent_test();
//		Can::rx_test();

		//显示当前节点的数值
		if( p_nodeStatus->isHidden() )
		{
			int count;
			if( curNet == 0 )
			{
				count = p_mod->net0All;
			}
			else
			{
				count = p_mod->net1All;
			}
			for(int i = 1; i <= count; i++)
			{
				curNode = ++curNode % count;
				if(curNode == 0)
				{
					curNode = count;
				}
				if ( p_mod->getNodeStats( curNet, curNode) != ERROR )
				{	 
					if ( p_mod->getSN(curNet, curNode) != 0)
					{
						Pake::send( curNet, curNode, QUE_CUR_VAL, NULL, 0);
						break;
					}
				}
			}
		}
		else
		{
			Pake::send( curNet, curNode, QUE_CUR_VAL, NULL, 0);
		}
		//printf("time_count\n");
        //printf("timer_countPower2222==%d\n",timer_countPower);
	}
 	sig.send();
	if(timer_count >= 5000)//WIAT_SEC )
	{
		::system("hwclock -s");
		timer_count = ModbusTx::timer;
		Watchdog::kellLive();//喂狗
        //printf("timer_time\n");
		Db::newTimeNoSec(lblLocalTime,&time_min);//界面时钟
        ::system("free");
        //printfCPU();
		p_timer->start(500);
		return ;
	}
    //printf("ModbusTx::timerModbusTx::timer===%d\n",ModbusTx::timer);
	p_timer->start(ModbusTx::timer);//启动定时器
}

void Main::pic_handle()
{
    static int inq_loop = 0,tmp_loop;
    tmp_loop++;
	inq_loop++;
    if (inq_loop == 60) {
		inq_loop = 0;
		PicProtocol::pic_heart_beat();
        //PicProtocol::pic_port_state_fsm(&PicProtocol::pic_port);
        //PicProtocol::pic_rebuild(&PicProtocol::pic_port);
	}
    if(tmp_loop == 20){
        tmp_loop = 0;
        PicProtocol::pic_port_state_fsm(&PicProtocol::pic_port);
        PicProtocol::pic_rebuild(&PicProtocol::pic_port);
    }
    //PicProtocol::pic_port_state_fsm(&PicProtocol::pic_port);
    //PicProtocol::pic_rebuild(&PicProtocol::pic_port);
}

void Main::pic_rebuild()
{
    PicProtocol::pic_rebuild(&PicProtocol::pic_port);
}

void Main::sound_timer()
{
     if(flagnosound == 0)
     {
         flagnosound = 1;
          printf("enter sound_timer stop sound\n");
     }
     else
     {
         flagnosound = 0;
         printf("enter sound_timer start sound\n");
     }

}

void Main::led_slot_timer()
{
    printf("now ModbusRx ====%d\n",ModbusRx::dataStatus);
    if (ModbusRx::dataStatus == 4)
    {
        printf("now ModbusRx led on or off\n");
        //si_i = ++ si_i % 10;//原来为60
//        if ( si_i == 1)
//            Led::commLightOn();
//        else  if(si_i == 6)//原来为20
//            Led::commLightOff();
         Led::commLightOn();
         usleep(500000);
         Led::commLightOff();
         //usleep(500000);
    }

}

void Main::clearScreenCount()
{
	screenCount = 0;
    //printf("clear screenCount!!!!!!!!\n");
}

//================ 电源检测 ================
void Main::powerCheck()
{
	//检测主电源
	if(Power::isMainPower())
	{
		if(mainpower == 1)
		{//主电源
			mainpower = 0;
			checkError();
			WarnMsg::insertMainOk();
			Message::_show(tr("主电正常了！"));
			setBellAndLedStatus();
		}
		Led::mainLightOn();//主电源灯
	}
	else
	{
		if(mainpower == 0)
        {
            mainStat = 1;
			mainpower = 1;
			error = 1;
			errorLed = 1;
			WarnMsg::insertMainNo();
			Message::_show(tr("主电欠压！"));
			setBellAndLedStatus();
		}        
        Power::offRelay();
        relayStats = 0;
		Led::mainLightOff();//主灯灭
	}
	
	//j4电平控制 判断是否短路断路
	if (relayStats == 0) {	
        if (Power::isPrePowerJ() == 0) {//断路
            //printf("off off off off off\n");
			off = 1;
			on = 0;
        } else if (Power::isPrePowerJ() == 1) {//短路
            //printf("on on on on on on \n");
			on = 1;
			off = 0;
        } else if (Power::isPrePowerJ() == 2) {//ok
            //printf("ok ok ok ok ok ok\n");
			on = 0;
			off = 0;
		}
    } else {//电池充电中
        /*if (Power::isPrePowerJ() == 0) {//断路
            //printf("off off off off off\n");
            off = 1;
            on = 0;
        }
        else*/
        if (Power::isPrePowerJ() == 1) {//短路
			on = 1;
			off = 0;
		}
	}

	//短路
	if( on == 1 )
	{
		if(onStat == 0)
		{
			onStat = 1;
			error = 1;
			errorLed = 1;
			WarnMsg::insertPreMainOn();	
			Message::_show(tr("备电短路！"));
			setBellAndLedStatus();
		}
		Led::preMainLightOff();
	}
	else
	{
		if(onStat == 1)
		{
			onStat = 0;
			checkError();
			setBellAndLedStatus();
			Message::_show(tr("备电短路恢复了！"));
			WarnMsg::insertPreMainOk();
		}
	}

	//断路
	if( off == 1 )
	{
		if(offStat == 0)
		{
			offStat = 1;
			error = 1;
			errorLed = 1;
			WarnMsg::insertPreMainOff();	
			Message::_show(tr("备电断路！"));
			setBellAndLedStatus();
		}
		Led::preMainLightOff();
	}
	else
	{
		if(offStat == 1)
		{
			offStat = 0;
			checkError();
			Message::_show(tr("备电断路恢复了！"));
			WarnMsg::insertPreMainOk();
			setBellAndLedStatus();
		}
	}

	//检测备电源欠压
	if ((on == 0) && (off == 0))
	{
		if(Power::isPrePower())
		{
			if(prepower == 1)
			{
				prepower = 0;
				checkError();
				Message::_show(tr("备电不欠压了！"));
				WarnMsg::insertPreMainOk();
				setBellAndLedStatus();
			}            
			Led::preMainLightOn();
		}
		else
		{
			if(prepower == 0)
			{
				prepower = 1;
				error = 1;
				errorLed = 1;
				WarnMsg::insertPreMainNo();
				Message::_show(tr("备电欠压！"));
				setBellAndLedStatus();
			}
			Led::preMainLightOff();
		}
	}
	// 继电器控制
	if ((Power::isChargeHigh() == false) && (on == 0) && (off == 0)) {
        if(Power::isMainPower())//主电源
        {
            Power::onRelay();
            relayStats = 1;
            if(preStat == 0){
                preStat = 1;
                Message::_show(tr("电池充电!"));
            }
            //printf("on relay\n");
        }else{
            if(mainStat == 1){
                mainStat = 0;
                Message::_show(tr("请连接主电源充电!"));
            }
        }

    } else if((Power::isChargeHigh() == true) && (on == 0) && (off == 0)){
        Power::offRelay();
        relayStats = 0;
        if(preStat == 1){
            preStat = 0;
            Message::_show(tr("电池电量充足!"));
        }
        //printf("off relay when full\n");
    }else {
		Power::offRelay();
		printf("off relay\n");
		relayStats = 0;
	}
}
//============== 复位回复 ===============
void Main::slot_ans_reset()
{
    QString time_str = Db::newTime();
	struct pake* dat = &Pake::readBuf;
	if(dat == NULL) return;
	int net = 0 , id = 0;
	struct mod *mo  = p_mod -> getNode( curNet, curNode);
	net = dat->net;
	id = dat->id;
	p_mod -> cleWarn( net, id);
	p_mod -> setIsReset(net, id, false);
    

	if(p_nodeStatus -> curNet == net && p_nodeStatus-> curId == id )
		p_nodeStatus->_show(curNet,curNode,mo->sn,NORMAL);
	if(curNet !=  net)
		showCurrentNet( net);//显示当前网络
	else
		setBtnFalg( id, NORMAL);
//	powerCheck();
//	checkError();
//	checkWarn();
//	setBellAndLedStatus();
	setLblWarnSum();
    PicProtocol::pic_reset(time_str);
	printf("reset\t%d,\t%d,\n",net,id);
}
//================== 注册SN =====================
void Main::slot_mod()
{
	struct pake* dat = &Pake::readBuf;
	printf("net = %d, id = %d ,d = %d \n",dat->net,dat->id,dat->data[0]);
	p_mod->regSN( dat->net, dat->id, dat->data[0]);
}
//=============== 选择网络 =============
void Main::slot_net()
{
	QPushButton* b = qobject_cast<QPushButton*>(sender());
	if(b == btnNet0 )
	{
		curNet = 0;
		lblNet -> setText(tr("0"));
		btnNet1->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/netBtn1_f.png);"));
                btnNet0->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/netBtn1.png);"));

	}
	else {
		curNet = 1;
		lblNet -> setText(tr("1"));
		btnNet1->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/netBtn1.png);"));
                btnNet0->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/netBtn1_f.png);"));
	}
	clearSubNodeDat();
	curNode = -1;
	lblNode->setText(tr(""));
	lblXing->setText(tr(""));
	initCurrentNode();
}
//========== 显示当前网络  ==========
void Main::showCurrentNet(int net)
{
	if(net  ==  0 ){
		curNet = 0;
		lblNet -> setText(tr("0"));
		btnNet1->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/netBtn1_f.png);"));
		btnNet0->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/netBtn1.png);"));
	}
	else{
		curNet = 1;
		lblNet -> setText(tr("1"));
		btnNet1->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/netBtn1.png);"));
                btnNet0->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/netBtn1_f.png);"));
	}
	initCurrentNode();
}
//=========== 加载当前网络节点 ===============
void  Main::initCurrentNode()
{
	struct mod *mo;
    for(int id = 1 ; id <= BtnNodeNUm ; id++)
	{
		mo = p_mod -> getNode( curNet, id);
		if(mo == NULL) continue;
		if( mo->isHave == true)
        {//printf("enter 917 mo->flag==%d\n",mo->flag);
			setBtnFalg( id, mo->flag);
            if(btn_node[id - 1].btn.isVisible() == false)
                btn_node[id -1].btn.setVisible(true);
		}
		else
		{
            if(btn_node[id - 1].btn.isVisible() == true)
                btn_node[id -1].btn.setVisible(false);
		}
	}
}
//===============节点按钮=================
void Main::slot_btn_node()
{
	int btn_id;
	btn_id = qobject_cast<QPushButton*>(sender())->text().toInt();
	struct mod *mo  = p_mod -> getNode( curNet, btn_id);
	if( p_mod->getSN(curNet, btn_id) != 0)
    {   //QWSServer::setCurrentInputMethod(NodeStatus::imf_my);
        //delete  p_imf;
		curNode = btn_id;
		//显示模块型号
		lblXing->setText(tr(Module::moTyp[mo->sn].name));
		//显示模块网络号
		lblNet->setText(QString::number(curNet));
		//显示模块节点号
		lblNode->setText(QString::number(curNode));
		clearSubNodeDat();
		p_nodeStatus->_show( curNet, curNode, mo->sn,p_mod->getNodeStats(curNet,curNode));
        //NodeStatus::imf_my = new SyszuxIM();
        QTextCodec::setCodecForCStrings(0);
        QWSServer::setCurrentInputMethod(NodeStatus::imf_my);
        NodeStatus::imf_my->updateHandler(QWSInputMethod::FocusOut);
	}
	else
	{
		Message::_show(tr("节点没有注册!"));
	}
}
//========= 静音 ==========
void Main::slot_no_sound()
{
	error = 0;
	warn = 0;
	Bell::error_flag = 0;
	Bell::warn_flag = 0;
	Bell::off();
}

void Main::slot_start_sound()
{
    s_timer->start(5000);//5s
}

void Main::slot_stop_sound()
{
    s_timer->stop();
    if(flagnosound == 1)//time ok
    {
        printf("stop sound\n");
        //add user operation
        //flagnosound = 0;
    }
    else
    {
        printf("start sound\n");
    }
}
//======== 试验 =========
void Main::slot_btn_try()
{
    whoChePwd = TRY;
    p_chePwd->_show();
//    if(curNet >= 0 && curNode > 0 && curNet < 2 && curNode <= BtnNodeNUm)
//	{
//		Pake::send( curNet, curNode, SET_MOD_TRY, NULL, 0);
//	}
//	else
//	{
//		Message::_show(tr("没有选择节点!"));
//	}
}
//======== 按键试验回复 ========
void Main::slot_ans_try()
{
	struct pake* dat = &Pake::readBuf;
	Message::_show(tr("网络")+QString::number(dat->net)+tr("节点")+QString::number(dat->id)+tr("试验成功!"));
}
//=============== 初始化 预警 报警 故障  按钮 ===============
void Main::initBtnNode()
{
	int i ;
//	int x = 30, y = 15, w = 40, h = 31;
    int x = 25, y = 15, w = 44, h = 38;//52
//	int xw = 41, xh = 33;
    int xw = 44, xh = 46;//52
    btn_node = new BtnNode[BtnNodeNUm];
    for( i = 0; i < BtnNodeNUm ; i++)
        {//初始化报警
		btn_node[i].btn.setParent(nodePerent);
		btn_node[i].btn.setFocusPolicy(Qt::NoFocus);
		btn_node[i].btn.setFlat(true);
		btn_node[i].btn.setText(QString::number(i+1));
        if(i%13 == 0 && i != 0)
		{
			x = 25;
			y += xh;
		}
		btn_node[i].btn.setGeometry(x,y,w,h);

		normalColor(btn_node[i].btn);
		btn_node[i].flag = NORMAL;
		btn_node[i].btn.setVisible(false);
		x += xw;
	}
}
/*===========================================================
	功能:改变按钮节点状态 (正常 报警 预警 故障 取消节点)
	id: 节点 号 ;
        falg: NORMAL 正常, PREWARN 预警, WARN 报警 , ERROR 故障 ;
============================================================*/
void Main::setBtnFalg(int id,int flag)
{
    //printf("flag ==%d btn_node[%d].flag==%d\n",flag,id-1,btn_node[id-1].flag);
	if(btn_node[id-1].flag == flag) return;
	if(flag == NORMAL)
	{//正常
		normalColor(btn_node[id-1].btn);
	}	
	else if(flag == WARN)
	{//报警
		warnColor(btn_node[id-1].btn);
	}
	else if(flag == ERROR)
	{//故障
		errorColor(btn_node[id-1].btn);
	}
    else if(flag == UNABLE)
    {//掉线
        unableColor(btn_node[id-1].btn);
    }
	btn_node[id-1].flag = flag;
}
void Main::slot_WarnSumOne()
{
    WarnSumOne = 1;
    p_query->_show();
}
void Main::slot_WarnSumTwo()
{
    WarnSumOne = 2;
    p_query->_show();
}
void Main::slot_query()
{//信息查询
    WarnSumOne = 0;
	p_query->_show();
}
void Main::slot_relogin()
{//重新登录
	p_relog->_show();
}
void Main::slot_btn_reset()
{//复位按键 
	whoChePwd = RESET;
	p_chePwd->_show();
}
void Main::slot_check_main()
{//自检
	whoChePwd = CHECK;
	p_chePwd->_show();
}
void Main::slot_logout()
{// 模块注销
	whoChePwd = LOGOUT;
	p_chePwd->_show();
}
void Main::slot_sys()
{//系统管理
	whoChePwd = SYS;
	p_chePwd->_show(); 
}
void Main::slot_reboot()
{//重新启动	
	whoChePwd = REBOOT;
	p_chePwd->_show(); 
}
void Main::slot_put_off()
{//C型脱扣    
    //frmInput::Instance()->show();
    whoChePwd = TUO;
    p_chePwd->_show();
}

void Main::slot_printer()
{
    //frmInput::Instance()->hide();
    whoChePwd = PRINTER;
    p_chePwd->_show();
}

void Main::slot_help()
{
    //QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(),0,0,800,600);
    //pixmap.save("1.png","png");
    p_help->_show();
}

void Main::check_pwd()
{
	struct mod *mo;
	switch(whoChePwd)
	{
		case SYS:
			printf("sys 1\n");
			p_sys->_show();
			printf("sys 2\n");
			break;
        case TUO:
            //p_putOff->_show();
            mainpower=0;//
            prepower=0;//
            errorLed=0;//
            warnLed=0;//
            error=0;//
            warn=0;//
            offStat=0;//
            onStat=0;//
            preStat=0;//
            mainStat=0;
            off=0;//
            on=0;//
            preJ4=0;//
            relayStats=0;//
            warnRelay = 0;
            //Led::CtlOff();//
            setBellAndLedStatus();
            Led::commLightOff();
            Led::mainLightOff();//主电源灯
            Led::preMainLightOff();

            lblNode->setText("");
            lblXing->setText("");
            Signals::netCount[0] =  Mater::readNet0Count();
            Signals::netCount[1] = Mater::readNet1Count();
            Signals::timer = Mater::readSendTimer();
            sig.netCurId[0] = 1;
            sig.netCurId[1] = 1;
            //p_mod = new Module();	//初始化模块:

            if(curNet >= 0 && curNode >= 0 && curNet < 2 && curNode < BtnNodeNUm)
            {
                //p_mod->unreg( curNet, curNode);
                p_mod->reset( curNet, curNode);
                //setBtnFalg(curNode, ERROR);
                setBtnFalg(curNode, UNABLE);
                //lblNode0 -> setText("0");//网络0节点数
                //lblNode1 -> setText("0");//网络1节点数
                lblWarnSumOne->setText("0");//网络报警数
                lblWarnSumTwo->setText("0");//网络故障数

            }
            else
            {
                Message::_show(tr("节点不存在!"));
            }
            deleteall();

            //usleep(2000000);
//            checkError();
//            checkWarn();
//            powerCheck();
//            checkRelayWarn();

//            for(int id=1;id<=BtnNodeNUm;id++)
//            {
//                mo=p_mod->getNode(0,id);p_mod -> cleSubWarn( 0 , id);
//                if(mo==NULL) continue;
//                if(mo->isHave==true && mo->flag==UNABLE)
//                {
//                    printf("0000now enter mo->flag==UNABLE\n");
//                    WarnMsg::insertEAlarm(0,id);
//                    Bell::error();
//                    Led::modErrorLightOn();
//                }
//            }

//            for(int id=1;id<=BtnNodeNUm;id++)
//            {
//                mo=p_mod->getNode(1,id);p_mod -> cleSubWarn( 1 , id);
//                if(mo==NULL) continue;
//                if(mo->isHave==true && mo->flag==UNABLE)
//                {
//                    printf("1111now enter mo->flag==UNABLE\n");
//                    WarnMsg::insertEAlarm(1,id);
//                    Bell::error();
//                    Led::modErrorLightOn();
//                }
//            }

//            Signals::netCount[0] =  Mater::readNet0Count();
//            Signals::netCount[1] = Mater::readNet1Count();
//            Signals::timer = Mater::readSendTimer();

            //p_mod = new Module();	//初始化模块:

            setLblNodSum();
            //setLblWarnSum();
			break;
		case PRINTER:            
            p_printer->_show();
			break;
		case LOGOUT:
//            if(curNet >= 0 && curNode >= 0 && curNet < 2 && curNode < BtnNodeNUm)
//			{
//				p_mod->unreg( curNet, curNode);
//                //setBtnFalg(curNode, ERROR);
//                setBtnFalg(curNode, UNABLE);
//                lblNode0 -> setText("0");//网络0节点数
//                lblNode1 -> setText("0");//网络1节点数
//                lblWarnSumOne->setText("0");//网络报警数
//                lblWarnSumTwo->setText("0");//网络故障数

//				checkError();
//				WarnMsg::insertNodeRemove(curNet,curNode);
//			}
//			else
//			{
//				Message::_show(tr("节点不存在!"));
//			}
//			setLblNodSum();
//            setLblWarnSum();
            memset(Db::username,0,sizeof(Db::username));
			break;
		case REBOOT:
            //::system("reboot -f");
            //::system("killall -9 addressbook");
            ::system("/etc/init.d/rcS_next");
			break;
        case TRY:
            Module::TryAllNode(0);
            Module::TryAllNode(1);
//            if(curNet >= 0 && curNode > 0 && curNet < 2 && curNode <= BtnNodeNUm)
//            {
//                Pake::send( curNet, curNode, SET_MOD_TRY, NULL, 0);
//            }
//            else
//            {
//                Message::_show(tr("没有选择节点!"));
//            }
            break;
		case RESET:
            //mainpower=0;//
            //prepower=0;//
	        errorLed=0;//
	        warnLed=0;//
	        error=0;//
	        warn=0;//
            //offStat=0;//
            //onStat=0;//
            //preStat=0;//
            //mainStat=0;
            //off=0;//
            //on=0;//
            //preJ4=0;//
            //relayStats=0;//
            //warnRelay = 0;
            //Led::CtlOff();//
			setBellAndLedStatus();
			for( int i = 0 ; i < 2; i ++)
			{
                for(int j = 1 ; j <= BtnNodeNUm; j ++)
				{
					p_mod->setIsReset( i, j, true);
				}
			}
            
			checkError();
			//checkWarn();
			powerCheck();
		   // setBellAndLedStatus();
            for(int id=1;id<=BtnNodeNUm;id++)
			{
				mo=p_mod->getNode(curNet,id);
				if(mo==NULL) continue;
                if(mo->isHave==true && mo->flag==UNABLE)
				{
                    printf("now enter mo->flag==UNABLE\n");
					WarnMsg::insertEAlarm(curNet,id);
					Bell::error();
					Led::modErrorLightOn();
				}
			}
			for(int i=0;i<5000;i++)
			{
				for(int j=0;j<5000;j++)
				{
					;
				}
			}
			break;
		case CHECK:
	        //mainpower=0;//
	        //prepower=0;//
	        errorLed=0;//
	        warnLed=0;//
	        error=0;//
	        warn=0;//
	        //offStat=0;//
	        //onStat=0;//
	        //off=0;//
	        //on=0;//
	        //preJ4=0;//
	        //relayStats=1;//
            //Led::CtlOff();//
			setBellAndLedStatus();
            //Main::LCDmain();
			//p_timer->stop();
            p_check->_show();
			//p_timer->start(1000);
			/*for(int id=1;id<=110;id++)
			{
				mo = p_mod->getNode(curNet,id);
				if(mo==NULL) continue;
				if(mo->isHave==true && mo->flag==ERROR)
				{
					WarnMsg::insertEAlarm(curNet,id);
					//setBellAndLedStatus();
					Bell::error();
					Led::modErrorLightOn();
				}
			}*/
	        /*mainpower=0;//
	        prepower=0;//
	        errorLed=0;//
	        warnLed=0;//
	        error=0;//
	        warn=0;//
	        offStat=0;//
	        onStat=0;//
	        off=0;//
	        on=0;//
	        preJ4=0;//
	        relayStats=1;//
	        Led::CtlOff();//
			setBellAndLedStatus();*/
            for(int id=1;id<=BtnNodeNUm;id++)
			{
				mo = p_mod->getNode(curNet,id);
				if(mo==NULL) continue;
                if(mo->isHave==true && mo->flag==UNABLE)
				{
					//WarnMsg::insertEAlarm(curNet,id);
					//Bell::error();
					Led::modErrorLightOn();
					//errorLed=1;
					//error=1;
			        //setBellAndLedStatus();
				}
			}
		//	setBellAndLedStatus();
		//	p_timer->stop();
		//	p_check->_show();
		//	p_timer->start(1000);
            //sig.send();
			checkError();
			checkWarn();
			if(warnLed==1)
			{
				Led::warnLightOn();               
			}
			if(errorLed==1)
			{
				Led::modErrorLightOn();
			}
			//powerCheck();
			//setBellAndLedStatus();
			break;
	}
	whoChePwd = NONE;
}
/*============= 检查故障 ================*/
void Main::checkError()
{
	if(p_mod -> errorCount() > 0 ||  mainpower || prepower  || onStat || offStat)
	{//故障
		errorLed =  1;
	}
	else
	{
		error = 0;
		errorLed = 0;
	}
}
/*============= 检查报警 ===============*/
void Main::checkWarn()
{
	if(p_mod->warnCount() > 0)
	{
		warnLed = 1;
	}
	else
	{
		warnLed = 0;
		warn = 0;
	}
}
/*============= 检查报警控制Relay ===============*/
void Main::checkRelayWarn()
{printf("checkRelayWarn\n");
    if(p_mod->warnCount() > 0)
    {
        warnRelay = 1;
    }
    else
    {
        warnRelay = 0;
    }
}
//============ 初始化当前信息子节点 ============
void Main::initSubNode()
{
	int i;
	int x = 250, y = 10 , w = 90, h = 20;
	int xw = 100, xh = 30;
	lbl_subNode = new struct LblSubNode[8];
	for( i = 0; i < 8 ; i++)
	{
		lbl_subNode[i].lbl.setParent(frame_2);
		lbl_subNode[i].lbl.setText(QString::number(i)+tr(":"));
		lbl_subNode[i].lblValue.setParent(frame_2);
		lbl_subNode[i].id = i;
		lbl_subNode[i].flag = NORMAL;
		if(i%4 == 0 && i != 0){
			x = 250;
			y += xh;
		}
		lbl_subNode[i].lbl.setGeometry( x, y, 20, h);
                lbl_subNode[i].lblValue.setGeometry( x + 20, y, w-20, h);
		lbl_subNode[i].lbl.setVisible(true);
		lbl_subNode[i].lblValue.setVisible(true);
		x += xw;
	}
}
void Main::initConnect()
{//连接信号于槽
    for(int i = 0; i < BtnNodeNUm ; i++)
	connect(&btn_node[i].btn,SIGNAL(clicked()),this,SLOT(slot_btn_node()),Qt::QueuedConnection);//节点按钮
    connect(lblWarnSumOne,SIGNAL(clicked()),this,SLOT(slot_WarnSumOne()));
    connect(lblWarnSumTwo,SIGNAL(clicked()),this,SLOT(slot_WarnSumTwo()));
	connect(btn_reset,SIGNAL(clicked()),this,SLOT(slot_btn_reset()));//复位
	connect(btn_query,SIGNAL(clicked()),this,SLOT(slot_query()));//查询
	connect(btn_relogin,SIGNAL(clicked()),this,SLOT(slot_relogin()));//重新登录
	connect(btn_sysCheck,SIGNAL(clicked()),this,SLOT(slot_check_main()));//系统检测
	connect(btn_reboot,SIGNAL(clicked()),this,SLOT(slot_reboot()));//系统重启
    connect(btn_tuo,SIGNAL(clicked()),this,SLOT(slot_put_off()));//--脱扣  复位
	connect(btn_logout,SIGNAL(clicked()),this,SLOT(slot_logout()));//模块注销
	connect(btn_try,SIGNAL(clicked()),this,SLOT(slot_btn_try()));//试验
	connect(btn_sysSet,SIGNAL(clicked()),this,SLOT(slot_sys()));//系统设置
	connect(btn_noSound,SIGNAL(clicked()),this,SLOT(slot_no_sound()));//静音
    connect(btn_noSound,SIGNAL(pressed()),this,SLOT(slot_start_sound()));//静音
    connect(btn_noSound,SIGNAL(released()),this,SLOT(slot_stop_sound()));//静音
	connect(btnNet0,SIGNAL(clicked()),this,SLOT(slot_net()));//单击网络
	connect(btnNet1,SIGNAL(clicked()),this,SLOT(slot_net()));//单击网络
	connect(btn_printer, SIGNAL(clicked()), this, SLOT(slot_printer()));
	connect(btn_help, SIGNAL(clicked()), this, SLOT(slot_help()));
	connect(p_timer,SIGNAL(timeout()),this,SLOT(slot_timer()));//显示系统时间
    connect(pic_timer, SIGNAL(timeout()), this, SLOT(pic_handle()));//自动上传
    //connect(pic_rebuild_timer, SIGNAL(timeout()), this, SLOT(pic_rebuild()));//自动上传
    connect(s_timer, SIGNAL(timeout()), this, SLOT(sound_timer()));
    //connect(led_timer, SIGNAL(timeout()), this, SLOT(led_slot_timer()));
}
void Main::showHowNet()
{
	btnNet1->setVisible(false);
	lblNode1->setVisible(false);
    //lblWarnSumTwo->setVisible(false);
}
Main::~Main()
{
	Db::close();
	delete[] btn_node;
	delete[] lbl_subNode;
	delete  p_imf;
	delete 	p_query;	//查询界面指针
	delete 	p_check;	//系统检测
	delete 	p_putOff;	//脱扣
	delete 	p_sys;		//系统管理
	delete 	p_relog;	//重启
	//delete 	p_rx;	//接收数据
	delete 	p_timer;	//1s定时器
	delete 	p_mod;		//模块链表
	delete	p_chePwd;	//密码验证
	printf("exit Main\n");
}
//test is new object right
void Main::newErrorTest()
{
	if( p_imf == NULL)
	{
		printf("p_imf new error\n");
	}
	if( p_query == NULL)
	{
		printf(" p_query new error\n");
	}
	if(p_check == NULL)
	{
		printf("p_check new error\n");
	}
	if(p_putOff == NULL)
	{
		printf("p_putOff new error\n");
	}
	if( p_sys == NULL)
	{
		printf(" p_sys new error\n");
	}
	if(p_relog == NULL)
	{
		printf("p_relog new error\n");
	}
	if(p_timer == NULL)
	{
		printf("p_timer new error\n");
	}
	if(p_mod == NULL)
	{
		printf("p_mod new error\n");
	}
	if(p_chePwd == NULL)
	{
		printf("p_chePwd new error\n");
	}
}

void Main::deleteall()
{
    WarnMsg::delnowAll();
    WarnMsg::delnowerrAll();
}

//写下节点数
void Main::setLblNodSum()
{
	char ch[20];
	sprintf(ch,"%d",p_mod->nodeCount(0));
	lblNode0 -> setText(tr(ch));//网络0节点数
	if(NET == 1) return;
	sprintf(ch,"%d",p_mod->nodeCount(1));
	lblNode1 -> setText(tr(ch));//网络1节点数
}
//写下报警数
void Main::setLblWarnSum()
{
	char ch[20];
#if 1
    sprintf(ch,"%d",p_mod->warnCount());
    lblWarnSumOne->setText(tr(ch));//网络报警数
    sprintf(ch,"%d",p_mod->errorCount());
    lblWarnSumTwo->setText(tr(ch));//网络故障数
    sprintf(ch,"%d",p_mod->warnerrorCount());
    lblWarnSum->setText(tr(ch));
    //lblWarnSum->setVisible(false);
#else
    //sprintf(ch,"%d",p_mod->warnCount(0));
    sprintf(ch,"%d",p_mod->warnerrorCount(0));
	lblWarnSumOne->setText(tr(ch));//网络0报警数
    if(NET == 1) return;
    //sprintf(ch,"%d",p_mod->warnCount(1));
    sprintf(ch,"%d",p_mod->warnerrorCount(1));
	lblWarnSumTwo->setText(tr(ch));//网络1报警数
 #endif
}
//清除颜色
void Main::clearColor(QWidget& qw)
{
	qw.setStyleSheet(QString::fromUtf8(""));
}
//正常颜色
void Main::normalColor(QWidget& qw)
{
	qw.setStyleSheet(QString::fromUtf8("background-image:url(:/img/images/btnnormal.png);"));
}
//报警颜色
void Main::warnColor(QWidget& qw)
{
	qw.setStyleSheet(QString::fromUtf8("background-image:url(:/img/images/btnwarn.png);"));
}
//报警颜色
void Main::errorColor(QWidget& qw)
{
	qw.setStyleSheet(QString::fromUtf8("background-image:url(:/img/images/btnerror.png);"));
}
//掉线颜色
void Main::unableColor(QWidget& qw)
{
    qw.setStyleSheet(QString::fromUtf8("background-image:url(:/img/images/btnunable.png);"));
}
void Main::printfCPU()
{
	struct cpustatus cpu_stat;
	get_cpu_status(& cpu_stat);
	printf("user\t nice\t system\t free\n");
	printf("%4.2f\t %4.2f\t %4.2f\t %4.2f\n",cpu_stat.user,cpu_stat.nice,cpu_stat.system,cpu_stat.idle);
}
void Main::get_cpu_status(struct cpustatus *cpu_stat)
{
        unsigned int total;
        float   user;
        float   nice;
        float   system;
        float   idle;
        char   cpu[21];
        char   text[201];
        FILE   *fp;
      	if( (fp = fopen("/proc/stat","r")) == NULL){
		perror("open cpuinfo error.\n");
		return;
	}
        while( fgets( text, 200, fp) != NULL ){
             	if( strstr(text,"cpu") != NULL){
              		sscanf(text,"%s %f %f %f %f",cpu, &user, &nice, &system, &idle);
	      	}
        }
        fclose(fp);
        total=(user+nice+system+idle);
        user=(user/total)*100;
        nice=(nice/total)*100;
        system=(system/total)*100;
        idle=(idle/total)*100;
        cpu_stat->total = total;
        cpu_stat->user = user;
        cpu_stat->nice = nice;
        cpu_stat->system = system;
        cpu_stat->idle = idle;
}

void Main::hideAll()
{
    btn_relogin->setVisible(false);
    lbl_tuo_2->setVisible(false);
    btn_reset->setVisible(false);
    label_3->setVisible(false);
    lbl_sysCheck->setVisible(false);
    btn_sysCheck->setVisible(false);
    lbl_reboot_2->setVisible(false);
    btn_logout->setVisible(false);
    lbl_sysSet->setVisible(false);
    btn_query->setVisible(false);
    lbl_tuo->setVisible(false);
    lbl_logout->setVisible(false);
    btn_try->setVisible(false);
    btn_sysSet->setVisible(false);
    btn_reboot->setVisible(false);
    btn_noSound->setVisible(false);
    lbl_sysCheck_2->setVisible(false);
    lbl_reboot->setVisible(false);
    btn_tuo->setVisible(false);
    lbl_reboot_3->setVisible(false);
    nodePerent->setVisible(false);
    frame_2->setVisible(false);
    lblNode->setVisible(false);
    lblNet->setVisible(false);
    label_14->setVisible(false);
    label_32->setVisible(false);
    label_27->setVisible(false);
    lblXing->setVisible(false);
    label->setVisible(false);
    frame_3->setVisible(false);
    label_7->setVisible(false);
    lblWarnSumOne->setVisible(false);
    lblLocalTime->setVisible(false);
    lblWarnSumTwo->setVisible(false);
    btnNet1->setVisible(false);
    label_8->setVisible(false);
    lblNode0->setVisible(false);
    btnNet0->setVisible(false);
    lblNode1->setVisible(false);
    frame->setVisible(false);
    frame_4->setVisible(false);
    lbl_reboot_4->setVisible(false);
    btn_printer->setVisible(false);
    label_4->setVisible(false);
    btn_help->setVisible(false);
}

void Main::displayAll()
{
    btn_relogin->setVisible(true);
    lbl_tuo_2->setVisible(true);
    btn_reset->setVisible(true);
    label_3->setVisible(true);
    lbl_sysCheck->setVisible(true);
    btn_sysCheck->setVisible(true);
    lbl_reboot_2->setVisible(true);
    btn_logout->setVisible(true);
    lbl_sysSet->setVisible(true);
    btn_query->setVisible(true);
    lbl_tuo->setVisible(true);
    lbl_logout->setVisible(true);
    btn_try->setVisible(true);
    btn_sysSet->setVisible(true);
    btn_reboot->setVisible(true);
    btn_noSound->setVisible(true);
    lbl_sysCheck_2->setVisible(true);
    lbl_reboot->setVisible(true);
    btn_tuo->setVisible(true);
    lbl_reboot_3->setVisible(true);
    nodePerent->setVisible(true);
    frame_2->setVisible(true);
    lblNode->setVisible(true);
    lblNet->setVisible(true);
    label_14->setVisible(true);
    label_32->setVisible(true);
    label_27->setVisible(true);
    lblXing->setVisible(true);
    label->setVisible(true);
    frame_3->setVisible(true);
    label_7->setVisible(true);
    lblWarnSumOne->setVisible(true);
    lblLocalTime->setVisible(true);
    lblWarnSumTwo->setVisible(true);
    btnNet1->setVisible(true);
    label_8->setVisible(true);
    lblNode0->setVisible(true);
    btnNet0->setVisible(true);
    lblNode1->setVisible(true);
    frame->setVisible(true);
    frame_4->setVisible(true);
    lbl_reboot_4->setVisible(true);
    btn_printer->setVisible(true);
    label_4->setVisible(true);
    btn_help->setVisible(true);
}


void Main::LCDmain()
{
    QPalette bgdefaultPalette;

    printf("now enter LCDmain  colorcount == %d\n",colorcount);
//    QPalette bgdefaultPalette = this->palette();
//    bgdefaultPalette.setBrush(QPalette::Background,bgImages);
//    this->setPalette(bgPalette);
    if(flagcolor == 0)
    {//printf("now enter flagcolor == %d\n",flagcolor);
        bgdefaultPalette = this->palette();
        flagcolor = 1;
    }

//    QBrush defaultbrush = bgdefaultPalette.background();
//    QColor defaultcol = defaultbrush.color();

    hideAll();
    switch(colorcount)
    {
    case 0:
        setPalette(bgdefaultPalette);
        displayAll();
        this->update();
        colorcount = 1;
        break;
    case 1:
        setPalette(Qt::red);
        this->update();
        colorcount = 2;
        break;
    case 2:
        setPalette(Qt::blue);
        this->update();
        colorcount = 3;
        break;
    case 3:
        setPalette(Qt::green);
        this->update();
        colorcount = 4;
        break;
    case 4:
        setPalette(Qt::black);
        this->update();
        colorcount = 5;
        break;
    case 5:
        colorcount = 0;
        setPalette(bgdefaultPalette);
        displayAll();
        this->update();
        break;
    default:
        break;
    }

 //    usleep(1000000);
    //setStyleSheet ("background-color: rgb(0,0,0);color: rgb(255,255,255);");
   // this->setPixmap(QPixmap(QString::fromUtf8(":/img/images/blue.png")));
    //this->setStyleSheet("background-color: #000000;color: #ffffff");
//    this->setAutoFillBackground(true);
//    QPalette p=this->palette();
//    p.setColor(QPalette::Window,QColor (0,0,0,255));//p.setBrush(QPalette::Window,brush);
//    p.setBrush(QPalette::Background, QBrush(QPixmap(":/img/images/blue.png")));
//    this->setPalette(p);
     //setPalette(Qt::blue);
    //QWidget类构造函数内
//    QPalette p;
//    p.setBrush(this->backgroundRole(),QBrush(QColor(51,51,51)));
//    this->setPalette(p);
//    this->setAutoFillBackground(true);

//    QPalette bgpal = palette();
//    bgpal.setColor(QPalette::Background, QColor(0, 0 , 0, 255));
//    //bgpal.setColor (QPalette::Background, Qt::transparent);
//    bgpal.setColor (QPalette::Foreground, QColor(0, 0 , 0,255));
//    setPalette(bgpal);
//      QPainter p(this);
//      p.setCompositionMode(
//      QPainter::CompositionMode_Clear ); p.fillRect( 10, 10, 300,
//      300, Qt::SolidPattern );
}

 void Main::paintEvent( QPaintEvent * )
 {
    //QPalette bgdefaultPalette = this->palette();
    //printf("colorcount == %d  now enter paintEvent\n",colorcount);
 }
