/********************************************************************************
** Form generated from reading UI file 'bat_information.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BAT_INFORMATION_H
#define UI_BAT_INFORMATION_H

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

class Ui_bat_information
{
public:
    QLabel *label;
    QPushButton *change_equ_but;
    QPushButton *change_batinf_but;
    QPushButton *change_moni_but;
    QPushButton *change_billinf_but;
    QLineEdit *bms_status;
    QLineEdit *bms_soc;
    QLineEdit *rated_vol;
    QLineEdit *charge_timelife;
    QLineEdit *allow_charging_vol;
    QLineEdit *allow_charging_current;
    QLineEdit *allow_charging_C;
    QLineEdit *max_allow_charging_vol;
    QLineEdit *max_vol_position;
    QLineEdit *max_measuring_C;
    QLineEdit *max_vol;
    QLineEdit *bat_type;
    QLineEdit *bat_capacity;
    QLineEdit *max_measuring_C_position;

    void setupUi(QWidget *bat_information)
    {
        if (bat_information->objectName().isEmpty())
            bat_information->setObjectName(QString::fromUtf8("bat_information"));
        bat_information->resize(800, 480);
        bat_information->setAutoFillBackground(false);
        bat_information->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(bat_information);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 480));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/32_E3.png)"));
        change_equ_but = new QPushButton(bat_information);
        change_equ_but->setObjectName(QString::fromUtf8("change_equ_but"));
        change_equ_but->setGeometry(QRect(30, 190, 98, 81));
        change_equ_but->setFocusPolicy(Qt::NoFocus);
        change_equ_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_equ_but->setFlat(true);
        change_batinf_but = new QPushButton(bat_information);
        change_batinf_but->setObjectName(QString::fromUtf8("change_batinf_but"));
        change_batinf_but->setGeometry(QRect(30, 270, 98, 81));
        change_batinf_but->setFocusPolicy(Qt::NoFocus);
        change_batinf_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_batinf_but->setFlat(true);
        change_moni_but = new QPushButton(bat_information);
        change_moni_but->setObjectName(QString::fromUtf8("change_moni_but"));
        change_moni_but->setGeometry(QRect(28, 98, 98, 81));
        change_moni_but->setFocusPolicy(Qt::NoFocus);
        change_moni_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_moni_but->setFlat(true);
        change_billinf_but = new QPushButton(bat_information);
        change_billinf_but->setObjectName(QString::fromUtf8("change_billinf_but"));
        change_billinf_but->setGeometry(QRect(30, 360, 98, 81));
        change_billinf_but->setFocusPolicy(Qt::NoFocus);
        change_billinf_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_billinf_but->setFlat(true);
        bms_status = new QLineEdit(bat_information);
        bms_status->setObjectName(QString::fromUtf8("bms_status"));
        bms_status->setGeometry(QRect(350, 133, 98, 36));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        bms_status->setFont(font);
        bms_soc = new QLineEdit(bat_information);
        bms_soc->setObjectName(QString::fromUtf8("bms_soc"));
        bms_soc->setGeometry(QRect(651, 133, 98, 36));
        bms_soc->setFont(font);
        rated_vol = new QLineEdit(bat_information);
        rated_vol->setObjectName(QString::fromUtf8("rated_vol"));
        rated_vol->setGeometry(QRect(350, 173, 98, 36));
        rated_vol->setFont(font);
        charge_timelife = new QLineEdit(bat_information);
        charge_timelife->setObjectName(QString::fromUtf8("charge_timelife"));
        charge_timelife->setGeometry(QRect(350, 213, 98, 36));
        charge_timelife->setFont(font);
        allow_charging_vol = new QLineEdit(bat_information);
        allow_charging_vol->setObjectName(QString::fromUtf8("allow_charging_vol"));
        allow_charging_vol->setGeometry(QRect(350, 294, 98, 37));
        allow_charging_vol->setFont(font);
        allow_charging_current = new QLineEdit(bat_information);
        allow_charging_current->setObjectName(QString::fromUtf8("allow_charging_current"));
        allow_charging_current->setGeometry(QRect(350, 254, 98, 38));
        allow_charging_current->setFont(font);
        allow_charging_C = new QLineEdit(bat_information);
        allow_charging_C->setObjectName(QString::fromUtf8("allow_charging_C"));
        allow_charging_C->setGeometry(QRect(350, 333, 98, 38));
        allow_charging_C->setFont(font);
        max_allow_charging_vol = new QLineEdit(bat_information);
        max_allow_charging_vol->setObjectName(QString::fromUtf8("max_allow_charging_vol"));
        max_allow_charging_vol->setGeometry(QRect(350, 374, 98, 38));
        max_allow_charging_vol->setFont(font);
        max_vol_position = new QLineEdit(bat_information);
        max_vol_position->setObjectName(QString::fromUtf8("max_vol_position"));
        max_vol_position->setGeometry(QRect(650, 294, 98, 37));
        max_vol_position->setFont(font);
        max_measuring_C = new QLineEdit(bat_information);
        max_measuring_C->setObjectName(QString::fromUtf8("max_measuring_C"));
        max_measuring_C->setGeometry(QRect(650, 333, 98, 38));
        max_measuring_C->setFont(font);
        max_vol = new QLineEdit(bat_information);
        max_vol->setObjectName(QString::fromUtf8("max_vol"));
        max_vol->setGeometry(QRect(650, 253, 98, 38));
        max_vol->setFont(font);
        bat_type = new QLineEdit(bat_information);
        bat_type->setObjectName(QString::fromUtf8("bat_type"));
        bat_type->setGeometry(QRect(650, 173, 98, 36));
        bat_type->setFont(font);
        bat_capacity = new QLineEdit(bat_information);
        bat_capacity->setObjectName(QString::fromUtf8("bat_capacity"));
        bat_capacity->setGeometry(QRect(650, 213, 98, 38));
        bat_capacity->setFont(font);
        max_measuring_C_position = new QLineEdit(bat_information);
        max_measuring_C_position->setObjectName(QString::fromUtf8("max_measuring_C_position"));
        max_measuring_C_position->setGeometry(QRect(650, 374, 98, 38));
        max_measuring_C_position->setFont(font);

        retranslateUi(bat_information);

        QMetaObject::connectSlotsByName(bat_information);
    } // setupUi

    void retranslateUi(QWidget *bat_information)
    {
        bat_information->setWindowTitle(QApplication::translate("bat_information", "Form", 0));
        label->setText(QString());
        change_equ_but->setText(QString());
        change_batinf_but->setText(QString());
        change_moni_but->setText(QString());
        change_billinf_but->setText(QString());
        bms_status->setText(QApplication::translate("bat_information", "\345\276\205\346\234\272", 0));
        bms_soc->setText(QApplication::translate("bat_information", "50", 0));
        rated_vol->setText(QApplication::translate("bat_information", "500", 0));
        charge_timelife->setText(QApplication::translate("bat_information", "50", 0));
        allow_charging_vol->setText(QApplication::translate("bat_information", "500", 0));
        allow_charging_current->setText(QApplication::translate("bat_information", "60", 0));
        allow_charging_C->setText(QApplication::translate("bat_information", "90", 0));
        max_allow_charging_vol->setText(QApplication::translate("bat_information", "90", 0));
        max_vol_position->setText(QApplication::translate("bat_information", "1", 0));
        max_measuring_C->setText(QApplication::translate("bat_information", "90", 0));
        max_vol->setText(QApplication::translate("bat_information", "250", 0));
        bat_type->setText(QApplication::translate("bat_information", "\351\224\202", 0));
        bat_capacity->setText(QApplication::translate("bat_information", "50", 0));
        max_measuring_C_position->setText(QApplication::translate("bat_information", "1", 0));
    } // retranslateUi

};

namespace Ui {
    class bat_information: public Ui_bat_information {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BAT_INFORMATION_H
