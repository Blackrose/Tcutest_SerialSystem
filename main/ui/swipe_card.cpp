#include "swipe_card.h"
#include "ui_swipe_card.h"
#include "log.h"
#include "card_operation.h"

#define CARD
//#undef CARD

Swipe_card::Swipe_card(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Swipe_card)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);//窗口没有没有边
    setAttribute(Qt::WA_DeleteOnClose); //关闭时自动的释放内存

#ifdef CARD
    flag = 1;
    if(card_timer.isActive()){
        //card_timer.stop();//防止重新创建
    }else{
        log_printf(WRN,RED("CardWindow"));
        p_card = new CardWindow;
        p_card->ComInit();
        connect(&card_timer,SIGNAL(timeout()),this,SLOT(slot_cardtimer()));//充电信息
        card_timer.start(1000);
    }
     log_printf(WRN, "TCU: "RED("CardWindow CardWindow"));
#endif
}

#ifdef CARD
void  Swipe_card::slot_cardtimer()
{
//    if(flag == 1){
//        p_card->SendData("3111");//
//        flag = 0;
//    }else if(flag == 0){
//        p_card->SendData("3113");//
//        flag = 2;
//    }else if(flag == 2){
//        p_card->SendData("3114");//
//        flag = 1;
//    }
    p_card->SendData("3224");
    p_card->sendCardMsg();
    p_card->readCardCom();
    printf("length ===%d\n",strlen(p_card->recvBuf));
    if(strlen(p_card->recvBuf)>0)
    {
        card_timer.stop();
        card_operation *w_card_operation = new card_operation;
        w_card_operation->show();
    }
}
#endif

Swipe_card::~Swipe_card()
{
    delete ui;
}
