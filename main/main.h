/*=================================
		主界面
=================================*/
#ifndef LINLONG_MAIN
#define LINLONG_MAIN

#include <QWidget>
#include <QString>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QWidget>
#include <time.h>
#include <QWSInputMethod>
#include <QWSServer>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>
#include <QProgressBar>
#include<QPixmap>
#include <QDesktopWidget>

#include "ui_main.h"
#include "query.h"
#include "check.h"
#include "relogin.h"
#include "checkPwd.h"
#include "put_off.h"
#include "nodeStatus.h"
#include "message.h"

#include "sys/sys.h"
#include "keyboard/imframe.h"
#include "module/modList.h"
#include "define/define.h"
#include "rxdata.h"
#include "signals.h"
#include "sql/db.h"
#include "sql/node.h"
#include "sql/warnMsg.h"
#include "sql/optMsg.h"
#include "sql/dbuser.h"
#include "sql/mater.h"
#include "device/bell/bell.h"
#include "device/led/led.h"
#include "device/rtc/rtc.h"
#include "device/power/power.h"
#include "device/watchdog/watchdog.h"
#include "print.h"
#include "printer.h"
#include "help.h"
#include "qpainter.h"
#include "frminput/frminput.h"
#include "SYSZUXpinyin/syszuxim.h"
#include "SYSZUXpinyin/syszuxpinyin.h"
#include "nodeStatus.h"
#include "mylabel.h"

#define NORMAL 	1
#define WARN	2
#define ERROR	0
#define UNABLE  3

#define MA	0
#define A	1
#define C	2
#define HAVENET 2 //0 只有 0 net 1 只有  1 net  2两个都有

#define NONE	0
#define SYS	1
#define TUO	2
#define LOGOUT	3
#define REBOOT	4
#define RESET	5
#define CHECK	6
#define PRINTER 7
#define TRY 8

#define DATCOU	9 //当前显示的数据9个
#define WIAT_SEC 900000//
#define BtnNodeNUm 128

/*====================================
	结构体：显示节点封装;
	btn: 显示的按钮;
	flag: 节点的状态;
====================================*/
struct BtnNode{
	QPushButton btn;
	int flag;
};
/*====================================
	结构体： 显示子节点封装;
	lbl:  编号;
	lblValue: 数值;
	sudid: 子节点编号;
	flag: 节点的状态;
====================================*/
struct LblSubNode{
	QLabel	lbl;
	QLabel	lblValue;
	int 	id;
	int 	flag;
};
//cpu
struct cpustatus
{
        long  total;
        float user;
        float nice;
        float system;
        float idle;
};
//int whoChePwd;

class  Main:public QWidget,public Ui_MainForm
{
        Q_OBJECT
public :
        Main(QProgressBar *proBar,QWidget* parent = NULL);
        virtual ~Main();
	void setLblNodSum();
	void setLblWarnSum();
	/*===========================================================
		功能:改变按钮节点状态 (正常 报警 预警 故障 取消节点);
		 id: 节点 号 ;
	       falg: NORMAL 正常, PREWARN 预警, WARN 报警 , ERROR 故障 ;
	============================================================*/
	void setBtnFalg(int id,int flag);
	void initBtnNode();//初始化节点按钮
	void initSubNode();//初始化子节点
	void initConnect();//连接信号于槽
	void delBtnNode();//删除节点按钮
	/*=============================================
		功能:预警报警显示;
		net: 网络号; id: 节点号 ,subNode 子节点
		status: 报警类型,value 数值 , unit 单位 
	=============================================*/
	void ctlBell();//控制蜂鸣器
	void initCurrentNode();//加载当前节点
	void showCurrentNet(int net);//显示当前网络
	void showCurrentA();//显示当前漏电电流
	/*=================显示子节点的颜色 =================*/
	void setSubNodeStat(int value, struct LblSubNode *sudNode,int cora);
	void showNOPagSubNode(struct mod *mo);//第一页子节点显示
	/*================ 网络数 ===================*/
	void showHowNet();

	void clearColor(QWidget& qw);
	void normalColor(QWidget& qw);
	void warnColor(QWidget& qw);
	void errorColor(QWidget& qw);
    void unableColor(QWidget& qw);
	void printfCPU();
	void get_cpu_status(struct cpustatus *cpu_stat);
	//================== 电源检测 ================
	void powerCheck();
	/*=============清空子节点数据===============*/
	void clearSubNodeDat();
	/*============= 检查故障 ================*/
	void checkError();
	/*============= 检查报警 ===============*/
	void checkWarn();
    /*============= 检查报警控制Relay ===============*/
    void checkRelayWarn();
	/*============ 检测密码 ===============*/
	void check_pwd();
	void setBellAndLedStatus();
	void newErrorTest();
//	void set_pwd(int a);
    void LCDmain();
    void hideAll();
    void displayAll();
    void paintEvent( QPaintEvent * );

public :
	IMFrame *p_imf;			//键盘
    //SyszuxIM* im_my;		//键盘
	static int 	screenWaitTime; //屏幕保护时间s
	static int  com_led;
	Printer         *p_printer;
	Help            *p_help;
	Query 		*p_query;	//查询界面指针
	Check 		*p_check;	//系统检测
	PutOff 		*p_putOff;	//脱扣
	Sys 		*p_sys;		//系统管理
	Relogin 	*p_relog;	//重启
	//RxThread 	*p_rx;		//接收数据
	QTimer 		*p_timer;	//1s 定时器
    QTimer 		*pic_rebuild_timer;
	QTimer          *pic_timer;       //
    QTimer      *s_timer;
    QTimer      *led_timer; //通讯灯闪烁变化定时器－－－－－－－－－－－－－
	Module 		*p_mod;		//模块链表
	CheckPwd	*p_chePwd;	//密码验证
	NodeStatus      *p_nodeStatus;	//节点的详细状态
	Signals         sig;
	struct BtnNode 	*btn_node;	//节点按钮
	struct LblSubNode *lbl_subNode;	//子节点
    QObject *p_Mset;
	int 		curNet;		//当前显示的网络 默认0
	int 		curNode;	//当前选择的节点 默认-1
	int 		whoReset;	//谁复位 0 启动复位 1 按钮复位
    static int 		mainpower;	//主电源
    static int 		prepower;	//备电源
	int 		errorLed;	//节点故障灯
	int 		warnLed;	//led报警灯
    int         warnRelay;  //报警控制继电器

	int		off;		//断路 
	int 		on;		//短路
    static int 		offStat;
    static int 		onStat;
    int         preStat;
    int         mainStat;
	int 		preJ4;		//j4电平
	int 		relayStats;	//继电器状态
	int 		error;		//故障
	int 		warn;		//报警
	int 		screenCount;	//计算器
   static int 		whoChePwd;
	//显示当前电流 、 温度 、漏电数值
	int  		dataA[DATCOU];	//当前电流值
	int 		showCrurrent;	//当前显示的页
	int 		AruCount;	//延时计数器
	int 		time_min;	//时间的分位保存
	int 		timer_count;	
	int 		timer_countPower;
    int         colorcount;
    int         flagcolor;
    static int  flagnosound;
    static int  flagreset;
    static int  WarnSumOne;

public slots:
	void slot_printer();
	void slot_help();
    void slot_WarnSumOne();
    void slot_WarnSumTwo();
	void slot_query();		//查询
	void slot_relogin();		//登录
	void slot_sys();		//系统管理
	void slot_check_main();		//系统检测
	void slot_reboot();		//系统重启
	void slot_put_off();		//脱扣
	void slot_logout();		//模块注销
	void slot_btn_try();		//试验
	void slot_no_sound(); 		//静音
    void slot_start_sound();
    void slot_stop_sound();
	void slot_btn_node();		//node 按钮
	void slot_btn_reset();		//主机复位
	void slot_net();		//单击网络
	void slot_timer();		//定时器
    void pic_rebuild();
	void pic_handle();
    void sound_timer();
    void led_slot_timer();
	void clearScreenCount();
public:
	void slot_warn();		//报警
	void slot_reg(int net,int id);	//注册
	void slot_mod();		//型号
	void slot_cur_val();	//当前数据

	void slot_ans_reset();	//回复复位
	void slot_ans_try();	//回复试验
	void slot_error(int net,int id);
//	void set_pwd(int a);
};
#endif
