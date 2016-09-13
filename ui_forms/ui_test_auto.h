/********************************************************************************
** Form generated from reading UI file 'test_auto.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_AUTO_H
#define UI_TEST_AUTO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test_auto
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *back_but;

    void setupUi(QWidget *test_auto)
    {
        if (test_auto->objectName().isEmpty())
            test_auto->setObjectName(QString::fromUtf8("test_auto"));
        test_auto->resize(800, 480);
        test_auto->setAutoFillBackground(true);
        test_auto->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(test_auto);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 20, 171, 51));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8(""));
        label_2 = new QLabel(test_auto);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(590, 0, 191, 71));
        label_2->setAutoFillBackground(false);
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/serial_logo.png)"));
        back_but = new QPushButton(test_auto);
        back_but->setObjectName(QString::fromUtf8("back_but"));
        back_but->setGeometry(QRect(630, 380, 99, 41));
        back_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        retranslateUi(test_auto);

        QMetaObject::connectSlotsByName(test_auto);
    } // setupUi

    void retranslateUi(QWidget *test_auto)
    {
        test_auto->setWindowTitle(QApplication::translate("test_auto", "Form", 0));
        label->setText(QApplication::translate("test_auto", "SerialSystem_Test", 0));
        label_2->setText(QString());
        back_but->setText(QApplication::translate("test_auto", "Back", 0));
    } // retranslateUi

};

namespace Ui {
    class test_auto: public Ui_test_auto {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_AUTO_H
