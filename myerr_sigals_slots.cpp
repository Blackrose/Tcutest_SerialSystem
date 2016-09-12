#include "myerr_sigals_slots.h"
#include "stdio.h"
#include "tcu.h"

myerr_sigals_slots::myerr_sigals_slots(QWidget *parent) : QWidget(parent)
{
    connect(this,SIGNAL(ValueChanged(int)),this,SLOT(ChangeValue(int)));
    msgBox.setGeometry(350,150,150,100);
    msgBox.resize(150,100);
    msgBox.setFixedSize(150,100);
}


void myerr_sigals_slots::SetValue(int value)
{
    //if(value!=oldvalue)
    {
        //oldvalue=value;
        //value_tmp =value;
        emit ValueChanged(value);
    }
}

void myerr_sigals_slots::ChangeValue(int value)
{
    //FunctionForChangingTheValue(value);
    printf("now ChangeValue\n");
    //equipment_testing *w_equ_testing = new equipment_testing;
    //Charging_monitoring *w_change_moni = new Charging_monitoring;

    switch(value)
    {
        case TCU_ERR_STAGE_INVALID:
            break;
        case TCU_ERR_STAGE_CHECKVER:
             msgBox.critical(NULL, "Error", "版本校验失败");
            break;
        case TCU_ERR_STAGE_PARAMETER:
            msgBox.critical(NULL, "Error", "充电参数不匹配");
            break;
        case TCU_ERR_STAGE_CONNECT:
            break;
        case TCU_ERR_STAGE_START:
            break;
        case TCU_ERR_STAGE_STATUS:
            break;
        case TCU_ERR_STAGE_STOP:
            break;
        case TCU_ERR_STAGE_STOP_STATUS:
            break;
        case  TCU_ERR_STAGE_HEAT:
            break;
        case  TCU_ERR_STAGE_TIME:
            break;
        case  TCU_ERR_STAGE_ANY:
            break;
    }
}
