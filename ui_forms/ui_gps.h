/********************************************************************************
** Form generated from reading UI file 'gps.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GPS_H
#define UI_GPS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gps
{
public:
    QLabel *logo;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QComboBox *cmb_com;
    QLabel *label;
    QComboBox *cmb_bound;
    QPushButton *pb_read;
    QPushButton *pb_close;
    QTextEdit *tedit_output;
    QPushButton *back_but;

    void setupUi(QWidget *gps)
    {
        if (gps->objectName().isEmpty())
            gps->setObjectName(QString::fromUtf8("gps"));
        gps->resize(800, 480);
        gps->setStyleSheet(QString::fromUtf8(""));
        logo = new QLabel(gps);
        logo->setObjectName(QString::fromUtf8("logo"));
        logo->setGeometry(QRect(590, 0, 191, 71));
        logo->setMinimumSize(QSize(191, 71));
        logo->setMaximumSize(QSize(191, 71));
        logo->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/serial_logo.png)"));
        groupBox = new QGroupBox(gps);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 89, 761, 371));
        groupBox->setFlat(false);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        cmb_com = new QComboBox(groupBox);
        cmb_com->setObjectName(QString::fromUtf8("cmb_com"));
        sizePolicy.setHeightForWidth(cmb_com->sizePolicy().hasHeightForWidth());
        cmb_com->setSizePolicy(sizePolicy);

        gridLayout->addWidget(cmb_com, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 0, 2, 1, 1);

        cmb_bound = new QComboBox(groupBox);
        cmb_bound->setObjectName(QString::fromUtf8("cmb_bound"));
        sizePolicy.setHeightForWidth(cmb_bound->sizePolicy().hasHeightForWidth());
        cmb_bound->setSizePolicy(sizePolicy);

        gridLayout->addWidget(cmb_bound, 0, 3, 1, 1);

        pb_read = new QPushButton(groupBox);
        pb_read->setObjectName(QString::fromUtf8("pb_read"));

        gridLayout->addWidget(pb_read, 0, 4, 1, 1);

        pb_close = new QPushButton(groupBox);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));

        gridLayout->addWidget(pb_close, 0, 5, 1, 1);

        tedit_output = new QTextEdit(groupBox);
        tedit_output->setObjectName(QString::fromUtf8("tedit_output"));

        gridLayout->addWidget(tedit_output, 1, 0, 1, 6);

        back_but = new QPushButton(gps);
        back_but->setObjectName(QString::fromUtf8("back_but"));
        back_but->setGeometry(QRect(20, 20, 121, 41));
        back_but->setFocusPolicy(Qt::ClickFocus);
        back_but->setStyleSheet(QString::fromUtf8("background: transparent;"));
        back_but->setFlat(true);

        retranslateUi(gps);

        cmb_com->setCurrentIndex(5);
        cmb_bound->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(gps);
    } // setupUi

    void retranslateUi(QWidget *gps)
    {
        gps->setWindowTitle(QApplication::translate("gps", "gps", 0));
        logo->setText(QString());
        groupBox->setTitle(QApplication::translate("gps", "GPS", 0));
        label_2->setText(QApplication::translate("gps", "         com  : ", 0));
        cmb_com->clear();
        cmb_com->insertItems(0, QStringList()
         << QApplication::translate("gps", "ttyO0", 0)
         << QApplication::translate("gps", "ttyO1", 0)
         << QApplication::translate("gps", "ttyO2", 0)
         << QApplication::translate("gps", "ttyO3", 0)
         << QApplication::translate("gps", "ttyO4", 0)
         << QApplication::translate("gps", "ttyUSB1", 0)
        );
        label->setText(QApplication::translate("gps", "        bound: ", 0));
        cmb_bound->clear();
        cmb_bound->insertItems(0, QStringList()
         << QApplication::translate("gps", "4800", 0)
         << QApplication::translate("gps", "9600", 0)
         << QApplication::translate("gps", "19200", 0)
         << QApplication::translate("gps", "115200", 0)
        );
        pb_read->setText(QApplication::translate("gps", "read", 0));
        pb_close->setText(QApplication::translate("gps", "stop", 0));
        back_but->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class gps: public Ui_gps {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GPS_H
