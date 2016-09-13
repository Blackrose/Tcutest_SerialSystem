/********************************************************************************
** Form generated from reading UI file 'equipment_testing.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EQUIPMENT_TESTING_H
#define UI_EQUIPMENT_TESTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_equipment_testing
{
public:
    QLabel *label;
    QLabel *logo;
    QProgressBar *progressBar;
    QPushButton *back_but;

    void setupUi(QWidget *equipment_testing)
    {
        if (equipment_testing->objectName().isEmpty())
            equipment_testing->setObjectName(QString::fromUtf8("equipment_testing"));
        equipment_testing->resize(800, 480);
        equipment_testing->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(equipment_testing);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 800, 480));
        label->setStyleSheet(QString::fromUtf8("background:url(:/img/images/mmexport1464230866608.png)"));
        logo = new QLabel(equipment_testing);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setGeometry(QRect(590, 0, 191, 71));
        logo->setAutoFillBackground(false);
        logo->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/serial_logo.png)"));
        progressBar = new QProgressBar(equipment_testing);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(240, 290, 331, 23));
        progressBar->setAutoFillBackground(false);
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar:horizontal {\n"
"border: 1px solid gray;\n"
"border-radius: 3px;\n"
"background: white;\n"
"padding: 1px;\n"
"}\n"
"QProgressBar::chunk {\n"
"   background-color: #6893b3;\n"
"   width: 20px;\n"
"}\n"
"\n"
"QProgressBar {\n"
"   border: 2px solid grey;\n"
"   border-radius: 5px;\n"
"   text-align: center;\n"
"}"));
        progressBar->setValue(0);
        back_but = new QPushButton(equipment_testing);
        back_but->setObjectName(QString::fromUtf8("back_but"));
        back_but->setGeometry(QRect(0, 0, 191, 63));
        back_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        back_but->setFlat(true);

        retranslateUi(equipment_testing);

        QMetaObject::connectSlotsByName(equipment_testing);
    } // setupUi

    void retranslateUi(QWidget *equipment_testing)
    {
        equipment_testing->setWindowTitle(QApplication::translate("equipment_testing", "Form", 0));
        label->setText(QString());
        logo->setText(QString());
        back_but->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class equipment_testing: public Ui_equipment_testing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUIPMENT_TESTING_H
