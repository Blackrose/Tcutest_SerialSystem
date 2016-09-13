/********************************************************************************
** Form generated from reading UI file 'netwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWINDOW_H
#define UI_NETWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "network/qipaddressedit.h"

QT_BEGIN_NAMESPACE

class Ui_NetWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radio_dhcp;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QVBoxLayout *verticalLayout;
    QRadioButton *radio_static;
    QIpAddressEdit *edt_ip;
    QIpAddressEdit *edt_mask;
    QIpAddressEdit *edt_gateway;
    QIpAddressEdit *edt_dns;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QTextEdit *ip_inf;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLineEdit *hostname;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_7;
    QPushButton *ping;
    QPushButton *stop;
    QPushButton *clear;
    QTextEdit *result;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QComboBox *cb_interface;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *ok;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *back_but;

    void setupUi(QMainWindow *NetWindow)
    {
        if (NetWindow->objectName().isEmpty())
            NetWindow->setObjectName(QString::fromUtf8("NetWindow"));
        NetWindow->resize(800, 480);
        NetWindow->setStyleSheet(QString::fromUtf8(""));
        centralWidget = new QWidget(NetWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(13, 40, 779, 401));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(779, 0));
        groupBox->setMaximumSize(QSize(779, 421));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 20, 761, 371));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        radio_dhcp = new QRadioButton(widget);
        radio_dhcp->setObjectName(QString::fromUtf8("radio_dhcp"));
        sizePolicy.setHeightForWidth(radio_dhcp->sizePolicy().hasHeightForWidth());
        radio_dhcp->setSizePolicy(sizePolicy);
        radio_dhcp->setMaximumSize(QSize(16777215, 20));
        QFont font;
        font.setPointSize(14);
        radio_dhcp->setFont(font);

        verticalLayout_2->addWidget(radio_dhcp);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(18);
        label_2->setFont(font1);

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font1);

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setFont(font1);

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setFont(font1);

        verticalLayout_2->addWidget(label_5);


        horizontalLayout_4->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        radio_static = new QRadioButton(widget);
        radio_static->setObjectName(QString::fromUtf8("radio_static"));
        sizePolicy.setHeightForWidth(radio_static->sizePolicy().hasHeightForWidth());
        radio_static->setSizePolicy(sizePolicy);
        radio_static->setMaximumSize(QSize(16777215, 20));
        radio_static->setFont(font);

        verticalLayout->addWidget(radio_static);

        edt_ip = new QIpAddressEdit(widget);
        edt_ip->setObjectName(QString::fromUtf8("edt_ip"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(edt_ip->sizePolicy().hasHeightForWidth());
        edt_ip->setSizePolicy(sizePolicy1);
        edt_ip->setMinimumSize(QSize(0, 30));
        edt_ip->setFont(font);
        edt_ip->setStyleSheet(QString::fromUtf8("background:rgb(69, 255, 240)"));

        verticalLayout->addWidget(edt_ip);

        edt_mask = new QIpAddressEdit(widget);
        edt_mask->setObjectName(QString::fromUtf8("edt_mask"));
        sizePolicy1.setHeightForWidth(edt_mask->sizePolicy().hasHeightForWidth());
        edt_mask->setSizePolicy(sizePolicy1);
        edt_mask->setMinimumSize(QSize(250, 30));
        edt_mask->setFont(font);
        edt_mask->setStyleSheet(QString::fromUtf8("background:rgb(69, 255, 240)"));

        verticalLayout->addWidget(edt_mask);

        edt_gateway = new QIpAddressEdit(widget);
        edt_gateway->setObjectName(QString::fromUtf8("edt_gateway"));
        sizePolicy1.setHeightForWidth(edt_gateway->sizePolicy().hasHeightForWidth());
        edt_gateway->setSizePolicy(sizePolicy1);
        edt_gateway->setMinimumSize(QSize(0, 30));
        edt_gateway->setFont(font);
        edt_gateway->setStyleSheet(QString::fromUtf8("background:rgb(69, 255, 240)"));

        verticalLayout->addWidget(edt_gateway);

        edt_dns = new QIpAddressEdit(widget);
        edt_dns->setObjectName(QString::fromUtf8("edt_dns"));
        sizePolicy1.setHeightForWidth(edt_dns->sizePolicy().hasHeightForWidth());
        edt_dns->setSizePolicy(sizePolicy1);
        edt_dns->setMinimumSize(QSize(0, 30));
        edt_dns->setFont(font);
        edt_dns->setStyleSheet(QString::fromUtf8("background:rgb(69, 255, 240)"));

        verticalLayout->addWidget(edt_dns);


        horizontalLayout_4->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_4);

        groupBox_3 = new QGroupBox(widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        ip_inf = new QTextEdit(groupBox_3);
        ip_inf->setObjectName(QString::fromUtf8("ip_inf"));

        gridLayout_2->addWidget(ip_inf, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_3);


        horizontalLayout_5->addLayout(verticalLayout_3);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        hostname = new QLineEdit(widget);
        hostname->setObjectName(QString::fromUtf8("hostname"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(hostname->sizePolicy().hasHeightForWidth());
        hostname->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setPointSize(13);
        hostname->setFont(font2);

        gridLayout->addWidget(hostname, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setPointSize(16);
        groupBox_2->setFont(font3);
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        ping = new QPushButton(groupBox_2);
        ping->setObjectName(QString::fromUtf8("ping"));
        sizePolicy1.setHeightForWidth(ping->sizePolicy().hasHeightForWidth());
        ping->setSizePolicy(sizePolicy1);
        QFont font4;
        font4.setPointSize(11);
        ping->setFont(font4);

        gridLayout_7->addWidget(ping, 1, 0, 1, 1);

        stop = new QPushButton(groupBox_2);
        stop->setObjectName(QString::fromUtf8("stop"));
        sizePolicy1.setHeightForWidth(stop->sizePolicy().hasHeightForWidth());
        stop->setSizePolicy(sizePolicy1);
        stop->setFont(font4);

        gridLayout_7->addWidget(stop, 1, 1, 1, 1);

        clear = new QPushButton(groupBox_2);
        clear->setObjectName(QString::fromUtf8("clear"));
        sizePolicy1.setHeightForWidth(clear->sizePolicy().hasHeightForWidth());
        clear->setSizePolicy(sizePolicy1);
        clear->setFont(font4);

        gridLayout_7->addWidget(clear, 1, 2, 1, 1);

        result = new QTextEdit(groupBox_2);
        result->setObjectName(QString::fromUtf8("result"));
        result->setFont(font4);

        gridLayout_7->addWidget(result, 0, 0, 1, 3);


        horizontalLayout_2->addLayout(gridLayout_7);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 2);


        horizontalLayout_5->addLayout(gridLayout);

        widget1 = new QWidget(centralWidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(13, 7, 781, 27));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget1);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(105, 16777215));
        label->setFont(font3);

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cb_interface = new QComboBox(widget1);
        cb_interface->setObjectName(QString::fromUtf8("cb_interface"));
        sizePolicy2.setHeightForWidth(cb_interface->sizePolicy().hasHeightForWidth());
        cb_interface->setSizePolicy(sizePolicy2);
        cb_interface->setMinimumSize(QSize(100, 25));
        cb_interface->setMaximumSize(QSize(100, 25));
        cb_interface->setFont(font4);

        horizontalLayout->addWidget(cb_interface);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        widget2 = new QWidget(centralWidget);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(13, 448, 781, 27));
        horizontalLayout_3 = new QHBoxLayout(widget2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        ok = new QPushButton(widget2);
        ok->setObjectName(QString::fromUtf8("ok"));
        sizePolicy2.setHeightForWidth(ok->sizePolicy().hasHeightForWidth());
        ok->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(ok);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        back_but = new QPushButton(widget2);
        back_but->setObjectName(QString::fromUtf8("back_but"));

        horizontalLayout_3->addWidget(back_but);

        NetWindow->setCentralWidget(centralWidget);

        retranslateUi(NetWindow);

        QMetaObject::connectSlotsByName(NetWindow);
    } // setupUi

    void retranslateUi(QMainWindow *NetWindow)
    {
        NetWindow->setWindowTitle(QApplication::translate("NetWindow", "MainWindow", 0));
        groupBox->setTitle(QString());
        radio_dhcp->setText(QApplication::translate("NetWindow", "DHCP", 0));
        label_2->setText(QApplication::translate("NetWindow", "ip:", 0));
        label_3->setText(QApplication::translate("NetWindow", "netmask:", 0));
        label_4->setText(QApplication::translate("NetWindow", "gateway:", 0));
        label_5->setText(QApplication::translate("NetWindow", "dns:", 0));
        radio_static->setText(QApplication::translate("NetWindow", "STATIC", 0));
        groupBox_3->setTitle(QApplication::translate("NetWindow", "IP Information", 0));
        label_6->setText(QApplication::translate("NetWindow", "hostname:", 0));
        groupBox_2->setTitle(QApplication::translate("NetWindow", " result", 0));
        ping->setText(QApplication::translate("NetWindow", "ping", 0));
        stop->setText(QApplication::translate("NetWindow", "stop", 0));
        clear->setText(QApplication::translate("NetWindow", "clear", 0));
        label->setText(QApplication::translate("NetWindow", "  interface:", 0));
        ok->setText(QApplication::translate("NetWindow", "Apply and Restart Network", 0));
        back_but->setText(QApplication::translate("NetWindow", "back", 0));
    } // retranslateUi

};

namespace Ui {
    class NetWindow: public Ui_NetWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWINDOW_H
