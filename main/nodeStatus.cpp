/*======================================
	功能：显示节点的状态，报警、故障、
	          正常显示。记录报警故障信息。
	          时间 、 数值等。
	文件名：nodeStatus.h
=======================================*/
#include "nodeStatus.h"
#include "sql/node.h"
#include <QWidget>
#include "main.h"
/*====================================
	功能：初始化资源
====================================*/
NodeStatus::NodeStatus(QWidget *parent): QWidget(parent),Ui_NodeStatus()
{
	setupUi(this);
	par = parent;
        setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);//窗口没有没有边框  是 一个模太对话框

	connect( btn_reset, SIGNAL(clicked()), this, SLOT(slot_reset()));
	connect( btn_try, SIGNAL(clicked()), this, SLOT(slot_try()));
	connect( btn_close, SIGNAL(clicked()), this, SLOT(slot_hide()));
	connect( btn_no_wo, SIGNAL(clicked()), this, SLOT(slot_clear()));
	curNet = -1;
	curId = -1;
	setAttribute(Qt::WA_DeleteOnClose);
	printf("init NodeStatus ok\n");
}
/*====================================
	功能：退出函数
====================================*/
NodeStatus::~NodeStatus()
{
	printf("exit NodeStatus\n");
}
/*====================================
	功能：显示节点的状态
	mod：节点的型号
====================================*/
void NodeStatus::_show(int net,int id,int mod,int stat)
{
	lblVal0->setText(tr(""));
	lblVal1->setText(tr(""));
	lblVal2->setText(tr(""));
	lblVal3->setText(tr(""));
	lblVal4->setText(tr(""));
	lblVal5->setText(tr(""));
	lblVal6->setText(tr(""));
	lblVal7->setText(tr(""));
	
	curNet = net;
	curId = id;
	curMod = mod;

	switch( curMod )
	{
		case ML1T1:
                lblThis->setText(tr("网络号:")+QString::number(net)+tr(" 节点号:")+QString::number(id)+tr(" 型号:")+Module::moTyp[mod].name+tr("(1路剩余电流,1路温度)"));
                if (Module::getSubError(net, id, 0))
			fillRow( lbl0, lblstat0, net, id, 0, ERROR, true);
		else if (Module::getSubWarn(net, id, 0))
			fillRow( lbl0, lblstat0, net, id, 0, WARN, true);
		else
                	fillRow( lbl0, lblstat0, net, id, 0, NORMAL, true);
                fillRow( lbl1, lblstat1, net, id, 1, stat, true);
                fillRow( lbl2, lblstat2, net, id, 2, stat, true);
                fillRow( lbl3, lblstat3, net, id, 3, stat, true);
		if (Module::getSubError(net, id, 4))
			fillRow( lbl4, lblstat4, net, id, 4, ERROR, true);
		else if (Module::getSubWarn(net, id, 4))
			fillRow( lbl4, lblstat4, net, id, 4, WARN, true);
		else
                	fillRow( lbl4, lblstat4, net, id, 4, NORMAL, true);
                fillRow( lbl5, lblstat5, net, id, 5, stat, true);
                fillRow( lbl6, lblstat6, net, id, 6, stat, true);
                fillRow( lbl7, lblstat7, net, id, 7, stat, true);
                break;
		case DL1T1:
                lblThis->setText(tr("网络号:")+QString::number(net)+tr(" 节点号:")+QString::number(id)+tr(" 型号:")+Module::moTyp[mod].name+tr("(独立式,1路剩余电流,1路温度)"));
                if (Module::getSubError(net, id, 0))
                    fillRow( lbl0, lblstat0, net, id, 0, ERROR, true);
                else if (Module::getSubWarn(net, id, 0))
                    fillRow( lbl0, lblstat0, net, id, 0, WARN, true);
                else
                    fillRow( lbl0, lblstat0, net, id, 0, NORMAL, true);
                        //fillRow( lbl1, lblstat1, net, id, 1, stat, true);
                        //fillRow( lbl2, lblstat2, net, id, 2, stat, true);
                        //fillRow( lbl3, lblstat3, net, id, 3, stat, true);
                        fillRow( lbl1, lblstat1, net, id, 1, UNABLE, true);
                        fillRow( lbl2, lblstat2, net, id, 2, UNABLE, true);
                        fillRow( lbl3, lblstat3, net, id, 3, UNABLE, true);
                if (Module::getSubError(net, id, 4))
                    fillRow( lbl4, lblstat4, net, id, 4, ERROR, true);
                else if (Module::getSubWarn(net, id, 4))
                    fillRow( lbl4, lblstat4, net, id, 4, WARN, true);
                else
                    fillRow( lbl4, lblstat4, net, id, 4, NORMAL, true);
                        //fillRow( lbl5, lblstat5, net, id, 5, stat, true);
                        //fillRow( lbl6, lblstat6, net, id, 6, stat, true);
                        //fillRow( lbl7, lblstat7, net, id, 7, stat, true);
                        fillRow( lbl5, lblstat5, net, id, 5, UNABLE, true);
                        fillRow( lbl6, lblstat6, net, id, 6, UNABLE, true);
                        fillRow( lbl7, lblstat7, net, id, 7, UNABLE, true);
                break;
		case ML4T4:
		lblThis->setText(tr("网络号:")+QString::number(net)+tr(" 节点号:")+QString::number(id)+tr(" 型号:")+Module::moTyp[mod].name+tr("(4路剩余电流,4路温度)"));
                if (Module::getSubError(net, id, 0))
                        fillRow( lbl0, lblstat0, net, id, 0, ERROR, true);
                else if (Module::getSubWarn(net, id, 0))
                        fillRow( lbl0, lblstat0, net, id, 0, WARN, true);
                else    
                        fillRow( lbl0, lblstat0, net, id, 0, NORMAL, true);
                if (Module::getSubError(net, id, 1))
                        fillRow( lbl1, lblstat1, net, id, 1, ERROR, true);
                else if (Module::getSubWarn(net, id, 1))
                        fillRow( lbl1, lblstat1, net, id, 1, WARN, true);
                else    
                        fillRow( lbl1, lblstat1, net, id, 1, NORMAL, true);
                if (Module::getSubError(net, id, 2))
                        fillRow( lbl2, lblstat2, net, id, 2, ERROR, true);
                else if (Module::getSubWarn(net, id, 2))
                        fillRow( lbl2, lblstat2, net, id, 2, WARN, true);
                else    
                        fillRow( lbl2, lblstat2, net, id, 2, NORMAL, true);
                if (Module::getSubError(net, id, 3))
                        fillRow( lbl3, lblstat3, net, id, 3, ERROR, true);
                else if (Module::getSubWarn(net, id, 3))
                        fillRow( lbl3, lblstat3, net, id, 3, WARN, true);
                else    
                        fillRow( lbl3, lblstat3, net, id, 3, NORMAL, true);
                if (Module::getSubError(net, id, 4))
                        fillRow( lbl4, lblstat4, net, id, 4, ERROR, true);
                else if (Module::getSubWarn(net, id, 4))
                        fillRow( lbl4, lblstat4, net, id, 4, WARN, true);
                else    
                        fillRow( lbl4, lblstat4, net, id, 4, NORMAL, true);
                if (Module::getSubError(net, id, 5))
                        fillRow( lbl5, lblstat5, net, id, 5, ERROR, true);
                else if (Module::getSubWarn(net, id, 5))
                        fillRow( lbl5, lblstat5, net, id, 5, WARN, true);
                else    
                        fillRow( lbl5, lblstat5, net, id, 5, NORMAL, true);
                if (Module::getSubError(net, id, 6))
                        fillRow( lbl6, lblstat6, net, id, 6, ERROR, true);
                else if (Module::getSubWarn(net, id, 6))
                        fillRow( lbl6, lblstat6, net, id, 6, WARN, true);
                else    
                        fillRow( lbl6, lblstat6, net, id, 6, NORMAL, true);
                if (Module::getSubError(net, id, 7))
                        fillRow( lbl7, lblstat7, net, id, 7, ERROR, true);
                else if (Module::getSubWarn(net, id, 7))
                        fillRow( lbl7, lblstat7, net, id, 7, WARN, true);
                else    
                        fillRow( lbl7, lblstat7, net, id, 7, NORMAL, true);
                break;
		case ML8:
		lblThis->setText(tr("网络号:")+QString::number(net)+tr(" 节点号:")+QString::number(id)+tr(" 型号:")+Module::moTyp[mod].name+tr("(8路剩余电流)"));
                if (Module::getSubError(net, id, 0))
                        fillRow( lbl0, lblstat0, net, id, 0, ERROR, true);
                else if (Module::getSubWarn(net, id, 0))
                        fillRow( lbl0, lblstat0, net, id, 0, WARN, true);
                else
                        fillRow( lbl0, lblstat0, net, id, 0, NORMAL, true);
                if (Module::getSubError(net, id, 1))
                        fillRow( lbl1, lblstat1, net, id, 1, ERROR, true);
                else if (Module::getSubWarn(net, id, 1))
                        fillRow( lbl1, lblstat1, net, id, 1, WARN, true);
                else
                        fillRow( lbl1, lblstat1, net, id, 1, NORMAL, true);
                if (Module::getSubError(net, id, 2))
                        fillRow( lbl2, lblstat2, net, id, 2, ERROR, true);
                else if (Module::getSubWarn(net, id, 2))
                        fillRow( lbl2, lblstat2, net, id, 2, WARN, true);
                else
                        fillRow( lbl2, lblstat2, net, id, 2, NORMAL, true);
                if (Module::getSubError(net, id, 3))
                        fillRow( lbl3, lblstat3, net, id, 3, ERROR, true);
                else if (Module::getSubWarn(net, id, 3))
                        fillRow( lbl3, lblstat3, net, id, 3, WARN, true);
                else
                        fillRow( lbl3, lblstat3, net, id, 3, NORMAL, true);
                if (Module::getSubError(net, id, 4))
                        fillRow( lbl4, lblstat4, net, id, 4, ERROR, true);
                else if (Module::getSubWarn(net, id, 4))
                        fillRow( lbl4, lblstat4, net, id, 4, WARN, true);
                else
                        fillRow( lbl4, lblstat4, net, id, 4, NORMAL, true);
                if (Module::getSubError(net, id, 5))
                        fillRow( lbl5, lblstat5, net, id, 5, ERROR, true);
                else if (Module::getSubWarn(net, id, 5))
                        fillRow( lbl5, lblstat5, net, id, 5, WARN, true);
                else
                        fillRow( lbl5, lblstat5, net, id, 5, NORMAL, true);
                if (Module::getSubError(net, id, 6))
                        fillRow( lbl6, lblstat6, net, id, 6, ERROR, true);
                else if (Module::getSubWarn(net, id, 6))
                        fillRow( lbl6, lblstat6, net, id, 6, WARN, true);
                else
                        fillRow( lbl6, lblstat6, net, id, 6, NORMAL, true);
                if (Module::getSubError(net, id, 7))
                        fillRow( lbl7, lblstat7, net, id, 7, ERROR, true);
                else if (Module::getSubWarn(net, id, 7))
                        fillRow( lbl7, lblstat7, net, id, 7, WARN, true);
                else
                        fillRow( lbl7, lblstat7, net, id, 7, NORMAL, true);
                break;
	}

	Pake::send( curNet, curId, QUE_CUR_VAL, NULL, 0);
	show();
}
/*====================================
	功能：些下当前数值
====================================*/
void NodeStatus::setCurVal(int* val,int sum)
{
	switch( curMod )
	{
	case ML1T1:
	case DL1T1:
        case ML4T4:
                setLblValue( lblVal0, val[0], 1);
                setLblValue( lblVal1, val[1], 1);
                setLblValue( lblVal2, val[2], 1);
                setLblValue( lblVal3, val[3], 1);
                setLblValue( lblVal4, val[4], 0);
                setLblValue( lblVal5, val[5], 0);
                setLblValue( lblVal6, val[6], 0);
                setLblValue( lblVal7, val[7], 0);
                break;
	    case ML8:
                setLblValue( lblVal0, val[0], 1);
                setLblValue( lblVal1, val[1], 1);
                setLblValue( lblVal2, val[2], 1);
                setLblValue( lblVal3, val[3], 1);
                setLblValue( lblVal4, val[4], 1);
                setLblValue( lblVal5, val[5], 1);
                setLblValue( lblVal6, val[6], 1);
                setLblValue( lblVal7, val[7], 1);
                break;
	}
}
void NodeStatus::setLblValue(QLabel *lbl,int value, int cora)
{
	if(cora == 0)
	{//温度
		if(value < 5)
			value = 0;
                lbl->setText(QString::number(value)+tr("℃"));
	}
	else if( cora == 1)
	{//mA
		if(value < 10)
			value = 0;
		lbl->setText(QString::number(value)+tr("mA"));
	}
}
/*====================================
	功能：填充节点信息
====================================*/
void NodeStatus::fillRow(QLabel *lbl,QLabel *lblStats,int net, int id,int subId,int stat,bool isHave)
{
	char *time;
	int val;
	int TOrL = 2; // 1 == t 2 == l normal is l TOrL = 2;
	lblStats->setEnabled(isHave);
	lbl->setEnabled(isHave);
	if(Module::getSubWarn(net,id,subId))
	{
		Module::getWarnTimeAndVal( net, id, subId, &time, &val);

		if ((curMod == ML4T4) || (curMod == ML1T1) || (curMod == DL1T1))
		{
			if(subId>3)
			{
				TOrL = 1;
			}
			else
			{
				TOrL = 2;
			}
		}
		if(curMod == ML8)
		{
			TOrL = 2;
		}
		if( TOrL == 1)
		{ 
			if(val < 10)
			{
                            lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)+tr("℃     ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
			else if(val < 100)
			{
                            lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)+tr("℃    ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
			else
			{
                            lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)+tr("℃   ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
		}
		if( TOrL == 2 )
		{
			if(val < 10)
			{
				lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)
					+tr("mA    ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
			else if(val < 100)
			{
				lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)
					+tr("mA   ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
			else if(val < 1000)
			{
				lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)
					+tr("mA  ")+time+tr(" ")+SqlNode::getAddr(net,id,subId));
			}
			else
			{
				lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)
					+tr("mA ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
		}
        nodeWarn(lblStats);
	}
	else
	{
		lbl->setText(QString::number(subId)+tr("路    正常     -------------------- ")+ SqlNode::getAddr(net,id,subId));
		nodeNormal(lblStats);
	}
	if(stat == ERROR)
	{
		lbl->setText(QString::number(subId)+tr("路    故障     -------------------- ")+ SqlNode::getAddr(net,id,subId));
		nodeError(lblStats);
	}
    if(stat == UNABLE)
    {
        lbl->setText(QString::number(subId)+tr("路    ----     -------------------- ")+ SqlNode::getAddr(net,id,subId));
        nodeUnable(lblStats);
    }

}
/*	if(stat == NORMAL)//原来为“isHave==false”
	{
		lbl->setText(QString::number(subId)+tr("路    正常     -------------------- ")+ SqlNode::getAddr(net,id,subId));
		nodeNormal(lblStats);
		return;
	}
	if(stat == ERROR)
	{
		lbl->setText(QString::number(subId)+tr("路    故障     -------------------- ")+ SqlNode::getAddr(net,id,subId));
		nodeError(lblStats);
		return;
	}
	if(Module::getSubWarn(net,id,subId))//原来为“Module::getSubWarn(net,id,subId)”
	{//报警
		Module::getWarnTimeAndVal( net, id, subId, &time, &val);
		
		if( (curMod == ML4T4))
		{
            if ( subId > 3)
			{
                TOrL = 1;
			}
			else
			{
				TOrL=2;
			}
		}

		if((curMod==MC)||(curMod==ML8))
		{
			TOrL=2;
		}
		
		if( TOrL == 1)
		{ 
			if(val < 10)
			{
                            lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)+tr("℃     ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
			else if(val < 100)
			{
                            lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)+tr("℃    ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
			else
			{
                            lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)+tr("℃   ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
		}
		if( TOrL == 2 )
		{
			if(val < 10)
			{
				lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)
					+tr("mA    ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
			else if(val < 100)
			{
				lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)
					+tr("mA   ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
			else if(val < 1000)
			{
				lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)
					+tr("mA  ")+time+tr(" ")+SqlNode::getAddr(net,id,subId));
			}
			else
			{
				lbl->setText(QString::number(subId)+tr("路    ")+QString::number(val)
					+tr("mA ")+time+tr(" ")+ SqlNode::getAddr(net,id,subId));
			}
		}
		nodeWarn(lblStats);
	}
}*/
/*====================================
	功能：复位
====================================*/
void NodeStatus::slot_reset()
{
	((Main*)par)->slot_btn_reset();
}
/*====================================
	功能：试验
====================================*/
void NodeStatus::slot_try()
{
	Pake::send( curNet, curId, SET_MOD_TRY, NULL, 0);
}
void NodeStatus::slot_clear()
{
	((Main*)par)->slot_no_sound();
}
/*====================================
	功能：hide窗口
====================================*/
void NodeStatus::slot_hide()
{
	hide();
	Pake::send( curNet, curId, QUE_CUR_VAL, NULL, 0);
	curNet = -1;
	curId = -1;
}	
/*====================================
	功能：写下lbl报警
====================================*/
void NodeStatus::nodeWarn(QLabel *lbl)
{
	lbl->setPixmap(QPixmap(QString::fromUtf8(":/img/images/warn1.png")));
}
/*====================================
	功能：写下lbl故障
====================================*/
void NodeStatus::nodeError(QLabel *lbl)
{
	lbl->setPixmap(QPixmap(QString::fromUtf8(":/img/images/err.png")));
}
/*====================================
	功能：写下lbl正常
====================================*/
void NodeStatus::nodeNormal(QLabel *lbl)
{
	lbl->setPixmap(QPixmap(QString::fromUtf8(":/img/images/normal1.png")));
}


/*====================================
    功能：写下lbl不能用
====================================*/
void NodeStatus::nodeUnable(QLabel *lbl)
{
    lbl->setPixmap(QPixmap(QString::fromUtf8(":/img/images/unable.png")));
}
