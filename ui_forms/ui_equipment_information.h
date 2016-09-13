/********************************************************************************
** Form generated from reading UI file 'equipment_information.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EQUIPMENT_INFORMATION_H
#define UI_EQUIPMENT_INFORMATION_H

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

class Ui_Equipment_information
{
public:
    QLabel *label;
    QPushButton *change_equ_but;
    QPushButton *change_batinf_but;
    QPushButton *change_moni_but;
    QPushButton *change_billinf_but;
    QLineEdit *charger_sn;
    QLineEdit *charger_interface_ID;
    QLineEdit *charger_status;
    QLineEdit *charge_power;
    QLineEdit *charge_current;
    QLineEdit *charge_vol;

    void setupUi(QWidget *Equipment_information)
    {
        if (Equipment_information->objectName().isEmpty())
            Equipment_information->setObjectName(QString::fromUtf8("Equipment_information"));
        Equipment_information->resize(800, 480);
        label = new QLabel(Equipment_information);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 480));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/31.png)"));
        change_equ_but = new QPushButton(Equipment_information);
        change_equ_but->setObjectName(QString::fromUtf8("change_equ_but"));
        change_equ_but->setGeometry(QRect(30, 190, 98, 81));
        change_equ_but->setFocusPolicy(Qt::NoFocus);
        change_equ_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_equ_but->setFlat(true);
        change_batinf_but = new QPushButton(Equipment_information);
        change_batinf_but->setObjectName(QString::fromUtf8("change_batinf_but"));
        change_batinf_but->setGeometry(QRect(30, 270, 98, 81));
        change_batinf_but->setFocusPolicy(Qt::NoFocus);
        change_batinf_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_batinf_but->setFlat(true);
        change_moni_but = new QPushButton(Equipment_information);
        change_moni_but->setObjectName(QString::fromUtf8("change_moni_but"));
        change_moni_but->setGeometry(QRect(28, 98, 98, 81));
        change_moni_but->setFocusPolicy(Qt::ClickFocus);
        change_moni_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_moni_but->setFlat(true);
        change_billinf_but = new QPushButton(Equipment_information);
        change_billinf_but->setObjectName(QString::fromUtf8("change_billinf_but"));
        change_billinf_but->setGeometry(QRect(30, 360, 98, 81));
        change_billinf_but->setFocusPolicy(Qt::NoFocus);
        change_billinf_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_billinf_but->setFlat(true);
        charger_sn = new QLineEdit(Equipment_information);
        charger_sn->setObjectName(QString::fromUtf8("charger_sn"));
        charger_sn->setGeometry(QRect(300, 115, 284, 35));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        charger_sn->setFont(font);
        charger_sn->setCursor(QCursor(Qt::ArrowCursor));
        charger_sn->setMouseTracking(false);
        charger_sn->setFocusPolicy(Qt::NoFocus);
        charger_interface_ID = new QLineEdit(Equipment_information);
        charger_interface_ID->setObjectName(QString::fromUtf8("charger_interface_ID"));
        charger_interface_ID->setGeometry(QRect(300, 166, 284, 35));
        charger_interface_ID->setFont(font);
        charger_interface_ID->setCursor(QCursor(Qt::ArrowCursor));
        charger_interface_ID->setMouseTracking(false);
        charger_interface_ID->setFocusPolicy(Qt::NoFocus);
        charger_status = new QLineEdit(Equipment_information);
        charger_status->setObjectName(QString::fromUtf8("charger_status"));
        charger_status->setGeometry(QRect(300, 248, 140, 38));
        charger_status->setFont(font);
        charger_status->setCursor(QCursor(Qt::ArrowCursor));
        charger_status->setMouseTracking(false);
        charger_status->setFocusPolicy(Qt::NoFocus);
        charge_power = new QLineEdit(Equipment_information);
        charge_power->setObjectName(QString::fromUtf8("charge_power"));
        charge_power->setGeometry(QRect(600, 248, 140, 38));
        charge_power->setFont(font);
        charge_power->setCursor(QCursor(Qt::ArrowCursor));
        charge_power->setMouseTracking(false);
        charge_power->setFocusPolicy(Qt::NoFocus);
        charge_current = new QLineEdit(Equipment_information);
        charge_current->setObjectName(QString::fromUtf8("charge_current"));
        charge_current->setGeometry(QRect(600, 304, 140, 38));
        charge_current->setFont(font);
        charge_current->setCursor(QCursor(Qt::ArrowCursor));
        charge_current->setMouseTracking(false);
        charge_current->setFocusPolicy(Qt::NoFocus);
        charge_vol = new QLineEdit(Equipment_information);
        charge_vol->setObjectName(QString::fromUtf8("charge_vol"));
        charge_vol->setGeometry(QRect(300, 304, 140, 38));
        charge_vol->setFont(font);
        charge_vol->setCursor(QCursor(Qt::ArrowCursor));
        charge_vol->setMouseTracking(false);
        charge_vol->setFocusPolicy(Qt::NoFocus);

        retranslateUi(Equipment_information);

        QMetaObject::connectSlotsByName(Equipment_information);
    } // setupUi

    void retranslateUi(QWidget *Equipment_information)
    {
        Equipment_information->setWindowTitle(QApplication::translate("Equipment_information", "Form", 0));
        label->setText(QString());
        change_equ_but->setText(QString());
        change_batinf_but->setText(QString());
        change_moni_but->setText(QString());
        change_billinf_but->setText(QString());
        charger_sn->setText(QApplication::translate("Equipment_information", "01010101", 0));
        charger_interface_ID->setText(QApplication::translate("Equipment_information", "0", 0));
        charger_status->setText(QApplication::translate("Equipment_information", "\345\276\205\346\234\272", 0));
        charge_power->setText(QApplication::translate("Equipment_information", "60", 0));
        charge_current->setText(QApplication::translate("Equipment_information", "120", 0));
        charge_vol->setText(QApplication::translate("Equipment_information", "500", 0));
    } // retranslateUi

};

namespace Ui {
    class Equipment_information: public Ui_Equipment_information {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUIPMENT_INFORMATION_H
