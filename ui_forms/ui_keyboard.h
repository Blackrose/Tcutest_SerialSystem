/********************************************************************************
** Form generated from reading UI file 'keyboard.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_H
#define UI_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGroupBox *groupBox;
    QPushButton *btn2;
    QPushButton *btnq;
    QPushButton *btn8;
    QPushButton *btn1;
    QPushButton *btn3;
    QPushButton *btn4;
    QPushButton *btn5;
    QPushButton *btn7;
    QPushButton *btn9;
    QPushButton *btn6;
    QPushButton *btn0;
    QPushButton *btno;
    QPushButton *btnt;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(262, 129);
        groupBox = new QGroupBox(Form);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 262, 130));
        groupBox->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 0, 0);\n"
""));
        btn2 = new QPushButton(groupBox);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setGeometry(QRect(110, 10, 41, 31));
        btnq = new QPushButton(groupBox);
        btnq->setObjectName(QString::fromUtf8("btnq"));
        btnq->setGeometry(QRect(210, 90, 41, 31));
        btn8 = new QPushButton(groupBox);
        btn8->setObjectName(QString::fromUtf8("btn8"));
        btn8->setGeometry(QRect(160, 50, 41, 31));
        btn1 = new QPushButton(groupBox);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(60, 10, 41, 31));
        btn3 = new QPushButton(groupBox);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        btn3->setGeometry(QRect(160, 10, 41, 31));
        btn4 = new QPushButton(groupBox);
        btn4->setObjectName(QString::fromUtf8("btn4"));
        btn4->setGeometry(QRect(210, 10, 41, 31));
        btn5 = new QPushButton(groupBox);
        btn5->setObjectName(QString::fromUtf8("btn5"));
        btn5->setGeometry(QRect(10, 50, 41, 31));
        btn7 = new QPushButton(groupBox);
        btn7->setObjectName(QString::fromUtf8("btn7"));
        btn7->setGeometry(QRect(110, 50, 41, 31));
        btn9 = new QPushButton(groupBox);
        btn9->setObjectName(QString::fromUtf8("btn9"));
        btn9->setGeometry(QRect(210, 50, 41, 31));
        btn6 = new QPushButton(groupBox);
        btn6->setObjectName(QString::fromUtf8("btn6"));
        btn6->setGeometry(QRect(60, 50, 41, 31));
        btn0 = new QPushButton(groupBox);
        btn0->setObjectName(QString::fromUtf8("btn0"));
        btn0->setGeometry(QRect(10, 10, 41, 31));
        btno = new QPushButton(groupBox);
        btno->setObjectName(QString::fromUtf8("btno"));
        btno->setGeometry(QRect(110, 90, 91, 31));
        btnt = new QPushButton(groupBox);
        btnt->setObjectName(QString::fromUtf8("btnt"));
        btnt->setGeometry(QRect(10, 90, 91, 31));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        groupBox->setTitle(QString());
        btn2->setText(QApplication::translate("Form", "2", 0));
        btnq->setText(QApplication::translate("Form", "\345\217\226\346\266\210", 0));
        btn8->setText(QApplication::translate("Form", "8", 0));
        btn1->setText(QApplication::translate("Form", "1", 0));
        btn3->setText(QApplication::translate("Form", "3", 0));
        btn4->setText(QApplication::translate("Form", "4", 0));
        btn5->setText(QApplication::translate("Form", "5", 0));
        btn7->setText(QApplication::translate("Form", "7", 0));
        btn9->setText(QApplication::translate("Form", "9", 0));
        btn6->setText(QApplication::translate("Form", "6", 0));
        btn0->setText(QApplication::translate("Form", "0", 0));
        btno->setText(QApplication::translate("Form", "\347\241\256 \345\256\232", 0));
        btnt->setText(QApplication::translate("Form", "\351\200\200 \346\240\274", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
