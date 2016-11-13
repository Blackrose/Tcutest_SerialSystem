#include "mythread.h"
#include "tcu_canbus/serialsystem.h"
#include <stdio.h>

//mythread mythread_can ;

mythread::mythread(QObject *parent) : QThread(parent)
{
    stopstatus = false;
}

void mythread::run()
{
    printf("tcu_canbus\n");
    tcu_canbus();
    stopstatus = true;
}
void mythread::stop()
{
    printf("tcu_canstop\n");
    //if(stopstatus == true)
    {
        tcu_canstop();
    }
}
