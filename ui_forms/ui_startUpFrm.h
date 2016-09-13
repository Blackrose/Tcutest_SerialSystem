/********************************************************************************
** Form generated from reading UI file 'startUpFrm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTUPFRM_H
#define UI_STARTUPFRM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_startUpFrm
{
public:
    QProgressBar *progressBar;

    void setupUi(QWidget *startUpFrm)
    {
        if (startUpFrm->objectName().isEmpty())
            startUpFrm->setObjectName(QString::fromUtf8("startUpFrm"));
        startUpFrm->setWindowModality(Qt::NonModal);
        startUpFrm->resize(801, 481);
        startUpFrm->setCursor(QCursor(Qt::WaitCursor));
        startUpFrm->setAutoFillBackground(false);
        startUpFrm->setStyleSheet(QString::fromUtf8("background-color: rgb(91, 91, 91);"));
        progressBar = new QProgressBar(startUpFrm);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(200, 230, 401, 23));
        progressBar->setCursor(QCursor(Qt::WaitCursor));
        progressBar->setMouseTracking(false);
        progressBar->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        progressBar->setMinimum(0);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::BottomToTop);

        retranslateUi(startUpFrm);

        QMetaObject::connectSlotsByName(startUpFrm);
    } // setupUi

    void retranslateUi(QWidget *startUpFrm)
    {
        startUpFrm->setWindowTitle(QApplication::translate("startUpFrm", "Form", 0));
        progressBar->setFormat(QApplication::translate("startUpFrm", "%p%", 0));
    } // retranslateUi

};

namespace Ui {
    class startUpFrm: public Ui_startUpFrm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTUPFRM_H
