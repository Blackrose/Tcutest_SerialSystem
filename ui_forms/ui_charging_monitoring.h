/********************************************************************************
** Form generated from reading UI file 'charging_monitoring.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGING_MONITORING_H
#define UI_CHARGING_MONITORING_H

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

class Ui_Charging_monitoring
{
public:
    QLabel *charge_monitoring;
    QLabel *full_charge;
    QPushButton *full_charge_but;
    QPushButton *charge_7but;
    QPushButton *charge_6but;
    QPushButton *charge_5but;
    QPushButton *charge_4but;
    QPushButton *charge_3but;
    QPushButton *charge_2but;
    QPushButton *charge_1but;
    QLineEdit *bat_soc;
    QPushButton *soc_set;
    QPushButton *change_moni_but;
    QPushButton *change_equ_but;
    QPushButton *change_billinf_but;
    QLineEdit *charge_current;
    QLineEdit *charge_power;
    QLineEdit *charge_vol;
    QLineEdit *bat_status;
    QLineEdit *charge_time;
    QLineEdit *charge_status;
    QPushButton *soc_stop;
    QPushButton *change_batinf_but;

    void setupUi(QWidget *Charging_monitoring)
    {
        if (Charging_monitoring->objectName().isEmpty())
            Charging_monitoring->setObjectName(QString::fromUtf8("Charging_monitoring"));
        Charging_monitoring->resize(800, 480);
        Charging_monitoring->setAutoFillBackground(true);
        Charging_monitoring->setStyleSheet(QString::fromUtf8(""));
        charge_monitoring = new QLabel(Charging_monitoring);
        charge_monitoring->setObjectName(QString::fromUtf8("charge_monitoring"));
        charge_monitoring->setGeometry(QRect(0, 0, 800, 480));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        charge_monitoring->setFont(font);
        charge_monitoring->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/30.png);"));
        full_charge = new QLabel(Charging_monitoring);
        full_charge->setObjectName(QString::fromUtf8("full_charge"));
        full_charge->setGeometry(QRect(410, 130, 171, 61));
        full_charge->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new8dianci.png)"));
        full_charge_but = new QPushButton(Charging_monitoring);
        full_charge_but->setObjectName(QString::fromUtf8("full_charge_but"));
        full_charge_but->setGeometry(QRect(610, 130, 128, 58));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/images/new8dianci.png"), QSize(), QIcon::Normal, QIcon::Off);
        full_charge_but->setIcon(icon);
        full_charge_but->setIconSize(QSize(128, 64));
        full_charge_but->setAutoDefault(false);
        charge_7but = new QPushButton(Charging_monitoring);
        charge_7but->setObjectName(QString::fromUtf8("charge_7but"));
        charge_7but->setGeometry(QRect(610, 130, 128, 58));
        charge_7but->setAutoFillBackground(false);
        charge_7but->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new7dianci.png)"));
        charge_6but = new QPushButton(Charging_monitoring);
        charge_6but->setObjectName(QString::fromUtf8("charge_6but"));
        charge_6but->setGeometry(QRect(610, 130, 128, 58));
        charge_6but->setAutoFillBackground(false);
        charge_6but->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new6dianci.png)"));
        charge_5but = new QPushButton(Charging_monitoring);
        charge_5but->setObjectName(QString::fromUtf8("charge_5but"));
        charge_5but->setGeometry(QRect(610, 130, 128, 58));
        charge_5but->setAutoFillBackground(false);
        charge_5but->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new5dianci.png)"));
        charge_4but = new QPushButton(Charging_monitoring);
        charge_4but->setObjectName(QString::fromUtf8("charge_4but"));
        charge_4but->setGeometry(QRect(610, 130, 128, 58));
        charge_4but->setAutoFillBackground(false);
        charge_4but->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new4dianci.png)"));
        charge_3but = new QPushButton(Charging_monitoring);
        charge_3but->setObjectName(QString::fromUtf8("charge_3but"));
        charge_3but->setGeometry(QRect(610, 130, 128, 58));
        charge_3but->setAutoFillBackground(false);
        charge_3but->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new3dianci.png)"));
        charge_2but = new QPushButton(Charging_monitoring);
        charge_2but->setObjectName(QString::fromUtf8("charge_2but"));
        charge_2but->setGeometry(QRect(610, 130, 128, 58));
        charge_2but->setAutoFillBackground(false);
        charge_2but->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new2dianci.png)"));
        charge_1but = new QPushButton(Charging_monitoring);
        charge_1but->setObjectName(QString::fromUtf8("charge_1but"));
        charge_1but->setGeometry(QRect(610, 130, 128, 58));
        charge_1but->setAutoFillBackground(false);
        charge_1but->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/new1dianci.png)"));
        bat_soc = new QLineEdit(Charging_monitoring);
        bat_soc->setObjectName(QString::fromUtf8("bat_soc"));
        bat_soc->setGeometry(QRect(435, 213, 100, 35));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        bat_soc->setFont(font1);
        soc_set = new QPushButton(Charging_monitoring);
        soc_set->setObjectName(QString::fromUtf8("soc_set"));
        soc_set->setGeometry(QRect(430, 260, 99, 27));
        change_moni_but = new QPushButton(Charging_monitoring);
        change_moni_but->setObjectName(QString::fromUtf8("change_moni_but"));
        change_moni_but->setGeometry(QRect(28, 98, 98, 81));
        change_moni_but->setFocusPolicy(Qt::NoFocus);
        change_moni_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_moni_but->setFlat(true);
        change_equ_but = new QPushButton(Charging_monitoring);
        change_equ_but->setObjectName(QString::fromUtf8("change_equ_but"));
        change_equ_but->setGeometry(QRect(30, 190, 98, 81));
        change_equ_but->setFocusPolicy(Qt::NoFocus);
        change_equ_but->setContextMenuPolicy(Qt::DefaultContextMenu);
        change_equ_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_equ_but->setFlat(true);
        change_billinf_but = new QPushButton(Charging_monitoring);
        change_billinf_but->setObjectName(QString::fromUtf8("change_billinf_but"));
        change_billinf_but->setGeometry(QRect(30, 360, 98, 81));
        change_billinf_but->setFocusPolicy(Qt::StrongFocus);
        change_billinf_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_billinf_but->setFlat(true);
        charge_current = new QLineEdit(Charging_monitoring);
        charge_current->setObjectName(QString::fromUtf8("charge_current"));
        charge_current->setGeometry(QRect(632, 303, 96, 35));
        charge_current->setFont(font1);
        charge_power = new QLineEdit(Charging_monitoring);
        charge_power->setObjectName(QString::fromUtf8("charge_power"));
        charge_power->setGeometry(QRect(327, 389, 96, 37));
        charge_power->setFont(font1);
        charge_vol = new QLineEdit(Charging_monitoring);
        charge_vol->setObjectName(QString::fromUtf8("charge_vol"));
        charge_vol->setGeometry(QRect(632, 346, 96, 35));
        charge_vol->setFont(font1);
        bat_status = new QLineEdit(Charging_monitoring);
        bat_status->setObjectName(QString::fromUtf8("bat_status"));
        bat_status->setGeometry(QRect(328, 346, 96, 35));
        bat_status->setFont(font1);
        charge_time = new QLineEdit(Charging_monitoring);
        charge_time->setObjectName(QString::fromUtf8("charge_time"));
        charge_time->setGeometry(QRect(631, 389, 96, 37));
        charge_time->setFont(font1);
        charge_status = new QLineEdit(Charging_monitoring);
        charge_status->setObjectName(QString::fromUtf8("charge_status"));
        charge_status->setEnabled(true);
        charge_status->setGeometry(QRect(328, 303, 96, 35));
        charge_status->setFont(font1);
        soc_stop = new QPushButton(Charging_monitoring);
        soc_stop->setObjectName(QString::fromUtf8("soc_stop"));
        soc_stop->setGeometry(QRect(600, 210, 157, 58));
        soc_stop->setFocusPolicy(Qt::StrongFocus);
        soc_stop->setStyleSheet(QString::fromUtf8("background: transparent;"));
        soc_stop->setFlat(true);
        change_batinf_but = new QPushButton(Charging_monitoring);
        change_batinf_but->setObjectName(QString::fromUtf8("change_batinf_but"));
        change_batinf_but->setGeometry(QRect(30, 270, 98, 81));
        change_batinf_but->setFocusPolicy(Qt::StrongFocus);
        change_batinf_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_batinf_but->setFlat(true);

        retranslateUi(Charging_monitoring);

        QMetaObject::connectSlotsByName(Charging_monitoring);
    } // setupUi

    void retranslateUi(QWidget *Charging_monitoring)
    {
        Charging_monitoring->setWindowTitle(QApplication::translate("Charging_monitoring", "Form", 0));
        charge_monitoring->setText(QString());
        full_charge->setText(QString());
        full_charge_but->setText(QString());
        full_charge_but->setShortcut(QString());
        charge_7but->setText(QString());
        charge_6but->setText(QString());
        charge_5but->setText(QString());
        charge_4but->setText(QString());
        charge_3but->setText(QString());
        charge_2but->setText(QString());
        charge_1but->setText(QString());
        bat_soc->setText(QApplication::translate("Charging_monitoring", "100", 0));
        soc_set->setText(QApplication::translate("Charging_monitoring", "ok", 0));
        change_moni_but->setText(QString());
        change_equ_but->setText(QString());
        change_billinf_but->setText(QString());
        charge_current->setText(QApplication::translate("Charging_monitoring", "120", 0));
        charge_power->setText(QApplication::translate("Charging_monitoring", "60", 0));
        charge_vol->setText(QApplication::translate("Charging_monitoring", "500", 0));
        bat_status->setText(QApplication::translate("Charging_monitoring", "\346\255\243\345\270\270", 0));
        charge_time->setText(QApplication::translate("Charging_monitoring", "60", 0));
        charge_status->setText(QApplication::translate("Charging_monitoring", "\345\276\205\346\234\272", 0));
        soc_stop->setText(QString());
        change_batinf_but->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Charging_monitoring: public Ui_Charging_monitoring {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGING_MONITORING_H
