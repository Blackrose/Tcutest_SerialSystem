/********************************************************************************
** Form generated from reading UI file 'test_manual.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_MANUAL_H
#define UI_TEST_MANUAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test_Manual
{
public:
    QPushButton *back_but;
    QLabel *label;
    QLabel *label_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *touch_but;
    QSpacerItem *horizontalSpacer;
    QPushButton *Card_but;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *gprs_but;
    QPushButton *gps_but;
    QPushButton *Emeter_but;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QPushButton *network_but;
    QPushButton *Canbus_but;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *u_sd_but;
    QPushButton *rtc_but;
    QPushButton *pwm_but;
    QPushButton *power_but;
    QPushButton *sam_but;

    void setupUi(QWidget *test_Manual)
    {
        if (test_Manual->objectName().isEmpty())
            test_Manual->setObjectName(QString::fromUtf8("test_Manual"));
        test_Manual->resize(800, 480);
        test_Manual->setStyleSheet(QString::fromUtf8(""));
        back_but = new QPushButton(test_Manual);
        back_but->setObjectName(QString::fromUtf8("back_but"));
        back_but->setGeometry(QRect(630, 380, 99, 41));
        back_but->setStyleSheet(QString::fromUtf8("background-image:url()"));
        label = new QLabel(test_Manual);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 20, 171, 51));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-image:url()"));
        label_2 = new QLabel(test_Manual);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(590, 0, 191, 71));
        label_2->setStyleSheet(QString::fromUtf8("background-image: url(:/img/images/serial_logo.png)"));
        layoutWidget = new QWidget(test_Manual);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 100, 631, 271));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        touch_but = new QPushButton(layoutWidget);
        touch_but->setObjectName(QString::fromUtf8("touch_but"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(touch_but->sizePolicy().hasHeightForWidth());
        touch_but->setSizePolicy(sizePolicy);
        touch_but->setMaximumSize(QSize(649, 16777215));
        touch_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(touch_but, 2, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        Card_but = new QPushButton(layoutWidget);
        Card_but->setObjectName(QString::fromUtf8("Card_but"));
        sizePolicy.setHeightForWidth(Card_but->sizePolicy().hasHeightForWidth());
        Card_but->setSizePolicy(sizePolicy);
        Card_but->setMaximumSize(QSize(649, 16777215));
        Card_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(Card_but, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 5, 1, 1);

        gprs_but = new QPushButton(layoutWidget);
        gprs_but->setObjectName(QString::fromUtf8("gprs_but"));
        sizePolicy.setHeightForWidth(gprs_but->sizePolicy().hasHeightForWidth());
        gprs_but->setSizePolicy(sizePolicy);
        gprs_but->setMaximumSize(QSize(649, 16777215));
        gprs_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(gprs_but, 0, 8, 1, 1);

        gps_but = new QPushButton(layoutWidget);
        gps_but->setObjectName(QString::fromUtf8("gps_but"));
        sizePolicy.setHeightForWidth(gps_but->sizePolicy().hasHeightForWidth());
        gps_but->setSizePolicy(sizePolicy);
        gps_but->setMaximumSize(QSize(649, 16777215));
        gps_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(gps_but, 0, 6, 1, 1);

        Emeter_but = new QPushButton(layoutWidget);
        Emeter_but->setObjectName(QString::fromUtf8("Emeter_but"));
        sizePolicy.setHeightForWidth(Emeter_but->sizePolicy().hasHeightForWidth());
        Emeter_but->setSizePolicy(sizePolicy);
        Emeter_but->setMaximumSize(QSize(649, 16777215));
        Emeter_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(Emeter_but, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        network_but = new QPushButton(layoutWidget);
        network_but->setObjectName(QString::fromUtf8("network_but"));
        sizePolicy.setHeightForWidth(network_but->sizePolicy().hasHeightForWidth());
        network_but->setSizePolicy(sizePolicy);
        network_but->setMaximumSize(QSize(649, 16777215));
        network_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(network_but, 2, 0, 1, 1);

        Canbus_but = new QPushButton(layoutWidget);
        Canbus_but->setObjectName(QString::fromUtf8("Canbus_but"));
        sizePolicy.setHeightForWidth(Canbus_but->sizePolicy().hasHeightForWidth());
        Canbus_but->setSizePolicy(sizePolicy);
        Canbus_but->setMaximumSize(QSize(649, 16777215));
        Canbus_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(Canbus_but, 0, 4, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 7, 1, 1);

        u_sd_but = new QPushButton(layoutWidget);
        u_sd_but->setObjectName(QString::fromUtf8("u_sd_but"));
        sizePolicy.setHeightForWidth(u_sd_but->sizePolicy().hasHeightForWidth());
        u_sd_but->setSizePolicy(sizePolicy);
        u_sd_but->setMaximumSize(QSize(649, 16777215));
        u_sd_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(u_sd_but, 4, 6, 1, 1);

        rtc_but = new QPushButton(layoutWidget);
        rtc_but->setObjectName(QString::fromUtf8("rtc_but"));
        sizePolicy.setHeightForWidth(rtc_but->sizePolicy().hasHeightForWidth());
        rtc_but->setSizePolicy(sizePolicy);
        rtc_but->setMaximumSize(QSize(649, 16777215));
        rtc_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(rtc_but, 2, 2, 1, 1);

        pwm_but = new QPushButton(layoutWidget);
        pwm_but->setObjectName(QString::fromUtf8("pwm_but"));
        sizePolicy.setHeightForWidth(pwm_but->sizePolicy().hasHeightForWidth());
        pwm_but->setSizePolicy(sizePolicy);
        pwm_but->setMaximumSize(QSize(649, 16777215));
        pwm_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(pwm_but, 2, 6, 1, 1);

        power_but = new QPushButton(layoutWidget);
        power_but->setObjectName(QString::fromUtf8("power_but"));
        sizePolicy.setHeightForWidth(power_but->sizePolicy().hasHeightForWidth());
        power_but->setSizePolicy(sizePolicy);
        power_but->setMaximumSize(QSize(649, 16777215));
        power_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(power_but, 2, 8, 1, 1);

        sam_but = new QPushButton(layoutWidget);
        sam_but->setObjectName(QString::fromUtf8("sam_but"));
        sizePolicy.setHeightForWidth(sam_but->sizePolicy().hasHeightForWidth());
        sam_but->setSizePolicy(sizePolicy);
        sam_but->setMaximumSize(QSize(649, 16777215));
        sam_but->setStyleSheet(QString::fromUtf8("background-image:url()"));

        gridLayout->addWidget(sam_but, 4, 2, 1, 1);


        retranslateUi(test_Manual);

        QMetaObject::connectSlotsByName(test_Manual);
    } // setupUi

    void retranslateUi(QWidget *test_Manual)
    {
        test_Manual->setWindowTitle(QApplication::translate("test_Manual", "Form", 0));
        back_but->setText(QApplication::translate("test_Manual", "Back", 0));
        label->setText(QApplication::translate("test_Manual", "SerialSystem_Test", 0));
        label_2->setText(QString());
        touch_but->setText(QApplication::translate("test_Manual", "\345\261\217\345\271\225\346\240\241\345\207\206", 0));
        Card_but->setText(QApplication::translate("test_Manual", "\345\210\267\345\215\241\345\231\250", 0));
        gprs_but->setText(QApplication::translate("test_Manual", "GPRS/SIM", 0));
        gps_but->setText(QApplication::translate("test_Manual", "GPS", 0));
        Emeter_but->setText(QApplication::translate("test_Manual", "\347\224\265\350\203\275\350\241\250", 0));
        network_but->setText(QApplication::translate("test_Manual", "\347\275\221\347\273\234", 0));
        Canbus_but->setText(QApplication::translate("test_Manual", "Can\351\200\232\350\256\257", 0));
        u_sd_but->setText(QApplication::translate("test_Manual", "U\347\233\230/SD\345\215\241", 0));
        rtc_but->setText(QApplication::translate("test_Manual", "RTC", 0));
        pwm_but->setText(QApplication::translate("test_Manual", "\350\234\202\351\270\243\345\231\250/\350\200\263\346\234\272", 0));
        power_but->setText(QApplication::translate("test_Manual", "\346\216\211\347\224\265\346\243\200\346\265\213", 0));
        sam_but->setText(QApplication::translate("test_Manual", "ESAM/PSAM", 0));
    } // retranslateUi

};

namespace Ui {
    class test_Manual: public Ui_test_Manual {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_MANUAL_H
