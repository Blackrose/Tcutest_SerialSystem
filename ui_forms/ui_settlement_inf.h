/********************************************************************************
** Form generated from reading UI file 'settlement_inf.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTLEMENT_INF_H
#define UI_SETTLEMENT_INF_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settlement_inf
{
public:
    QLabel *label;

    void setupUi(QWidget *settlement_inf)
    {
        if (settlement_inf->objectName().isEmpty())
            settlement_inf->setObjectName(QString::fromUtf8("settlement_inf"));
        settlement_inf->resize(800, 480);
        settlement_inf->setCursor(QCursor(Qt::ArrowCursor));
        settlement_inf->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(settlement_inf);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 480));
        label->setStyleSheet(QString::fromUtf8("background:url(:/img/images/F7main.png)"));

        retranslateUi(settlement_inf);

        QMetaObject::connectSlotsByName(settlement_inf);
    } // setupUi

    void retranslateUi(QWidget *settlement_inf)
    {
        settlement_inf->setWindowTitle(QApplication::translate("settlement_inf", "Form", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class settlement_inf: public Ui_settlement_inf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTLEMENT_INF_H
