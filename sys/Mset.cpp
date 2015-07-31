/*=============================
	M型节点设置
=============================*/
#include "Mset.h"
#include <stdio.h>
#include <QWidget>
#include "main/message.h"
#include "warnMsg.h"


int Mset::nodeParm[] = {0};
bool Mset::isReadData = false;

Mset::Mset( IMFrame *im, QWidget *parent): QWidget(parent),Ui_MSetForm()
{
	setupUi(this);
        setWindowFlags(Qt::Dialog);
	setGeometry(45,25,550,430);
	imf = im;
	setAttribute(Qt::WA_DeleteOnClose);
	txtWarn->installEventFilter(this);
	txtDelay->installEventFilter(this);
	cleanData();
	isLorT = 0;
    connect(btnFu, SIGNAL(clicked()),this,SLOT(resetCmd()));//重置
    connect(btnOK, SIGNAL(clicked()),this,SLOT(setParm()));//设置

	connect( cmbNet, SIGNAL(currentIndexChanged(int)),this,SLOT(net_currentIndexChanged(int)));//网络号
	connect( cmbNode, SIGNAL(currentIndexChanged(int)),this,SLOT(node_currentIndexChanged(int)));//节点
	connect( cmbSubNode, SIGNAL(currentIndexChanged(int)),this,SLOT(subNode_currentIndexChanged(int)));//子节点

    //connect( txtWarn, SIGNAL(textChanged(const QString &)), this, SLOT(warn_valueChanged( const QString &)));
    connect( txtWarn, SIGNAL(textEdited(const QString &)), this, SLOT(warn_valueChanged( const QString &)));
    connect( txtDelay, SIGNAL(textChanged( const QString &)), this, SLOT(delChange( const QString &)));

	connect( &timer, SIGNAL(timeout()), this, SLOT(slot_timer()));//显示系统时间

	printf("init MSet ok\n");
}
void Mset::_show()
{
	printf("mset show_ init\n");
	int n = Module::getNet();
	cmbNet -> clear();
	if( n == 0 )
	{
		cmbNet->insertItem(0, "0");
	}
	else if(n == 1)
	{
		cmbNet->insertItem(0, "1");
	}
	else if(n == 2)
	{
		cmbNet->insertItem(0, "0");
        cmbNet->insertItem(1, "1");
	}
	timer.start(1000);
	isReadData = false;
	printf("mset show_ end\n");
}
//========= 读取参数 =========
void Mset::nodeGetParm()
{
	struct pake* p_dat = &Pake::readBuf;
	int i;
	for(i = 0 ; i < 9 ; i++)
	{
		nodeParm[i] = p_dat->data[i];
	}
	isReadData = true;
	//txtDelay->setText( QString::number(nodeParm[8]));
	//txtWarn->setText( QString::number(nodeParm[cmbSubNode->currentIndex()]));
	Message::_show(tr("设备参数读取成功!"));
}

void Mset::slot_timer()
{
	//timer.stop();
	if(isReadData == true)
	{
		txtDelay->setText(QString::number(nodeParm[8]));
        printf("cmbSubNode->currentText().toInt()===%d\n",cmbSubNode->currentText().toInt());
		subNode_currentIndexChanged(cmbSubNode->currentText().toInt());
		isReadData =  false;
	}
}
//=========== 网络改变 ==========
void Mset::net_currentIndexChanged(int index)
{
	printf("net init\n");
	int ind = 0;
	if(cmbNet->count() < 1) return ;
	int net = cmbNet->currentText().toInt();
	cmbNode->clear();
    for(int  node = 1; node < BtnNodeNUm + 1; node ++ )
	{
		sn = Module::getNodeSN( net, node );
		if( sn != NO_SN && sn != MC) cmbNode->insertItem( ind ++, QString::number(node));
	}
	printf("net end\n");
}
//=========== 节点改变 ==========
void Mset::node_currentIndexChanged (int index)
{
	printf("node init\n");
	if(cmbNode->count() > 0 && cmbNet->count() > 0)
	{
		sn = Module::getNodeSN( cmbNet->currentText().toInt(), cmbNode->currentText().toInt());
		lblSN->setText(tr(Module::moTyp[sn].name));        
		switch(sn)
		{
			case ML1T1:
            case DL1T1:
                insertNewSubItem(sn,8);
                break;
			case ML4T4:
			case ML8: 
				insertSubItem(8);
				break;
		}
	}
	printf("node end\n");
}
//子节点改变
void Mset::subNode_currentIndexChanged(int index)
{
    printf("subNode init   index==%d\n",index);
	int i = 0;//默认漏电报警
	if(index > 7) return;
    if ((ML4T4 == sn))// || (ML1T1 == sn) || (DL1T1 == sn))
    {
		if(index > 3)
        {
			i =1;
            txtWarn->setText( QString::number(nodeParm[index]));//10
		}
		else
		{
			i=0;
            txtWarn->setText( QString::number(nodeParm[index]));
		}
	}
    if((ML1T1 == sn) || (DL1T1 == sn))
    {
        if(index > 0 )
        {
            i =1;
            txtWarn->setText( QString::number(nodeParm[4]));
        }
        else
        {
            i=0;
            txtWarn->setText( QString::number(nodeParm[index]));
        }
    }
    if((MC == sn)||(ML8 == sn))
    {
		i=0;
		txtWarn->setText( QString::number(nodeParm[index]));
	}

	if(i == 0)
    {
        lbl_wran->setText(tr("漏电报警(mA)"));
		isLorT = 1;
	}
    else if(i == 1){
        lbl_wran->setText(tr("温度报警(℃)"));
		isLorT = 2;
	}	
	printf("subNode end\n");
}
//=========== 写下报警数值 ====================
void Mset::warn_valueChanged ( const QString & text)
{
	if(text == NULL || text == "") return;
	if(cmbSubNode->count() < 1) return;
    //QString s="";
	if(isLorT == 1)
	{
		
        if((text.toInt() > 1000))
		{
			txtWarn->setText("1000");
			return;
		}
//        if(text.toInt() < 80)
//        {
//            //usleep(1000000);// 1s
//            txtWarn->setText("80");
//            return;
//        }
//        if((text.toInt() < 80))
//        {
//            txtWarn->setText(text.left(text.length()-1));
//            return;
//        }
	}
    else if( isLorT == 2)//当温度为45－140时版本
	{
        if((text.toInt() > 140))
		{
            txtWarn->setText("140");
			return;
		}

//        if((text.toInt() < 55))
//        {
//            //usleep(2000000); //2s
//            txtWarn->setText("55");
//            return;
//        }
	}
/*	else if(isLorT == 2)
	{
		if((text.toInt() != 55))
		{
			txtWarn->setText("55");
			return;
		}
	}*/
/*	int currentSubNode = cmbSubNode->currentText().toInt();
	if((sn==ML4T4))
	{
		if(currentSubNode > 3)
		{
	        nodeParm[currentSubNode] = text.toInt()*10;
		}
		else
		{
	        nodeParm[currentSubNode] = text.toInt();
		}
	}
	if((sn==MC)||(sn==ML8))
	{
	    nodeParm[currentSubNode] = text.toInt();
	}*/
}
//============= 设置 =============
void Mset::setParm()
{
	int net;
	int id;
	if(isLorT==1)
	{
        if(txtWarn->text().toInt()>1000)
		{
			txtWarn->setText("1000");
		}
        else if(txtWarn->text().toInt()<80)
        {
            txtWarn->setText("80");
        }
		else
		{
			txtWarn->setText(txtWarn->text());
		}
	}
	else if(isLorT==2)
	{
        if(txtWarn->text().toInt()>140)
		{
            txtWarn->setText("140");
		}
        else if(txtWarn->text().toInt()<45)
        {
            txtWarn->setText("45");
		}
		else
		{
			txtWarn->setText(txtWarn->text());
		}
	/*	if(txtWarn->text().toInt()!=55)
		{
			txtWarn->setText("55");
		}*/
	}

	int currentSubNode = cmbSubNode->currentText().toInt();
    printf("currentSubNode==%d\n",currentSubNode);
    if ((sn == ML4T4) || (sn == ML1T1) || (sn == DL1T1))
	{
        if(currentSubNode > 3)
		{
            nodeParm[currentSubNode] = txtWarn->text().toInt();//*10;
		}
		else
		{
	        nodeParm[currentSubNode] = txtWarn->text().toInt();
		}
    }
	if((sn==MC)||(sn==ML8))
	{
	    nodeParm[currentSubNode] = txtWarn->text().toInt();
	}

	if( cmbNet->count() > 0 && cmbNode->count() > 0)
	{
		net = cmbNet->currentText().toInt();
		id = cmbNode->currentText().toInt();
		Pake::send( net, id, SET_WAR_VAL, nodeParm, 9);
		WarnMsg::insertNodeSet( net, id);
	}
}
//=========== 重置 ===============
void Mset::resetCmd()
{
	if( cmbNet->count() > 0 && cmbNode->count() > 0)
	{
		int net = cmbNet->currentText().toInt();
		int id = cmbNode->currentText().toInt();
		sn = Module::getNodeSN( net, id);
		lblSN->setText( tr(Module::moTyp[sn].name) );
		//漏电温度
		Pake::send( net, id, QUE_WAR_VAL, NULL, 0);
	}
}
void Mset::insertSubItem(int count)
{
	cmbSubNode->clear();
	for(int i = 0; i < count ; i++)
	{
		cmbSubNode->insertItem(i,QString::number(i));
	}
}
void Mset::insertNewSubItem(int flag, int count)
{
    cmbSubNode->clear();
    if(flag == DL1T1 || flag == ML1T1)
    {
        cmbSubNode->insertItem(0,QString::number(0));
        cmbSubNode->insertItem(4,QString::number(4));
    }
    else
    {
        for(int i = 0; i < count ; i++)
        {
            cmbSubNode->insertItem(i,QString::number(i));
        }
    }
}
void Mset::cleanData()
{
	for(int i = 0 ; i < 16 ; i ++ )
	{
		nodeParm[i] = 0;//报警数据
	}
}
bool Mset::eventFilter(QObject *obj, QEvent *event)
{
	QLineEdit *txt = (QLineEdit*)obj;
	QWidget* wid=(QWidget*)obj;
	QRect qr,qr1;
	if(event->type() == QEvent::MouseButtonPress){
		qr = wid->geometry();
		int w=qr.width();
		int h=qr.height();
		wid = wid->parentWidget();
		while(wid != 0 ){
			qr1 = wid->geometry();
			qr.setX(qr.x()+qr1.x());
			qr.setY(qr.y()+qr1.y());
			wid = wid->parentWidget();
		}
		qr.setRect( qr.x(), qr.y(), w, h);
		imf->my_show(&qr,txt);
	}
	if(event->type() == QEvent::FocusOut){
		imf->my_hide();
	}
	return QWidget::eventFilter(obj, event);
}
/*============================*/
// 延时文本改变
void Mset::delChange(const QString &str)
{
	printf("del c\n");
	if(str == "" || str == "") return;
	printf("del c1\n");
    if((str.toInt() > 30)||(str.toInt()==0))
	{
		printf("del c2\n");
		txtDelay->setText(str.left(str.length()-1));
	}
	printf("del c3\n");
	nodeParm[8] = txtDelay->text().toInt();
	printf("del c4\n");
}
Mset::~Mset()
{
	printf("exit BridewellSet\n");
}
