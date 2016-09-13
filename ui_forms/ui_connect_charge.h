/********************************************************************************
** Form generated from reading UI file 'connect_charge.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECT_CHARGE_H
#define UI_CONNECT_CHARGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_connect_charge
{
public:
    QLabel *label;
    QLabel *label_tcu_version;
    QLineEdit *tcu_version;
    QLabel *label_time;
    QLabel *lblLocalTime;
    QPushButton *back_but;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *connect_charge)
    {
        if (connect_charge->objectName().isEmpty())
            connect_charge->setObjectName(QString::fromUtf8("connect_charge"));
        connect_charge->resize(800, 480);
        connect_charge->setAutoFillBackground(false);
        connect_charge->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(connect_charge);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 480));
        label->setCursor(QCursor(Qt::ArrowCursor));
        label->setMouseTracking(true);
        label->setFocusPolicy(Qt::StrongFocus);
        label->setAcceptDrops(true);
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("background:url(:/img/images/Main.png)"));
        label_tcu_version = new QLabel(connect_charge);
        label_tcu_version->setObjectName(QString::fromUtf8("label_tcu_version"));
        label_tcu_version->setGeometry(QRect(20, 430, 51, 31));
        label_tcu_version->setStyleSheet(QString::fromUtf8("background:url()"));
        tcu_version = new QLineEdit(connect_charge);
        tcu_version->setObjectName(QString::fromUtf8("tcu_version"));
        tcu_version->setEnabled(true);
        tcu_version->setGeometry(QRect(80, 430, 81, 31));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        tcu_version->setFont(font);
        tcu_version->setCursor(QCursor(Qt::ArrowCursor));
        tcu_version->setMouseTracking(false);
        tcu_version->setFocusPolicy(Qt::NoFocus);
        tcu_version->setAcceptDrops(false);
        label_time = new QLabel(connect_charge);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(180, 430, 41, 31));
        label_time->setStyleSheet(QString::fromUtf8("background:url()"));
        lblLocalTime = new QLabel(connect_charge);
        lblLocalTime->setObjectName(QString::fromUtf8("lblLocalTime"));
        lblLocalTime->setGeometry(QRect(220, 430, 401, 29));
        lblLocalTime->setFont(font);
        lblLocalTime->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lblLocalTime->setFrameShape(QFrame::Box);
        lblLocalTime->setFrameShadow(QFrame::Plain);
        lblLocalTime->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        back_but = new QPushButton(connect_charge);
        back_but->setObjectName(QString::fromUtf8("back_but"));
        back_but->setGeometry(QRect(0, 0, 201, 63));
        back_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        back_but->setFlat(true);
        label_2 = new QLabel(connect_charge);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(590, 0, 191, 71));
        label_2->setAutoFillBackground(false);
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/serial_logo.png)"));
        label_3 = new QLabel(connect_charge);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(290, 220, 251, 51));
        QFont font1;
        font1.setPointSize(27);
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);

        retranslateUi(connect_charge);

        QMetaObject::connectSlotsByName(connect_charge);
    } // setupUi

    void retranslateUi(QWidget *connect_charge)
    {
        connect_charge->setWindowTitle(QApplication::translate("connect_charge", "Form", 0));
        label->setText(QString());
        label_tcu_version->setText(QApplication::translate("connect_charge", "\346\235\277\346\234\254\345\217\267:", 0));
        tcu_version->setText(QApplication::translate("connect_charge", "12.10", 0));
        label_time->setText(QApplication::translate("connect_charge", "\346\227\266\351\227\264:", 0));
        lblLocalTime->setText(QApplication::translate("connect_charge", "00-00-00  \346\230\237\346\234\237:0 00:00:00:000", 0));
        back_but->setText(QString());
        label_2->setText(QString());
        label_3->setText(QApplication::translate("connect_charge", "\350\257\267\350\277\236\346\216\245\347\224\265\345\212\250\346\261\275\350\275\246", 0));
    } // retranslateUi

};

namespace Ui {
    class connect_charge: public Ui_connect_charge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECT_CHARGE_H
