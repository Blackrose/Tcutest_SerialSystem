#include "pingwindow.h"
#include "ui_pingwindow.h"
#include <QMessageBox>

PingWindow::PingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PingWindow)
{
    ui->setupUi(this);
    ui->hostname->setText("192.168.0.9");
    myprocess = NULL;
}

PingWindow::~PingWindow()
{
    delete ui;
}

void PingWindow::on_ping_clicked()
{
    if(ui->hostname->text() == QString(""))
    {
        QMessageBox::about(this,"error","hostname cannot be empty!");
        return;
    }

    if(myprocess)
        delete myprocess;

    myprocess = new QProcess(this);
    connect(myprocess, SIGNAL(readyReadStandardOutput()),this, SLOT(result()));
    connect(myprocess, SIGNAL(readyReadStandardError()),this, SLOT(result()));
    myprocess->start(QString("ping ")+ui->hostname->text());
    ui->result->append(QString("ping ")+ui->hostname->text());
    //myprocess->waitForFinished();
}

void PingWindow::result()
{
    QString abc = myprocess->readAllStandardOutput();
    ui->result->append(abc.trimmed());
    QString efg = myprocess->readAllStandardError();
    if(efg.length()>1)ui->result->append(efg.trimmed());
}

void PingWindow::on_stop_clicked()
{
    delete myprocess;
    myprocess = NULL;
}

void PingWindow::on_clear_clicked()
{
    ui->result->clear();
}

void PingWindow::closeEvent(QCloseEvent *)
{
    exit(0);
}

void PingWindow::moveEvent(QMoveEvent *)
{
    this->move(QPoint(0,0));
}

void PingWindow::resizeEvent(QResizeEvent *)
{
    this->showMaximized();
}


