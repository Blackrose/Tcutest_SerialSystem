/*======================================
	功能：显示节点的状态，报警、故障、
	          正常显示。记录报警故障信息。
	          时间 、 数值等。
	文件名：nodeStatus.h
=======================================*/
#include "nodeStatus.h"
#include "sql/node.h"
#include "main.h"
#include <QWidget>


SyszuxIM* NodeStatus::imf_my;
/*====================================
	功能：初始化资源
====================================*/
NodeStatus::NodeStatus(IMFrame *im, QWidget *parent): QWidget(parent),Ui_NodeStatus()
{
	setupUi(this);
	par = parent;
        setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);//窗口没有没有边框  是 一个模太对话框
    p_imf= im;   
    imf_my = new SyszuxIM();

	connect( btn_reset, SIGNAL(clicked()), this, SLOT(slot_reset()));
	connect( btn_try, SIGNAL(clicked()), this, SLOT(slot_try()));
	connect( btn_close, SIGNAL(clicked()), this, SLOT(slot_hide()));
	connect( btn_no_wo, SIGNAL(clicked()), this, SLOT(slot_clear()));
    connect( btn_ok, SIGNAL(clicked()), this, SLOT(slot_ok()));
    connect( btn_change, SIGNAL(clicked()), this, SLOT(slot_change()));

    //connect(txt0,SIGNAL(textEdited(const QString &)),this,SLOT(txtChange(QString)));
    connect(txt0,SIGNAL(clicked()),this,SLOT(txt0Change()));
    connect(txt1,SIGNAL(clicked()),this,SLOT(txt1Change()));
    connect(txt2,SIGNAL(clicked()),this,SLOT(txt2Change()));
    connect(txt3,SIGNAL(clicked()),this,SLOT(txt3Change()));
    connect(txt4,SIGNAL(clicked()),this,SLOT(txt4Change()));
    connect(txt5,SIGNAL(clicked()),this,SLOT(txt5Change()));
    connect(txt6,SIGNAL(clicked()),this,SLOT(txt6Change()));
    connect(txt7,SIGNAL(clicked()),this,SLOT(txt7Change()));

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
//                fillRow( lbl1, lblstat1, net, id, 1, stat, true);
//                fillRow( lbl2, lblstat2, net, id, 2, stat, true);
//                fillRow( lbl3, lblstat3, net, id, 3, stat, true);
                fillRow( lbl1, lblstat1, net, id, 1, UNABLE, true);
                fillRow( lbl2, lblstat2, net, id, 2, UNABLE, true);
                fillRow( lbl3, lblstat3, net, id, 3, UNABLE, true);
		if (Module::getSubError(net, id, 4))
			fillRow( lbl4, lblstat4, net, id, 4, ERROR, true);
		else if (Module::getSubWarn(net, id, 4))
			fillRow( lbl4, lblstat4, net, id, 4, WARN, true);
		else
                	fillRow( lbl4, lblstat4, net, id, 4, NORMAL, true);
//                fillRow( lbl5, lblstat5, net, id, 5, stat, true);
//                fillRow( lbl6, lblstat6, net, id, 6, stat, true);
//                fillRow( lbl7, lblstat7, net, id, 7, stat, true);
                fillRow( lbl1, lblstat1, net, id, 1, UNABLE, true);
                fillRow( lbl2, lblstat2, net, id, 2, UNABLE, true);
                fillRow( lbl3, lblstat3, net, id, 3, UNABLE, true);
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


    switch(curMod)
    {
        case ML1T1:
        case DL1T1:
            txt0->setText(Mater::read0address((curNet*BtnNodeNUm + curId)));
            txt1->setText("");
            txt2->setText("");
            txt3->setText("");
            txt4->setText(Mater::read4address((curNet*BtnNodeNUm + curId)));
            txt5->setText("");
            txt6->setText("");
            txt7->setText("");
            txt0->setEnabled(false);
            txt4->setEnabled(false);
            txt1->setVisible(false);
            txt2->setVisible(false);
            txt3->setVisible(false);
            txt5->setVisible(false);
            txt6->setVisible(false);
            txt7->setVisible(false);
            break;
        case ML4T4:
        case ML8:
            txt0->setText(Mater::read0address((curNet*BtnNodeNUm + curId)));
            txt1->setText(Mater::read1address((curNet*BtnNodeNUm + curId)));
            txt2->setText(Mater::read2address((curNet*BtnNodeNUm + curId)));
            txt3->setText(Mater::read3address((curNet*BtnNodeNUm + curId)));
            txt4->setText(Mater::read4address((curNet*BtnNodeNUm + curId)));
            txt5->setText(Mater::read5address((curNet*BtnNodeNUm + curId)));
            txt6->setText(Mater::read6address((curNet*BtnNodeNUm + curId)));
            txt7->setText(Mater::read7address((curNet*BtnNodeNUm + curId)));
            txt0->setEnabled(false);
            txt1->setEnabled(false);
            txt2->setEnabled(false);
            txt3->setEnabled(false);
            txt4->setEnabled(false);
            txt5->setEnabled(false);
            txt6->setEnabled(false);
            txt7->setEnabled(false);
            txt1->setVisible(true);
            txt2->setVisible(true);
            txt3->setVisible(true);
            txt5->setVisible(true);
            txt6->setVisible(true);
            txt7->setVisible(true);
            break;
    }
}
/*====================================
	功能：些下当前数值
====================================*/
void NodeStatus::setCurVal(float* val,int sum)
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
void NodeStatus::setLblValue(QLabel *lbl,float value, int cora)
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
    float val;
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
    Main::flagreset = 1;
    imf_my->updateHandler(QWSInputMethod::FocusOut);
    QWSServer::setCurrentInputMethod(p_imf);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    if((curMod == ML4T4) || (curMod == ML8))
    {
        txt0->setEnabled(false);
        txt1->setEnabled(false);
        txt2->setEnabled(false);
        txt3->setEnabled(false);
        txt4->setEnabled(false);
        txt5->setEnabled(false);
        txt6->setEnabled(false);
        txt7->setEnabled(false);
    }
    else
    {
        txt0->setEnabled(false);
        txt4->setEnabled(false);
    }
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
//    QPixmap pixmap = QPixmap::grabWindow(QApplication::desktop()->winId(),0,0,800,600);
//    pixmap.save("7.png","png");
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
    imf_my->updateHandler(QWSInputMethod::FocusOut);
    QWSServer::setCurrentInputMethod(p_imf);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
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

void NodeStatus::txt0Change()
{    
    txt0->clearFocus();
    txt0->setFocus();
}

void NodeStatus::txt1Change()
{
    txt1->clearFocus();
    txt1->setFocus();
}

void NodeStatus::txt2Change()
{
    txt2->clearFocus();
    txt2->setFocus();
}

void NodeStatus::txt3Change()
{
    txt3->clearFocus();
    txt3->setFocus();
}

void NodeStatus::txt4Change()
{
    txt4->clearFocus();
    txt4->setFocus();
}

void NodeStatus::txt5Change()
{
    txt5->clearFocus();
    txt5->setFocus();
}

void NodeStatus::txt6Change()
{
    txt6->clearFocus();
    txt6->setFocus();
}

void NodeStatus::txt7Change()
{
    txt7->clearFocus();
    txt7->setFocus();
}


void NodeStatus::slot_ok()
{
    if((curMod == ML4T4) || (curMod == ML8))
    {
        Mater::write0address(txt0->text(),(curNet*BtnNodeNUm + curId));
        Mater::write1address(txt1->text(),(curNet*BtnNodeNUm + curId));
        Mater::write2address(txt2->text(),(curNet*BtnNodeNUm + curId));
        Mater::write3address(txt3->text(),(curNet*BtnNodeNUm + curId));
        Mater::write4address(txt4->text(),(curNet*BtnNodeNUm + curId));
        Mater::write5address(txt5->text(),(curNet*BtnNodeNUm + curId));
        Mater::write6address(txt6->text(),(curNet*BtnNodeNUm + curId));
        Mater::write7address(txt7->text(),(curNet*BtnNodeNUm + curId));
        txt0->setEnabled(false);
        txt1->setEnabled(false);
        txt2->setEnabled(false);
        txt3->setEnabled(false);
        txt4->setEnabled(false);
        txt5->setEnabled(false);
        txt6->setEnabled(false);
        txt7->setEnabled(false);
    }
    else
    {
        Mater::write0address(txt0->text(),(curNet*BtnNodeNUm + curId));
        Mater::write4address(txt4->text(),(curNet*BtnNodeNUm + curId));
        txt0->setEnabled(false);
        txt4->setEnabled(false);
    }
    QMessageBox::question (this, tr("提示信息"), tr("设置成功！"),
               tr("确定"), tr("取消"));
}

void NodeStatus::slot_change()
{
    if(Main::flagreset == 1)
    {
        return ;
    }
    QTextCodec::setCodecForCStrings(0);
    QWSServer::setCurrentInputMethod(imf_my);
    imf_my->updateHandler(QWSInputMethod::FocusOut);

    if((curMod == ML4T4) || (curMod == ML8))
    {
        txt0->setEnabled(true);
        txt1->setEnabled(true);
        txt2->setEnabled(true);
        txt3->setEnabled(true);
        txt4->setEnabled(true);
        txt5->setEnabled(true);
        txt6->setEnabled(true);
        txt7->setEnabled(true);
    }
    else
    {
        txt0->setEnabled(true);
        txt4->setEnabled(true);
    }
}
