/********************************************************************************
** Form generated from reading UI file 'secondwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDWINDOW_H
#define UI_SECONDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SecondWindow
{
public:
    QWidget *centralwidget;
    QLabel *main_gif;
    QPushButton *back_but;

    void setupUi(QMainWindow *SecondWindow)
    {
        if (SecondWindow->objectName().isEmpty())
            SecondWindow->setObjectName(QString::fromUtf8("SecondWindow"));
        SecondWindow->resize(800, 480);
        SecondWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(SecondWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        centralwidget->setAutoFillBackground(false);
        main_gif = new QLabel(centralwidget);
        main_gif->setObjectName(QString::fromUtf8("main_gif"));
        main_gif->setGeometry(QRect(0, 50, 771, 371));
        main_gif->setAutoFillBackground(true);
        main_gif->setStyleSheet(QString::fromUtf8("background-image:url(); "));
        back_but = new QPushButton(centralwidget);
        back_but->setObjectName(QString::fromUtf8("back_but"));
        back_but->setGeometry(QRect(690, 430, 99, 41));
        back_but->setStyleSheet(QString::fromUtf8("background-image:url()"));
        SecondWindow->setCentralWidget(centralwidget);

        retranslateUi(SecondWindow);

        QMetaObject::connectSlotsByName(SecondWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SecondWindow)
    {
        SecondWindow->setWindowTitle(QApplication::translate("SecondWindow", "MainWindow", 0));
        main_gif->setText(QApplication::translate("SecondWindow", "TextLabel", 0));
        back_but->setText(QApplication::translate("SecondWindow", "Back", 0));
    } // retranslateUi

};

namespace Ui {
    class SecondWindow: public Ui_SecondWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDWINDOW_H
