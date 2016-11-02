#include "charging_monitoring.h"
#include "ui_charging_monitoring.h"
#include "equipment_information.h"
#include "bat_information.h"
#include "billing_info.h"
#include "charging_end.h"
#include "main.h"
#include "tcu.h"
#include <QLabel>
#include <stdio.h>
//#include <sys/time.h>

#define  EMTER
//#undef  EMTER

Charging_monitoring::Charging_monitoring(QWidget *parent) : QWidget(parent), ui(new Ui::Charging_monitoring)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存

    ui->soc_set->setVisible(false);
    ui->full_charge->setVisible(false);
    ui->full_charge_but->setVisible(false);
    ui->charge_7but->setVisible(false);
    ui->charge_6but->setVisible(false);
    ui->charge_5but->setVisible(false);
    ui->charge_4but->setVisible(false);
    ui->charge_3but->setVisible(false);
    ui->charge_2but->setVisible(false);
    ui->charge_1but->setVisible(false);

    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->emter_current->setVisible(false);
    ui->emter_power->setVisible(false);
    ui->emter_vol->setVisible(false);

    ui->charge_vol->setText(task->emter_info.emter_vol);
    ui->charge_current->setText(task->emter_info.emter_current);
    ui->charge_power->setText(task->emter_info.emter_power);
    charge_inf();
    slot_chargingtimer();
    initBtnNode();

    //connect(ui->soc_set,SIGNAL(clicked()),this,SLOT(set_soc()));//查询
    //connect(ui->change_moni_but,SIGNAL(clicked()),this,SLOT(change_moni());
    connect(ui->change_equ_but,SIGNAL(clicked()),this,SLOT(change_equinf()));//
    connect(ui->change_batinf_but,SIGNAL(clicked()),this,SLOT(change_batinf()));//
    //connect(ui->change_carinf_but,SIGNAL(clicked()),this,SLOT(change_carinf()));//
    connect(ui->change_billinf_but,SIGNAL(clicked()),this,SLOT(change_billinf()));//
    //connect(ui->change_end_but,SIGNAL(clicked()),this,SLOT(change_end()));//
    connect(ui->soc_stop,SIGNAL(clicked()),this,SLOT(Charging_monitoring_hide()));
    //connect(ui->soc_stop,SIGNAL(clicked()),this,SLOT(change_main()));

    connect(&tst_timer,SIGNAL(timeout()),this,SLOT(slot_timer()));//停止充电
    tst_timer.start(100);

    flag = 1;
    connect(&tmp_timer,SIGNAL(timeout()),this,SLOT(slot_tmptimer()));//充电信息
    if(tmp_timer.isActive()){
        tmp_timer.stop();
    }
    tmp_timer.start(500);

    tmp = 0;
    connect(&charging_timer,SIGNAL(timeout()),this,SLOT(slot_chargingtimer()));//充电计时
    if(charging_timer.isActive()){
        charging_timer.stop();
    }
    charging_timer.start(1000);

    Message::static_msg = new Message();


#ifdef EMTER
    p_emter = new EmterWindow();
    p_emter->ComInit();
    //p_emter->SendData("02010100");
    //p_emter->StartInit();
    //p_emter->sendEmterMsg();
#endif

#if 0
    if(bat_soc_int<100){//90
        ui->full_charge_but->setVisible(false);
        ui->charge_7but->setVisible(true);
    }else if(bat_soc_int<90 && bat_soc_int>80){//80
        ui->charge_7but->setVisible(false);
        ui->charge_6but->setVisible(true);
    }else if(bat_soc_int<80 && bat_soc_int>60){//60
        ui->charge_6but->setVisible(false);
        ui->charge_5but->setVisible(true);
    }else if(bat_soc_int<60 && bat_soc_int>30){//40
        ui->charge_5but->setVisible(false);
        ui->charge_4but->setVisible(true);
    }else if(bat_soc_int<30 && bat_soc_int>20){//30
        ui->charge_4but->setVisible(false);
        ui->charge_3but->setVisible(true);
    }else if(bat_soc_int<20 && bat_soc_int>10){//20
        ui->charge_3but->setVisible(false);
        ui->charge_2but->setVisible(true);
    }else if(bat_soc_int<20){//10
        ui->charge_2but->setVisible(false);
        ui->charge_1but->setVisible(true);
    }
#endif
    printf("successs!!!");
}

void Charging_monitoring::slot_timer()
{



    if(task->tcu_err_stage == (TCU_ERR_STAGE_TIMEOUT | TCU_ERR_STAGE_START))
    {
        myerr_sigals.SetValue(task->tcu_err_stage);
        ui->label_inf->setText("启动充电超时");
        //QMessageBox::critical(NULL, "Error", "启动充电超时");
        //tst_timer.stop();//注释掉可重试进行下一步，否则定时器停止，无法跳转界面到
    }
    if(task->tcu_err_stage == (TCU_ERR_STAGE_TIMEOUT | TCU_ERR_STAGE_STOP))
    {
        myerr_sigals.SetValue(task->tcu_err_stage);
        ui->label_inf->setText("停止充电超时");
        //QMessageBox::critical(NULL, "Error", "停止充电超时");
        //tst_timer.stop();
    }

    if(task->tcu_stage == TCU_STAGE_START)
    {
        ui->label_inf->setText("启动充电");
    }

    if(task->tcu_stage == TCU_STAGE_STARTING)
    {
        ui->label_inf->setText("启动充电...");
        my_sigals.SetValue(TCU_STAGE_STARTING);
    }

    if(task->tcu_stage == TCU_STAGE_STATUS)
    {
        ui->label_inf->setText("启动充电完成");
        my_sigals.SetValue(TCU_STAGE_STATUS);
    }

    if(task->tcu_stage == TCU_STAGE_CHARGING)
    {
        ui->label_inf->setText("充电中...");
    }

    if(task->tcu_stage == TCU_STAGE_STOP || task->tcu_err_stage == TCU_ERR_STAGE_STOP)
    {
            //QMessageBox::about(NULL, "Stop", "停止充电");
            ui->label_inf->setText("停止充电");
            my_sigals.SetValue(TCU_STAGE_STOP);
            tst_timer.stop();
    }

    if(task->tcu_stage == TCU_STAGE_STOP_END )
    {
            //QMessageBox::about(NULL, "Stop", "停止充电");
            ui->label_inf->setText("停止充电");
            my_sigals.SetValue(TCU_STAGE_STOP_END);
            tst_timer.stop();
    }

    if(task->tcu_err_stage == TCU_ERR_STAGE_START)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_START);
        ui->label_inf->setText("启动充电失败");
        //QMessageBox::critical(NULL, "Error", "启动充电失败");
        tst_timer.stop();
    }

    if(task->tcu_err_stage == TCU_ERR_STAGE_STARTING)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_STARTING);
        ui->label_inf->setText("启动充电失败");
        //QMessageBox::critical(NULL, "Error", "启动充电失败");
        tst_timer.stop();
    }

    if(task->tcu_err_stage == TCU_ERR_STAGE_STOP_STATUS)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_STOP_STATUS);
        ui->label_inf->setText("停止充电失败");
        //QMessageBox::critical(NULL, "Error", "停止充电失败");
        tst_timer.stop();
    }

}


void Charging_monitoring::set_soc()
{printf("set_soc\n");
       ui->bat_soc->setText(ui->bat_soc->text());

       bat_soc_int =  ui->bat_soc->text().toInt();
       printf("bat_soc_txt==%d", bat_soc_int);

#if 0
       if(bat_soc_int==100 ){//90
           ui->full_charge_but->setVisible(true);
           ui->charge_7but->setVisible(false);
       }else if(bat_soc_int<100 && bat_soc_int>=90){//90
           ui->full_charge_but->setVisible(false);
           ui->charge_7but->setVisible(true);
       }else if(bat_soc_int<90 && bat_soc_int>=80){//80
           ui->charge_7but->setVisible(false);
           ui->charge_6but->setVisible(true);
       }else if(bat_soc_int<80 && bat_soc_int>=60){//60
           ui->charge_6but->setVisible(false);
           ui->charge_5but->setVisible(true);
       }else if(bat_soc_int<60 && bat_soc_int>=30){//40
           ui->charge_5but->setVisible(false);
           ui->charge_4but->setVisible(true);
       }else if(bat_soc_int<30 && bat_soc_int>=20){//30
           ui->charge_4but->setVisible(false);
           ui->charge_3but->setVisible(true);
       }else if(bat_soc_int<20 && bat_soc_int>=10){//20
           ui->charge_3but->setVisible(false);
           ui->charge_2but->setVisible(true);
       }else if(bat_soc_int<10){//10
           ui->charge_2but->setVisible(false);
           ui->charge_1but->setVisible(true);
       }
//#else
       switch (bat_soc_int/10) {
       case 10://100
           ui->full_charge_but->setVisible(true);
           ui->charge_7but->setVisible(false);
           ui->charge_1but->setVisible(false);
           break;
       case 9://90
           ui->full_charge_but->setVisible(false);
           ui->charge_7but->setVisible(true);
           ui->charge_6but->setVisible(false);
           break;
       case 8://80
           ui->charge_7but->setVisible(false);
           ui->charge_6but->setVisible(true);
           ui->charge_5but->setVisible(false);
           break;
       case 7:
       case 6://60
           ui->charge_6but->setVisible(false);
           ui->charge_5but->setVisible(true);
           ui->charge_4but->setVisible(false);
           break;
       case 5:
       case 4://40
           ui->charge_5but->setVisible(false);
           ui->charge_4but->setVisible(true);
           ui->charge_3but->setVisible(false);
           break;
       case 3://30
           ui->charge_4but->setVisible(false);
           ui->charge_3but->setVisible(true);
           ui->charge_2but->setVisible(false);
           break;
       case 2://20
           ui->charge_3but->setVisible(false);
           ui->charge_2but->setVisible(true);
           ui->charge_1but->setVisible(false);
           break;
       case 1://10
       case 0:
           ui->charge_2but->setVisible(false);
           ui->charge_1but->setVisible(true);
           break;
       default:
           break;
       }
#endif
       showBtn(bat_soc_int/10);
       //show();
}

void Charging_monitoring::showBtn(int flag)
{printf("showBtn\n");
  //int tmp = 0;
  //for(tmp=0;tmp<flag;tmp++)
  {
        setBtnFlag(tmp,btn_node[0].btn);
        tmp++;
        if(tmp == (flag + 1)){
            tmp = 0;
        }
  }
}

void Charging_monitoring::setBtnFlag(int flag,QWidget& qw)
{printf("setBtnFlag\n");
    switch(flag){
    case 0:
    case 1:
        qw.setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new1dianci.png);"));
        break;
    case 2:
        qw.setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new2dianci.png);"));
        break;
    case 3:
        qw.setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new3dianci.png);"));
        break;
    case 4:
    case 5:
        qw.setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new4dianci.png);"));
        break;
    case 6:
    case 7:
        qw.setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new5dianci.png);"));
        break;
    case 8:
        qw.setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new6dianci.png);"));
        break;
    case 9:
        qw.setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new7dianci.png);"));
        break;
    case 10:
        qw.setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new8dianci.png);"));
        break;
    default:
        qw.setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new8dianci.png);"));
        break;
    }
}

void Charging_monitoring::initBtnNode()
{
    printf("initBtnNode\n");
    int i ;
    int x = 400, y = 130, w = 130, h = 60;//52
    int xw = 44, xh = 46;//52
    btn_node = new BtnNode[BtnNodeNUm];

    for( i = 0; i < BtnNodeNUm ; i++)
    {
        btn_node[i].btn.setParent(ui->charge_monitoring);
        btn_node[i].btn.setFocusPolicy(Qt::NoFocus);
        btn_node[i].btn.setFlat(true);
        //btn_node[i].btn.setText(QString::number(i+1));
        btn_node[i].btn.setGeometry(x,y,w,h);
        setBtnFlag(i,btn_node[i].btn);
        btn_node[i].flag = i;
        btn_node[i].btn.setVisible(true);
        x += xw;
    }
}

void Charging_monitoring::charge_inf()
{
    char ch[50];

//    sprintf(ch,"%5.1f",(float)(task->ctf_info.spn8704_out_vol[1] + task->ctf_info.spn8704_out_vol[0]*256)/10);
//    ui->charge_vol->setText(ch);

//    sprintf(ch,"%4.2f",(float)(task->ctf_info.spn8704_out_cur[1] + task->ctf_info.spn8704_out_cur[0]*256)/100);
//    ui->charge_current->setText(ch);

    //sprintf(ch,"%d",(task->ctf_info.spn8704_out_vol * task->ctf_info.spn8704_out_cur)/1000);
   // ui->charge_power->setText(ch);

    int cc_status;
    cc_status = task->crf_info.spn8448_status & 0x0F;

    if(cc_status == CC_WAIT)
    {
        sprintf(ch,"待机");
    }else if(cc_status == CC_WORK)
    {
            sprintf(ch,"工作");
    }else if(cc_status == CC_FULL)
    {
            sprintf(ch,"充满");
    }else if(cc_status == CC_WARN)
    {
            sprintf(ch,"告警");
    }else if(cc_status == CC_ERROR)
    {
            sprintf(ch,"故障");
    }
    ui->charge_status->setText(ch);

//    sprintf(ch,"%s",task->thb_info.spn12544_ele);
//    ui->charge_power->setText(ch);printf("charge_power==%s\n",ch);

//    sprintf(ch,"%s",task->ctf_info.spn8704_out_cur);
//    ui->charge_current->setText(ch);printf("charge_current==%s\n",ch);

//    sprintf(ch,"%s",task->ctf_info.spn8704_out_vol);
//    ui->charge_vol->setText(ch);printf("charge_vol==%s\n",ch);

//    sprintf(ch,"%s",task->thb_info.spn12544_time);
    //sprintf(ch,"%s",task->thb_info.spn12544_time);
    //ui->charge_time->setText(ch);printf("charge_time==%s\n",ch);
}

void Charging_monitoring::set_data()
{
//    ui->charge_status();
//    ui->bat_status();
//    ui->charge_power();
//    ui->charge_current();
//    ui->charge_vol();
//    ui->charge_time();
    charge_inf();
}

void Charging_monitoring::slot_tmptimer()
{    
    set_soc();
    set_data();
#ifdef EMTER
    if(flag == 1){
        p_emter->SendData("02010100");//A项电压 //0201FF00
//        p_emter->sendEmterMsg();
//        p_emter->readEmterCom();
//        p_emter->printf_data(flag);
        flag = 0;
    }else if(flag == 0){
        p_emter->SendData("02020100");//A项电流
//        p_emter->sendEmterMsg();
//        p_emter->readEmterCom();
//        p_emter->printf_data(flag);
        flag = 2;
    }else if(flag == 2){
        p_emter->SendData("00000000");//02030100Ａ相瞬时功率
//        p_emter->sendEmterMsg();
//        p_emter->readEmterCom();
//        p_emter->printf_data(flag);
        flag = 1;
    }

    p_emter->sendEmterMsg();
    //p_emter->readEmterCom();

//    ui->emter_vol->setText(task->emter_info.emter_vol);
//    ui->emter_current->setText(task->emter_info.emter_current);
//    ui->emter_power->setText(task->emter_info.emter_power);

    ui->charge_vol->setText(task->emter_info.emter_vol);
    ui->charge_current->setText(task->emter_info.emter_current);
    ui->charge_power->setText(task->emter_info.emter_power);
#endif
}

int   Charging_monitoring::mytime_substract(struct timeval *result, struct timeval *begin,struct timeval *end)
{

    if(begin->tv_sec > end->tv_sec)    return -1;
    if((begin->tv_sec == end->tv_sec) && (begin->tv_usec > end->tv_usec))    return -2;

    result->tv_sec    = (end->tv_sec - begin->tv_sec);
    result->tv_usec    = (end->tv_usec - begin->tv_usec);

    if(result->tv_usec < 0)
    {
        result->tv_sec--;
        result->tv_usec += 1000000;
    }
    return 0;
}


void Charging_monitoring::slot_chargingtimer()
{
    char ch[50];

    memset(&task->charging_time.stop,0,sizeof(struct timeval));
    memset(&task->charging_time.tcu_charging_time,0,sizeof(struct timeval));
    gettimeofday(&task->charging_time.stop,NULL);

    mytime_substract(&task->charging_time.tcu_charging_time,&task->charging_time.start,&task->charging_time.stop);

    printf("Total time : %d min %d s,%d us\n",(int)task->charging_time.tcu_charging_time.tv_sec/60,(int)task->charging_time.tcu_charging_time.tv_sec,(int)task->charging_time.tcu_charging_time.tv_usec);
    sprintf(ch,"%02d:%02d",(int)task->charging_time.tcu_charging_time.tv_sec/60,(int)task->charging_time.tcu_charging_time.tv_sec%60);
    sprintf(task->thb_info.spn12544_time,"%d",(int)task->charging_time.tcu_charging_time.tv_sec/60);

    ui->charge_time->setText(ch);

    //set_soc();
}


void Charging_monitoring::change_moni()
{
    Charging_monitoring *w_change_moni = new Charging_monitoring;
    w_change_moni->show();
}

void Charging_monitoring::change_equinf()
{
    Equipment_information *w_equipment_information = new Equipment_information;
    w_equipment_information->show();
}

void Charging_monitoring::change_batinf()
{
    bat_information *w_bat_information = new bat_information;
    w_bat_information->show();
}

void Charging_monitoring::change_billinf()
{
    Billing_info *w_billing_information = new Billing_info;
    w_billing_information->show();
}

void Charging_monitoring::change_end()
{    
    charging_end *w_charging_end = new charging_end;
    w_charging_end->show();
}

void Charging_monitoring::Charging_monitoring_hide()
{
    //hide();
    my_sigals.SetValue(TCU_STAGE_STOP);
}

void Charging_monitoring::change_main()// error
{
    //Main *w_change_main = new Main();
    //w_change_main->show();
}

Charging_monitoring::~Charging_monitoring()
{
    delete ui;
}
