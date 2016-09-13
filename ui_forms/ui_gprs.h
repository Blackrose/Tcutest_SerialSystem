/********************************************************************************
** Form generated from reading UI file 'gprs.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPRS_H
#define UI_GPRS_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gprs
{
public:
    QLabel *logo;
    QPushButton *back_but;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QComboBox *cb_com;
    QLabel *label_5;
    QComboBox *cb_bound;
    QLabel *label_6;
    QComboBox *cb_data;
    QLabel *label_7;
    QComboBox *cb_stop;
    QLabel *label_8;
    QComboBox *cb_partity;
    QPushButton *pbt_set;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    QPushButton *pbt_send;
    QPushButton *pbt_gprs;
    QLabel *label_3;
    QPushButton *ping;
    QLineEdit *Edit_phone;
    QLabel *label;
    QLabel *label_9;
    QPushButton *pbt_call;
    QLineEdit *hostname;
    QLabel *label_2;
    QLineEdit *Line_msg;
    QTextEdit *Edit_info;

    void setupUi(QWidget *Gprs)
    {
        if (Gprs->objectName().isEmpty())
            Gprs->setObjectName(QString::fromUtf8("Gprs"));
        Gprs->resize(800, 480);
        Gprs->setStyleSheet(QString::fromUtf8(""));
        logo = new QLabel(Gprs);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setGeometry(QRect(590, 0, 191, 71));
        logo->setMinimumSize(QSize(191, 71));
        logo->setMaximumSize(QSize(191, 71));
        logo->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/serial_logo.png)"));
        back_but = new QPushButton(Gprs);
        back_but->setObjectName(QString::fromUtf8("back_but"));
        back_but->setGeometry(QRect(18, 14, 121, 41));
        back_but->setFocusPolicy(Qt::ClickFocus);
        back_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        back_but->setFlat(true);
        layoutWidget = new QWidget(Gprs);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 70, 761, 391));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 80));
        groupBox->setMaximumSize(QSize(16777215, 122));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        cb_com = new QComboBox(groupBox);
        cb_com->setObjectName(QString::fromUtf8("cb_com"));

        gridLayout_3->addWidget(cb_com, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 0, 2, 1, 1);

        cb_bound = new QComboBox(groupBox);
        cb_bound->setObjectName(QString::fromUtf8("cb_bound"));

        gridLayout_3->addWidget(cb_bound, 0, 3, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 0, 4, 1, 1);

        cb_data = new QComboBox(groupBox);
        cb_data->setObjectName(QString::fromUtf8("cb_data"));

        gridLayout_3->addWidget(cb_data, 0, 5, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 1, 0, 1, 1);

        cb_stop = new QComboBox(groupBox);
        cb_stop->setObjectName(QString::fromUtf8("cb_stop"));

        gridLayout_3->addWidget(cb_stop, 1, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 1, 2, 1, 1);

        cb_partity = new QComboBox(groupBox);
        cb_partity->setObjectName(QString::fromUtf8("cb_partity"));

        gridLayout_3->addWidget(cb_partity, 1, 3, 1, 1);

        pbt_set = new QPushButton(groupBox);
        pbt_set->setObjectName(QString::fromUtf8("pbt_set"));

        gridLayout_3->addWidget(pbt_set, 1, 4, 1, 2);


        horizontalLayout->addLayout(gridLayout_3);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        groupBox_2->setMaximumSize(QSize(16777215, 240));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pbt_send = new QPushButton(groupBox_2);
        pbt_send->setObjectName(QString::fromUtf8("pbt_send"));

        gridLayout_2->addWidget(pbt_send, 1, 2, 1, 1);

        pbt_gprs = new QPushButton(groupBox_2);
        pbt_gprs->setObjectName(QString::fromUtf8("pbt_gprs"));

        gridLayout_2->addWidget(pbt_gprs, 2, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 3, 0, 1, 1);

        ping = new QPushButton(groupBox_2);
        ping->setObjectName(QString::fromUtf8("ping"));

        gridLayout_2->addWidget(ping, 3, 2, 1, 1);

        Edit_phone = new QLineEdit(groupBox_2);
        Edit_phone->setObjectName(QString::fromUtf8("Edit_phone"));

        gridLayout_2->addWidget(Edit_phone, 0, 1, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        pbt_call = new QPushButton(groupBox_2);
        pbt_call->setObjectName(QString::fromUtf8("pbt_call"));

        gridLayout_2->addWidget(pbt_call, 0, 2, 1, 1);

        hostname = new QLineEdit(groupBox_2);
        hostname->setObjectName(QString::fromUtf8("hostname"));

        gridLayout_2->addWidget(hostname, 2, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        Line_msg = new QLineEdit(groupBox_2);
        Line_msg->setObjectName(QString::fromUtf8("Line_msg"));

        gridLayout_2->addWidget(Line_msg, 1, 1, 1, 1);

        Edit_info = new QTextEdit(groupBox_2);
        Edit_info->setObjectName(QString::fromUtf8("Edit_info"));

        gridLayout_2->addWidget(Edit_info, 3, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(Gprs);

        cb_com->setCurrentIndex(3);
        cb_data->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Gprs);
    } // setupUi

    void retranslateUi(QWidget *Gprs)
    {
        Gprs->setWindowTitle(QApplication::translate("Gprs", "Gprs", 0));
        logo->setText(QString());
        back_but->setText(QString());
        groupBox->setTitle(QApplication::translate("Gprs", "com set", 0));
        label_4->setText(QApplication::translate("Gprs", "com:", 0));
        cb_com->clear();
        cb_com->insertItems(0, QStringList()
         << QApplication::translate("Gprs", "ttyO0", 0)
         << QApplication::translate("Gprs", "ttyO1", 0)
         << QApplication::translate("Gprs", "ttyO2", 0)
         << QApplication::translate("Gprs", "ttyO3", 0)
         << QApplication::translate("Gprs", "ttyO4", 0)
        );
        label_5->setText(QApplication::translate("Gprs", "bound:", 0));
        cb_bound->clear();
        cb_bound->insertItems(0, QStringList()
         << QApplication::translate("Gprs", "115200", 0)
         << QApplication::translate("Gprs", "9600", 0)
         << QApplication::translate("Gprs", "4800", 0)
        );
        label_6->setText(QApplication::translate("Gprs", "databits:", 0));
        cb_data->clear();
        cb_data->insertItems(0, QStringList()
         << QApplication::translate("Gprs", "5", 0)
         << QApplication::translate("Gprs", "6", 0)
         << QApplication::translate("Gprs", "7", 0)
         << QApplication::translate("Gprs", "8", 0)
        );
        label_7->setText(QApplication::translate("Gprs", "stopbits:", 0));
        cb_stop->clear();
        cb_stop->insertItems(0, QStringList()
         << QApplication::translate("Gprs", "1", 0)
         << QApplication::translate("Gprs", "1.5", 0)
         << QApplication::translate("Gprs", "2", 0)
        );
        label_8->setText(QApplication::translate("Gprs", "parity:", 0));
        cb_partity->clear();
        cb_partity->insertItems(0, QStringList()
         << QApplication::translate("Gprs", "N", 0)
         << QApplication::translate("Gprs", "O", 0)
         << QApplication::translate("Gprs", "E", 0)
        );
        pbt_set->setText(QApplication::translate("Gprs", "set", 0));
        groupBox_2->setTitle(QApplication::translate("Gprs", "gprs set", 0));
        pbt_send->setText(QApplication::translate("Gprs", "msg-s", 0));
        pbt_gprs->setText(QApplication::translate("Gprs", "gprs", 0));
        label_3->setText(QApplication::translate("Gprs", "information:", 0));
        ping->setText(QApplication::translate("Gprs", "ping", 0));
        Edit_phone->setText(QApplication::translate("Gprs", "18601024315", 0));
        label->setText(QApplication::translate("Gprs", "phone:", 0));
        label_9->setText(QApplication::translate("Gprs", "Message:", 0));
        pbt_call->setText(QApplication::translate("Gprs", "call", 0));
        hostname->setText(QApplication::translate("Gprs", "www.serialsystem.com", 0));
        label_2->setText(QApplication::translate("Gprs", "hostname:", 0));
        Line_msg->setText(QApplication::translate("Gprs", "message text", 0));
    } // retranslateUi

};

namespace Ui {
    class Gprs: public Ui_Gprs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPRS_H
