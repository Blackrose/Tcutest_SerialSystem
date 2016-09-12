#include "mythread.h"
#include "tcu_canbus/serialsystem.h"
mythread::mythread(QObject *parent) : QThread(parent)
{
    //stop = false;
}

void mythread::run()
{
    tcu_canbus();
}
void mythread::stop()
{
    tcu_canstop();
}
