#include "secondwindow.h"
#include "main.h"
#include <QWidget>
#include <QMovie>

//Check::Check(QWidget *parent): QWidget(parent),Ui_CheckForm()

Secondwindow::Secondwindow(QMainWindow *parent) : QMainWindow(parent), Ui_SecondWindow()
{
    setupUi(this);
    //par = parent;
    //setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);//窗口没有没有边框  是 一个模太对话框
   // connect(btn_close,SIGNAL(clicked()),this,SLOT(hide()));
    setAttribute(Qt::WA_DeleteOnClose);


    QMovie*movie=new QMovie(":/img/images/gif.gif");
    main_gif->setMovie(movie);
    movie->start();

    printf("init Secondwindow ok\n");
}

Secondwindow::~Secondwindow()
{
    printf("exit Help\n");
}
void Secondwindow::_show()
{
    show();
}

