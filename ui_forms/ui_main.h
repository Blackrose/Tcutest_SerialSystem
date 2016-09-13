/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QPushButton *auto_but;
    QLabel *label;
    QPushButton *report_but;
    QPushButton *manual_but;
    QPushButton *test;
    QLabel *label_2;
    QPushButton *back_but;
    QLabel *main_gif;
    QDateTimeEdit *dateTimeEdit;

    void setupUi(QWidget *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(800, 480);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/images/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainForm->setWindowIcon(icon);
        MainForm->setAutoFillBackground(false);
        MainForm->setStyleSheet(QString::fromUtf8(""));
        auto_but = new QPushButton(MainForm);
        auto_but->setObjectName(QString::fromUtf8("auto_but"));
        auto_but->setGeometry(QRect(90, 130, 99, 51));
        auto_but->setStyleSheet(QString::fromUtf8("background-image:url()"));
        label = new QLabel(MainForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 20, 171, 51));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-image:url()"));
        report_but = new QPushButton(MainForm);
        report_but->setObjectName(QString::fromUtf8("report_but"));
        report_but->setGeometry(QRect(500, 130, 91, 51));
        report_but->setStyleSheet(QString::fromUtf8("background-image:url()"));
        manual_but = new QPushButton(MainForm);
        manual_but->setObjectName(QString::fromUtf8("manual_but"));
        manual_but->setGeometry(QRect(300, 130, 99, 51));
        manual_but->setStyleSheet(QString::fromUtf8("background-image:url()"));
        test = new QPushButton(MainForm);
        test->setObjectName(QString::fromUtf8("test"));
        test->setGeometry(QRect(80, 330, 91, 51));
        test->setStyleSheet(QString::fromUtf8("border:4px groove gray;border-radius:10px;padding:10px;background-image:url();"));
        label_2 = new QLabel(MainForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(590, 0, 191, 71));
        label_2->setAutoFillBackground(false);
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/serial_logo.png)"));
        back_but = new QPushButton(MainForm);
        back_but->setObjectName(QString::fromUtf8("back_but"));
        back_but->setGeometry(QRect(630, 380, 99, 41));
        back_but->setStyleSheet(QString::fromUtf8("background-image:url()"));
        main_gif = new QLabel(MainForm);
        main_gif->setObjectName(QString::fromUtf8("main_gif"));
        main_gif->setGeometry(QRect(500, 330, 121, 21));
        main_gif->setAutoFillBackground(true);
        main_gif->setStyleSheet(QString::fromUtf8(""));
        dateTimeEdit = new QDateTimeEdit(MainForm);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setGeometry(QRect(153, 280, 291, 41));
        dateTimeEdit->setCurrentSection(QDateTimeEdit::YearSection);
        dateTimeEdit->setCalendarPopup(false);
        dateTimeEdit->setTimeSpec(Qt::LocalTime);

        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QWidget *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "\344\270\273\347\252\227\344\275\223", 0));
        auto_but->setText(QApplication::translate("MainForm", "\350\207\252\345\212\250\346\265\213\350\257\225", 0));
        label->setText(QApplication::translate("MainForm", "SerialSystem_Test", 0));
        report_but->setText(QApplication::translate("MainForm", "\346\265\213\350\257\225\346\212\245\345\221\212", 0));
        manual_but->setText(QApplication::translate("MainForm", "\346\211\213\345\212\250\346\265\213\350\257\225", 0));
        test->setText(QApplication::translate("MainForm", "\346\265\213\350\257\225\346\212\245\345\221\212", 0));
        label_2->setText(QString());
        back_but->setText(QApplication::translate("MainForm", "Back", 0));
        main_gif->setText(QApplication::translate("MainForm", "TextLabel", 0));
        dateTimeEdit->setDisplayFormat(QApplication::translate("MainForm", "yyyy\345\271\264MM\346\234\210dd\346\227\245 HH \346\227\266 mm \345\210\206 ss \347\247\222", 0));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
