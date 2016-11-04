/*=================================
		主界面
=================================*/
#ifndef LINLONG_MAIN
#define LINLONG_MAIN

#include <QWidget>
#include <QString>
#include <QInputDialog>
#include <QMessageBox>
//#include <QSqlDatabase>
#include <QWidget>
#include <time.h>
//#include <QWSInputMethod>
//#include <QWSServer>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>
#include <QProgressBar>
#include<QPixmap>
#include <QDesktopWidget>

#include "ui_main.h"
#include "secondwindow.h"
#include "message/message.h"
#include "Emter_window.h"

#define  EMTER_MAIN
#undef  EMTER_MAIN

class  Main:public QWidget,public Ui_MainForm
{
        Q_OBJECT
public :
        Main(QProgressBar *proBar,QWidget* parent = NULL);
        virtual ~Main();
        //Secondwindow  *w_second;
        void timerEvent(QTimerEvent *);
#ifdef EMTER_MAIN
        EmterWindow *p_emter;
#endif       
public slots:
        void secondwindow();
        void autotestwindow();
        void manualtestwindow();
};
#endif
