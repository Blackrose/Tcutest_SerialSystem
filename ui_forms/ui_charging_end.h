/********************************************************************************
** Form generated from reading UI file 'charging_end.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGING_END_H
#define UI_CHARGING_END_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_charging_end
{
public:
    QLabel *label;

    void setupUi(QWidget *charging_end)
    {
        if (charging_end->objectName().isEmpty())
            charging_end->setObjectName(QString::fromUtf8("charging_end"));
        charging_end->resize(800, 480);
        label = new QLabel(charging_end);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 480));
        label->setAutoFillBackground(false);
        label->setStyleSheet(QString::fromUtf8("border-image:url(:/img/images/C6_B2.png)"));

        retranslateUi(charging_end);

        QMetaObject::connectSlotsByName(charging_end);
    } // setupUi

    void retranslateUi(QWidget *charging_end)
    {
        charging_end->setWindowTitle(QApplication::translate("charging_end", "Form", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class charging_end: public Ui_charging_end {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGING_END_H
