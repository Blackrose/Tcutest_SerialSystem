/********************************************************************************
** Form generated from reading UI file 'Charging-monitoring.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGING_2D_MONITORING_H
#define UI_CHARGING_2D_MONITORING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_charge
{
public:

    void setupUi(QWidget *charge)
    {
        if (charge->objectName().isEmpty())
            charge->setObjectName(QString::fromUtf8("charge"));
        charge->resize(800, 480);
        charge->setAutoFillBackground(false);
        charge->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/30.png)"));

        retranslateUi(charge);

        QMetaObject::connectSlotsByName(charge);
    } // setupUi

    void retranslateUi(QWidget *charge)
    {
        charge->setWindowTitle(QApplication::translate("charge", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class charge: public Ui_charge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGING_2D_MONITORING_H
