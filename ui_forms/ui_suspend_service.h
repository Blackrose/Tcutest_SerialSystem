/********************************************************************************
** Form generated from reading UI file 'suspend_service.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUSPEND_SERVICE_H
#define UI_SUSPEND_SERVICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_suspend_service
{
public:

    void setupUi(QWidget *suspend_service)
    {
        if (suspend_service->objectName().isEmpty())
            suspend_service->setObjectName(QString::fromUtf8("suspend_service"));
        suspend_service->resize(800, 480);
        suspend_service->setAutoFillBackground(true);
        suspend_service->setStyleSheet(QString::fromUtf8("background:url(:/img/images/G1.png)"));

        retranslateUi(suspend_service);

        QMetaObject::connectSlotsByName(suspend_service);
    } // setupUi

    void retranslateUi(QWidget *suspend_service)
    {
        suspend_service->setWindowTitle(QApplication::translate("suspend_service", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class suspend_service: public Ui_suspend_service {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUSPEND_SERVICE_H
