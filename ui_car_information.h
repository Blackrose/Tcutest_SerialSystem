/********************************************************************************
** Form generated from reading UI file 'car_information.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAR_INFORMATION_H
#define UI_CAR_INFORMATION_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Car_information
{
public:
    QLabel *label;
    QPushButton *change_equ_but;
    QPushButton *change_moni_but;
    QPushButton *change_end_but;
    QPushButton *change_carinf_but;

    void setupUi(QWidget *Car_information)
    {
        if (Car_information->objectName().isEmpty())
            Car_information->setObjectName(QString::fromUtf8("Car_information"));
        Car_information->resize(800, 480);
        label = new QLabel(Car_information);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 480));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/31.png)"));
        change_equ_but = new QPushButton(Car_information);
        change_equ_but->setObjectName(QString::fromUtf8("change_equ_but"));
        change_equ_but->setGeometry(QRect(30, 190, 98, 81));
        change_equ_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_equ_but->setFlat(true);
        change_moni_but = new QPushButton(Car_information);
        change_moni_but->setObjectName(QString::fromUtf8("change_moni_but"));
        change_moni_but->setGeometry(QRect(28, 98, 98, 81));
        change_moni_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_moni_but->setFlat(true);
        change_end_but = new QPushButton(Car_information);
        change_end_but->setObjectName(QString::fromUtf8("change_end_but"));
        change_end_but->setGeometry(QRect(30, 360, 98, 81));
        change_end_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_end_but->setFlat(true);
        change_carinf_but = new QPushButton(Car_information);
        change_carinf_but->setObjectName(QString::fromUtf8("change_carinf_but"));
        change_carinf_but->setGeometry(QRect(30, 270, 98, 81));
        change_carinf_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        change_carinf_but->setFlat(true);

        retranslateUi(Car_information);

        QMetaObject::connectSlotsByName(Car_information);
    } // setupUi

    void retranslateUi(QWidget *Car_information)
    {
        Car_information->setWindowTitle(QApplication::translate("Car_information", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        change_equ_but->setText(QString());
        change_moni_but->setText(QString());
        change_end_but->setText(QString());
        change_carinf_but->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Car_information: public Ui_Car_information {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAR_INFORMATION_H
