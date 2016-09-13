/********************************************************************************
** Form generated from reading UI file 'billing_info.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BILLING_INFO_H
#define UI_BILLING_INFO_H

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

class Ui_Billing_info
{
public:
    QLabel *label;
    QPushButton *change_billinf_but;
    QPushButton *change_moni_but;
    QPushButton *change_equ_but;
    QPushButton *change_batinf_but;
    QLineEdit *total_power;
    QLineEdit *total_cost;
    QLineEdit *tip_power;
    QLineEdit *peak_power;
    QLineEdit *flat_power;
    QLineEdit *valley_power;
    QLineEdit *tip_price;
    QLineEdit *valley_price;
    QLineEdit *flat_price;
    QLineEdit *peak_price;

    void setupUi(QWidget *Billing_info)
    {
        if (Billing_info->objectName().isEmpty())
            Billing_info->setObjectName(QString::fromUtf8("Billing_info"));
        Billing_info->resize(800, 480);
        label = new QLabel(Billing_info);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 480));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/33_E4.png)"));
        change_billinf_but = new QPushButton(Billing_info);
        change_billinf_but->setObjectName(QString::fromUtf8("change_billinf_but"));
        change_billinf_but->setGeometry(QRect(30, 360, 98, 81));
        change_billinf_but->setFocusPolicy(Qt::NoFocus);
        change_billinf_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_billinf_but->setFlat(true);
        change_moni_but = new QPushButton(Billing_info);
        change_moni_but->setObjectName(QString::fromUtf8("change_moni_but"));
        change_moni_but->setGeometry(QRect(28, 98, 98, 81));
        change_moni_but->setFocusPolicy(Qt::NoFocus);
        change_moni_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_moni_but->setFlat(true);
        change_equ_but = new QPushButton(Billing_info);
        change_equ_but->setObjectName(QString::fromUtf8("change_equ_but"));
        change_equ_but->setGeometry(QRect(30, 190, 98, 81));
        change_equ_but->setFocusPolicy(Qt::NoFocus);
        change_equ_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_equ_but->setFlat(true);
        change_batinf_but = new QPushButton(Billing_info);
        change_batinf_but->setObjectName(QString::fromUtf8("change_batinf_but"));
        change_batinf_but->setGeometry(QRect(30, 270, 98, 81));
        change_batinf_but->setFocusPolicy(Qt::NoFocus);
        change_batinf_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_batinf_but->setFlat(true);
        total_power = new QLineEdit(Billing_info);
        total_power->setObjectName(QString::fromUtf8("total_power"));
        total_power->setGeometry(QRect(280, 121, 141, 37));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        total_power->setFont(font);
        total_cost = new QLineEdit(Billing_info);
        total_cost->setObjectName(QString::fromUtf8("total_cost"));
        total_cost->setGeometry(QRect(620, 121, 141, 37));
        total_cost->setFont(font);
        tip_power = new QLineEdit(Billing_info);
        tip_power->setObjectName(QString::fromUtf8("tip_power"));
        tip_power->setGeometry(QRect(283, 213, 137, 37));
        tip_power->setFont(font);
        peak_power = new QLineEdit(Billing_info);
        peak_power->setObjectName(QString::fromUtf8("peak_power"));
        peak_power->setGeometry(QRect(283, 265, 137, 37));
        peak_power->setFont(font);
        flat_power = new QLineEdit(Billing_info);
        flat_power->setObjectName(QString::fromUtf8("flat_power"));
        flat_power->setGeometry(QRect(283, 320, 137, 37));
        flat_power->setFont(font);
        valley_power = new QLineEdit(Billing_info);
        valley_power->setObjectName(QString::fromUtf8("valley_power"));
        valley_power->setGeometry(QRect(283, 372, 137, 37));
        valley_power->setFont(font);
        tip_price = new QLineEdit(Billing_info);
        tip_price->setObjectName(QString::fromUtf8("tip_price"));
        tip_price->setGeometry(QRect(620, 211, 137, 37));
        tip_price->setFont(font);
        valley_price = new QLineEdit(Billing_info);
        valley_price->setObjectName(QString::fromUtf8("valley_price"));
        valley_price->setGeometry(QRect(620, 372, 137, 37));
        valley_price->setFont(font);
        flat_price = new QLineEdit(Billing_info);
        flat_price->setObjectName(QString::fromUtf8("flat_price"));
        flat_price->setGeometry(QRect(620, 320, 137, 37));
        flat_price->setFont(font);
        peak_price = new QLineEdit(Billing_info);
        peak_price->setObjectName(QString::fromUtf8("peak_price"));
        peak_price->setGeometry(QRect(620, 265, 137, 37));
        peak_price->setFont(font);

        retranslateUi(Billing_info);

        QMetaObject::connectSlotsByName(Billing_info);
    } // setupUi

    void retranslateUi(QWidget *Billing_info)
    {
        Billing_info->setWindowTitle(QApplication::translate("Billing_info", "Form", 0));
        label->setText(QString());
        change_billinf_but->setText(QString());
        change_moni_but->setText(QString());
        change_equ_but->setText(QString());
        change_batinf_but->setText(QString());
        total_power->setText(QApplication::translate("Billing_info", "60", 0));
        total_cost->setText(QApplication::translate("Billing_info", "100", 0));
        tip_power->setText(QApplication::translate("Billing_info", "60", 0));
        peak_power->setText(QApplication::translate("Billing_info", "60", 0));
        flat_power->setText(QApplication::translate("Billing_info", "60", 0));
        valley_power->setText(QApplication::translate("Billing_info", "60", 0));
        tip_price->setText(QApplication::translate("Billing_info", "1.5", 0));
        valley_price->setText(QApplication::translate("Billing_info", "1.0", 0));
        flat_price->setText(QApplication::translate("Billing_info", "1.2", 0));
        peak_price->setText(QApplication::translate("Billing_info", "1.5", 0));
    } // retranslateUi

};

namespace Ui {
    class Billing_info: public Ui_Billing_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BILLING_INFO_H
