#include "double_gun.h"
#include "ui_double_gun.h"
#include "tcu.h"
#include "stdio.h"

double_gun::double_gun(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::double_gun)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/img/images/Main.png")));
    this->setPalette(palette);


#if 1
    QMovie*movie=new QMovie(":/img/images/charginggif.gif");
    ui->charging_gif->setMovie(movie);
    ui->charging_gif_2->setMovie(movie);
    movie->start();
#endif
    //ui->groupBox_2->setVisible(false);
    if(task->gun_num == GUN_NUM0 || task->gun_sn == GUN_NUM1 ){//一枪连接(单枪或双枪单充)
        //ui->groupBox_2->setVisible(false);

        ui->frame_moni->setVisible(true);
        ui->frame_equ->setVisible(false);
        ui->frame_bill->setVisible(false);
    }else{//双枪连接
        ui->groupBox_2->setVisible(true);
        ui->frame_moni->setVisible(true);
        ui->frame_equ->setVisible(false);
        ui->frame_bill->setVisible(false);

        ui->frame_moni_2->setVisible(true);
        ui->frame_equ_2->setVisible(false);
        ui->frame_bill_2->setVisible(false);
    }

    ui->frame_moni->setVisible(true);
    ui->frame_equ->setVisible(false);
    ui->frame_bill->setVisible(false);

    ui->frame_moni_2->setVisible(true);
    ui->frame_equ_2->setVisible(false);
    ui->frame_bill_2->setVisible(false);

    slot_tmptimer();


    memset(&task->charging_time[0].start,0,sizeof(struct timeval));
    gettimeofday(&task->charging_time[0].start,NULL);
    memset(&task->charging_time[1].start,0,sizeof(struct timeval));
    gettimeofday(&task->charging_time[1].start,NULL);


    if(tmp_timer.isActive()){
        tmp_timer.stop();//防止重新创建
    }else{
        connect(&tmp_timer,SIGNAL(timeout()),this,SLOT(slot_tmptimer()));//充电信息
        tmp_timer.start(500);
    }

     if(charging_timer.isActive()){
        charging_timer.stop();
    }else{
        connect(&charging_timer,SIGNAL(timeout()),this,SLOT(slot_chargingtimer()));//充电计时
        charging_timer.start(1000);
     }

     if(charging_timer_2.isActive()){
        charging_timer_2.stop();
    }else{
        connect(&charging_timer_2,SIGNAL(timeout()),this,SLOT(slot_chargingtimer_2()));//充电计时
        charging_timer_2.start(1000);
     }

     if(tst_timer.isActive()){
         tst_timer.stop();//防止重新创建
     }else{
        connect(&tst_timer,SIGNAL(timeout()),this,SLOT(slot_statustimer()));//充电状态
        tst_timer.start(100);
    }

}


void double_gun::slot_tmptimer()
{
    c_moni_msg();
    c_equ_msg();
    c_bill_msg();
    c_moni_msg_2();
    c_equ_msg_2();
    c_bill_msg_2();
}

int   double_gun::mytime_substract(struct timeval *result, struct timeval *begin,struct timeval *end)
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


void double_gun::slot_chargingtimer()
{
    char ch[50];

    memset(&task->charging_time[0].stop,0,sizeof(struct timeval));
    memset(&task->charging_time[0].tcu_charging_time,0,sizeof(struct timeval));
    gettimeofday(&task->charging_time[0].stop,NULL);
    mytime_substract(&task->charging_time[0].tcu_charging_time,&task->charging_time[0].start,&task->charging_time[0].stop);
    printf("Total time : %d min %d s,%d us\n",(int)task->charging_time[0].tcu_charging_time.tv_sec/60,(int)task->charging_time[0].tcu_charging_time.tv_sec,(int)task->charging_time[0].tcu_charging_time.tv_usec);
    sprintf(ch,"%02d:%02d",(int)task->charging_time[0].tcu_charging_time.tv_sec/60,(int)task->charging_time[0].tcu_charging_time.tv_sec%60);
    ui->c_time_1->setText(ch);
}

void double_gun::slot_chargingtimer_2()
{
    char ch[50];
    memset(&task->charging_time[1].stop,0,sizeof(struct timeval));
    memset(&task->charging_time[1].tcu_charging_time,0,sizeof(struct timeval));
    gettimeofday(&task->charging_time[1].stop,NULL);
    mytime_substract(&task->charging_time[1].tcu_charging_time,&task->charging_time[1].start,&task->charging_time[1].stop);
    printf("Total time : %d min %d s,%d us\n",(int)task->charging_time[1].tcu_charging_time.tv_sec/60,(int)task->charging_time[1].tcu_charging_time.tv_sec,(int)task->charging_time[1].tcu_charging_time.tv_usec);
    sprintf(ch,"%02d:%02d",(int)task->charging_time[1].tcu_charging_time.tv_sec/60,(int)task->charging_time[1].tcu_charging_time.tv_sec%60);
    ui->c_time_2->setText(ch);
}


void double_gun::slot_statustimer()
{
    QString gun,msg;
    gun += task->gun_sn;
    gun+= "# 枪 ";


    if(task->tcu_err_stage == (TCU_ERR_STAGE_TIMEOUT | TCU_ERR_STAGE_START))
    {
        myerr_sigals.SetValue(task->tcu_err_stage);
        msg = gun + "启动充电超时";
        ui->label_inf->setText(msg);
        //ui->label_inf->setText("启动充电超时");
        //QMessageBox::critical(NULL, "Error", "启动充电超时");        
    }
    if(task->tcu_err_stage == (TCU_ERR_STAGE_TIMEOUT | TCU_ERR_STAGE_STOP))
    {
        myerr_sigals.SetValue(task->tcu_err_stage);
        msg = gun + "停止充电超时";
        ui->label_inf->setText(msg);
        //ui->label_inf->setText("停止充电超时");
        //QMessageBox::critical(NULL, "Error", "停止充电超时");
    }

    if(task->tcu_stage == TCU_STAGE_START)
    {
        msg = gun + "启动充电";
        ui->label_inf->setText(msg);
        //ui->label_inf->setText("启动充电");
    }

    if(task->tcu_stage == TCU_STAGE_STARTING)
    {
        msg = gun + "启动充电...";
        ui->label_inf->setText(msg);
        //ui->label_inf->setText("启动充电...");
        my_sigals.SetValue(TCU_STAGE_STARTING);
    }

    if(task->tcu_stage == TCU_STAGE_STATUS)
    {
        msg = gun + "启动充电完成";
        ui->label_inf->setText(msg);
        //ui->label_inf->setText("启动充电完成");
        my_sigals.SetValue(TCU_STAGE_STATUS);
    }

    if(task->tcu_stage == TCU_STAGE_CHARGING)
    {
        msg = gun + "充电中...";
        ui->label_inf->setText(msg);
        //ui->label_inf->setText("充电中...");
    }

    if(task->tcu_stage == TCU_STAGE_STOP || task->tcu_err_stage == TCU_ERR_STAGE_STOP)
    {
            //QMessageBox::about(NULL, "Stop", "停止充电");
        msg = gun + "停止充电";
        ui->label_inf->setText(msg);
        //ui->label_inf->setText("停止充电");
        my_sigals.SetValue(TCU_STAGE_STOP);
        //tst_timer.stop();
    }

    if(task->tcu_stage == TCU_STAGE_STOP_END )
    {
            //QMessageBox::about(NULL, "Stop", "停止充电");
        msg = gun + "停止充电";
        ui->label_inf->setText(msg);
        //ui->label_inf->setText("停止充电");
        my_sigals.SetValue(TCU_STAGE_STOP_END);
        //tst_timer.stop();
    }

    if(task->tcu_err_stage == TCU_ERR_STAGE_START)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_START);
        msg = gun + "启动充电失败";
        ui->label_inf->setText(msg);
        //ui->label_inf->setText("启动充电失败");
        //QMessageBox::critical(NULL, "Error", "启动充电失败");
        //tst_timer.stop();
    }

    if(task->tcu_err_stage == TCU_ERR_STAGE_STARTING)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_STARTING);
        msg = gun + "启动充电失败";
        ui->label_inf->setText(msg);
        //ui->label_inf->setText("启动充电失败");
        //QMessageBox::critical(NULL, "Error", "启动充电失败");
        //tst_timer.stop();
    }

    if(task->tcu_err_stage == TCU_ERR_STAGE_STOP_STATUS)
    {
        myerr_sigals.SetValue(TCU_ERR_STAGE_STOP_STATUS);
        msg = gun + "停止充电失败";
        ui->label_inf->setText(msg);
        //ui->label_inf->setText("停止充电失败");
        //QMessageBox::critical(NULL, "Error", "停止充电失败");
        //tst_timer.stop();
    }

}

double_gun::~double_gun()
{
    delete ui;
}

void double_gun::on_back_but_clicked()
{
    hide();
    tst_timer.stop();
    tmp_timer.stop();
    charging_timer.stop();
    charging_timer_2.stop();
}

void double_gun::on_c_moni_but_pressed()
{
    ui->frame_moni->setVisible(true);
    ui->frame_equ->setVisible(false);
    ui->frame_bill->setVisible(false);
    ui->c_equ_but->setChecked(false);
    ui->c_billinf_but->setChecked(false);
}

void double_gun::on_c_equ_but_pressed()
{
    ui->frame_moni->setVisible(false);
    ui->frame_equ->setVisible(true);
    ui->frame_bill->setVisible(false);
    ui->c_moni_but->setChecked(false);
    ui->c_billinf_but->setChecked(false);
}

void double_gun::on_c_billinf_but_pressed()
{
    ui->frame_moni->setVisible(false);
    ui->frame_equ->setVisible(false);
    ui->frame_bill->setVisible(true);
    ui->c_moni_but->setChecked(false);
    ui->c_equ_but->setChecked(false);
}

void double_gun::on_soc_stop_1_pressed()
{
    my_sigals.oldvalue = 255;
    task->gun_sn = GUN_SN1;
    my_sigals.SetValue(TCU_STAGE_STOP);
    charging_timer.stop();
}

void double_gun::on_c_moni_but_2_pressed()
{
    ui->frame_moni_2->setVisible(true);
    ui->frame_equ_2->setVisible(false);
    ui->frame_bill_2->setVisible(false);
    ui->c_equ_but_2->setChecked(false);
    ui->c_billinf_but_2->setChecked(false);
}

void double_gun::on_c_equ_but_2_pressed()
{
    ui->frame_moni_2->setVisible(false);
    ui->frame_equ_2->setVisible(true);
    ui->frame_bill_2->setVisible(false);
    ui->c_moni_but_2->setChecked(false);
    ui->c_billinf_but_2->setChecked(false);
}

void double_gun::on_c_billinf_but_2_pressed()
{
    ui->frame_moni_2->setVisible(false);
    ui->frame_equ_2->setVisible(false);
    ui->frame_bill_2->setVisible(true);
    ui->c_moni_but_2->setChecked(false);
    ui->c_equ_but_2->setChecked(false);
}

void double_gun::on_soc_stop_2_pressed()
{
    my_sigals.oldvalue = 255;
    task->gun_sn = GUN_SN2;
    my_sigals.SetValue(TCU_STAGE_STOP);
    charging_timer_2.stop();
}


void  double_gun::c_moni_msg()
{
    char ch[50];

    int cc_status;
    cc_status = task->crf_DC_info.spn8448_status_1 & 0x0F;

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
    ui->c_status_1->setText(ch);

    sprintf(ch,"%d",task->ctf_DC_info.spn8704_soc);
    ui->bat_soc_1->setText(ch);

    if(task->gun_sn == GUN_SN0){
        ui->c_vol_1->setText(task->emter_info[EMTER_NUM0].emter_vol);
        ui->c_current_1->setText(task->emter_info[EMTER_NUM0].emter_current);
        ui->c_power_1->setText(task->emter_info[EMTER_NUM0].emter_power);
    }else if(task->gun_sn == GUN_SN1){
        ui->c_vol_1->setText(task->emter_info[EMTER_NUM1].emter_vol);
        ui->c_current_1->setText(task->emter_info[EMTER_NUM1].emter_current);
        ui->c_power_1->setText(task->emter_info[EMTER_NUM1].emter_power);
    }else{
        ui->c_vol_2->setText(task->emter_info[EMTER_NUM2].emter_vol);
        ui->c_current_2->setText(task->emter_info[EMTER_NUM2].emter_current);
        ui->c_power_2->setText(task->emter_info[EMTER_NUM2].emter_power);
    }

    if(BMS_COMMUNICATION_ERROR == (task->crf_DC_info.spn8448_status_1 & BMS_COMMUNICATION_ERROR)){
            log_printf(DBG, "TCU: BMS  "GRN("通信异常"));
            ui->bat_status_1->setText("异常");
    }else{
            log_printf(DBG, "TCU: BMS  "GRN("通信正常"));
            ui->bat_status_1->setText("正常");
    }

}
void  double_gun::c_equ_msg()
{
    char ch[50];
    sprintf(ch,"%02x%02x%02x%02x",
            task->tcp_info.spn2304_charger_sn[0],
            task->tcp_info.spn2304_charger_sn[1],
            task->tcp_info.spn2304_charger_sn[2],
            task->tcp_info.spn2304_charger_sn[3]);
    ui->charger_sn->setText(ch);

    sprintf(ch,"%d",task->crf_DC_info.spn8448_port);
    ui->charger_interface_ID->setText(ch);
}
void  double_gun::c_bill_msg()
{
    if(task->gun_sn == GUN_SN0){
        ui->total_power->setText(task->emter_info[EMTER_NUM0].emter_power);
    }else if(task->gun_sn == GUN_SN1){
        ui->total_power->setText(task->emter_info[EMTER_NUM1].emter_power);
    }else{
        ui->total_power->setText(task->emter_info[EMTER_NUM2].emter_power);
    }

}
void  double_gun::c_moni_msg_2()
{
    char ch[50];

    int cc_status;
    cc_status = task->crf_DC_info.spn8448_status_1 & 0x0F;

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
    ui->c_status_2->setText(ch);

    sprintf(ch,"%d",task->ctf_DC_info.spn8704_soc);
    ui->bat_soc_2->setText(ch);

    ui->c_vol_2->setText(task->emter_info[EMTER_NUM2].emter_vol);
    ui->c_current_2->setText(task->emter_info[EMTER_NUM2].emter_current);
    ui->c_power_2->setText(task->emter_info[EMTER_NUM2].emter_power);


    if(BMS_COMMUNICATION_ERROR == (task->crf_DC_info.spn8448_status_1 & BMS_COMMUNICATION_ERROR)){
            log_printf(DBG, "TCU: BMS  "GRN("通信异常"));
            ui->bat_status_2->setText("异常");
    }else{
            log_printf(DBG, "TCU: BMS  "GRN("通信正常"));
            ui->bat_status_2->setText("正常");
    }

}
void  double_gun::c_equ_msg_2()
{
    char ch[50];
    sprintf(ch,"%02x%02x%02x%02x",
            task->tcp_info.spn2304_charger_sn[0],
            task->tcp_info.spn2304_charger_sn[1],
            task->tcp_info.spn2304_charger_sn[2],
            task->tcp_info.spn2304_charger_sn[3]);
    ui->charger_sn_2->setText(ch);

    sprintf(ch,"%d",task->crf_DC_info.spn8448_port);
    ui->charger_interface_ID_2->setText(ch);
}
void  double_gun::c_bill_msg_2()
{
        ui->total_power_2->setText(task->emter_info[EMTER_NUM2].emter_power);
}
