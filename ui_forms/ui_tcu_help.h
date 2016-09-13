/********************************************************************************
** Form generated from reading UI file 'tcu_help.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCU_HELP_H
#define UI_TCU_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_tcu_help
{
public:
    QLabel *label;

    void setupUi(QWidget *tcu_help)
    {
        if (tcu_help->objectName().isEmpty())
            tcu_help->setObjectName(QString::fromUtf8("tcu_help"));
        tcu_help->resize(800, 480);
        label = new QLabel(tcu_help);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 480));
        label->setStyleSheet(QString::fromUtf8("background:url(:/img/images/mmexport1464230738224.png)"));

        retranslateUi(tcu_help);

        QMetaObject::connectSlotsByName(tcu_help);
    } // setupUi

    void retranslateUi(QWidget *tcu_help)
    {
        tcu_help->setWindowTitle(QApplication::translate("tcu_help", "Form", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class tcu_help: public Ui_tcu_help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCU_HELP_H
