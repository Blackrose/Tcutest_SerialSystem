/********************************************************************************
** Form generated from reading UI file 'Emter_window.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMTER_WINDOW_H
#define UI_EMTER_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmterWindow
{
public:
    QAction *actionAdd;
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionSave;
    QAction *actionClearBytes;
    QAction *actionLoadfile;
    QAction *actionCleanPort;
    QAction *actionWriteToFile;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *portNameComboBox;
    QLabel *label_2;
    QComboBox *baudRateComboBox;
    QLabel *label_3;
    QComboBox *dataBitsComboBox;
    QLabel *label_4;
    QComboBox *parityComboBox;
    QLabel *label_5;
    QComboBox *stopBitsComboBox;
    QSpacerItem *verticalSpacer;
    QCheckBox *obocheckBox;
    QLabel *label_6;
    QSpinBox *delayspinBox;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_5;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *chradioButton;
    QLCDNumber *recvbyteslcdNumber;
    QPushButton *clearUpBtn;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QTextBrowser *analyse_rev;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *sendcomboBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_8;
    QLineEdit *RulerID;
    QLabel *label_9;
    QComboBox *addrcomboBox;
    QComboBox *dircomboBox;
    QLCDNumber *sendbyteslcdNumber;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *sendAsHexcheckBox;
    QLineEdit *sendMsgLineEdit;
    QPushButton *sendmsgBtn;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EmterWindow)
    {
        if (EmterWindow->objectName().isEmpty())
            EmterWindow->setObjectName(QString::fromUtf8("EmterWindow"));
        EmterWindow->setEnabled(true);
        EmterWindow->resize(800, 480);
        EmterWindow->setMinimumSize(QSize(800, 480));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(9);
        EmterWindow->setFont(font);
        EmterWindow->setCursor(QCursor(Qt::PointingHandCursor));
        EmterWindow->setContextMenuPolicy(Qt::NoContextMenu);
        EmterWindow->setStyleSheet(QString::fromUtf8("QDialog{background:rgb(229, 255, 239)}\n"
"QStatusBar{background:url(:/images/header.bmp)}\n"
"QPushButton{background:url(:/images/header.bmp)}\n"
"QLCDNumber{background:url(:/images/lcd.bmp)}\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"\n"
""));
        EmterWindow->setIconSize(QSize(16, 16));
        EmterWindow->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        EmterWindow->setAnimated(true);
        actionAdd = new QAction(EmterWindow);
        actionAdd->setObjectName(QString::fromUtf8("actionAdd"));
        actionAdd->setCheckable(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAdd->setIcon(icon);
        actionOpen = new QAction(EmterWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionClose = new QAction(EmterWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClose->setIcon(icon2);
        actionExit = new QAction(EmterWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionAbout = new QAction(EmterWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/mesage.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon4);
        actionSave = new QAction(EmterWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon5);
        actionClearBytes = new QAction(EmterWindow);
        actionClearBytes->setObjectName(QString::fromUtf8("actionClearBytes"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/clearbytes.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClearBytes->setIcon(icon6);
        actionLoadfile = new QAction(EmterWindow);
        actionLoadfile->setObjectName(QString::fromUtf8("actionLoadfile"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/loadfile.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoadfile->setIcon(icon7);
        actionCleanPort = new QAction(EmterWindow);
        actionCleanPort->setObjectName(QString::fromUtf8("actionCleanPort"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/cleanport.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCleanPort->setIcon(icon8);
        actionWriteToFile = new QAction(EmterWindow);
        actionWriteToFile->setObjectName(QString::fromUtf8("actionWriteToFile"));
        actionWriteToFile->setCheckable(true);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/images/write2file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWriteToFile->setIcon(icon9);
        centralWidget = new QWidget(EmterWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        groupBox->setFlat(false);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label);

        portNameComboBox = new QComboBox(groupBox);
        portNameComboBox->setObjectName(QString::fromUtf8("portNameComboBox"));

        verticalLayout->addWidget(portNameComboBox);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_2);

        baudRateComboBox = new QComboBox(groupBox);
        baudRateComboBox->setObjectName(QString::fromUtf8("baudRateComboBox"));

        verticalLayout->addWidget(baudRateComboBox);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_3);

        dataBitsComboBox = new QComboBox(groupBox);
        dataBitsComboBox->setObjectName(QString::fromUtf8("dataBitsComboBox"));

        verticalLayout->addWidget(dataBitsComboBox);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_4);

        parityComboBox = new QComboBox(groupBox);
        parityComboBox->setObjectName(QString::fromUtf8("parityComboBox"));

        verticalLayout->addWidget(parityComboBox);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_5);

        stopBitsComboBox = new QComboBox(groupBox);
        stopBitsComboBox->setObjectName(QString::fromUtf8("stopBitsComboBox"));

        verticalLayout->addWidget(stopBitsComboBox);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        obocheckBox = new QCheckBox(groupBox);
        obocheckBox->setObjectName(QString::fromUtf8("obocheckBox"));

        verticalLayout->addWidget(obocheckBox);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_6);

        delayspinBox = new QSpinBox(groupBox);
        delayspinBox->setObjectName(QString::fromUtf8("delayspinBox"));
        delayspinBox->setMinimum(10);
        delayspinBox->setMaximum(5000);
        delayspinBox->setValue(200);

        verticalLayout->addWidget(delayspinBox);


        gridLayout->addWidget(groupBox, 0, 0, 2, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 300));
        groupBox_2->setMaximumSize(QSize(350, 16777215));
        groupBox_2->setStyleSheet(QString::fromUtf8(""));
        groupBox_2->setFlat(true);
        verticalLayout_5 = new QVBoxLayout(groupBox_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        frame_3 = new QFrame(groupBox_2);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMinimumSize(QSize(0, 264));
        frame_3->setMaximumSize(QSize(16777215, 264));
        frame_3->setStyleSheet(QString::fromUtf8(""));
        frame_3->setFrameShape(QFrame::WinPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_3->setLineWidth(1);
        frame_3->setMidLineWidth(0);
        verticalLayout_3 = new QVBoxLayout(frame_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chradioButton = new QRadioButton(frame_3);
        chradioButton->setObjectName(QString::fromUtf8("chradioButton"));
        chradioButton->setChecked(true);

        horizontalLayout->addWidget(chradioButton);

        recvbyteslcdNumber = new QLCDNumber(frame_3);
        recvbyteslcdNumber->setObjectName(QString::fromUtf8("recvbyteslcdNumber"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(recvbyteslcdNumber->sizePolicy().hasHeightForWidth());
        recvbyteslcdNumber->setSizePolicy(sizePolicy1);
        recvbyteslcdNumber->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(recvbyteslcdNumber);

        clearUpBtn = new QPushButton(frame_3);
        clearUpBtn->setObjectName(QString::fromUtf8("clearUpBtn"));
        clearUpBtn->setMinimumSize(QSize(0, 23));
        clearUpBtn->setMaximumSize(QSize(60, 23));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/images/edit-clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        clearUpBtn->setIcon(icon10);

        horizontalLayout->addWidget(clearUpBtn);


        verticalLayout_2->addLayout(horizontalLayout);

        textBrowser = new QTextBrowser(frame_3);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_5->addWidget(frame_3);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 0));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        frame = new QFrame(groupBox_3);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(280, 264));
        frame->setMaximumSize(QSize(16777215, 264));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        analyse_rev = new QTextBrowser(frame);
        analyse_rev->setObjectName(QString::fromUtf8("analyse_rev"));

        gridLayout_2->addWidget(analyse_rev, 0, 0, 1, 1);


        verticalLayout_4->addWidget(frame);


        gridLayout->addWidget(groupBox_3, 0, 2, 1, 1);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setStyleSheet(QString::fromUtf8(""));
        groupBox_4->setFlat(true);
        verticalLayout_7 = new QVBoxLayout(groupBox_4);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        sendcomboBox = new QComboBox(groupBox_4);
        sendcomboBox->setObjectName(QString::fromUtf8("sendcomboBox"));

        horizontalLayout_2->addWidget(sendcomboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(0, 0));
        label_8->setMaximumSize(QSize(65, 16777215));

        horizontalLayout_2->addWidget(label_8);

        RulerID = new QLineEdit(groupBox_4);
        RulerID->setObjectName(QString::fromUtf8("RulerID"));
        RulerID->setMinimumSize(QSize(80, 0));
        RulerID->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(RulerID);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMaximumSize(QSize(65, 16777215));

        horizontalLayout_2->addWidget(label_9);

        addrcomboBox = new QComboBox(groupBox_4);
        addrcomboBox->setObjectName(QString::fromUtf8("addrcomboBox"));
        addrcomboBox->setMinimumSize(QSize(127, 0));

        horizontalLayout_2->addWidget(addrcomboBox);

        dircomboBox = new QComboBox(groupBox_4);
        dircomboBox->setObjectName(QString::fromUtf8("dircomboBox"));
        dircomboBox->setMinimumSize(QSize(120, 0));

        horizontalLayout_2->addWidget(dircomboBox);

        sendbyteslcdNumber = new QLCDNumber(groupBox_4);
        sendbyteslcdNumber->setObjectName(QString::fromUtf8("sendbyteslcdNumber"));
        sendbyteslcdNumber->setMaximumSize(QSize(16777215, 27));

        horizontalLayout_2->addWidget(sendbyteslcdNumber);


        verticalLayout_7->addLayout(horizontalLayout_2);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        sendAsHexcheckBox = new QCheckBox(groupBox_4);
        sendAsHexcheckBox->setObjectName(QString::fromUtf8("sendAsHexcheckBox"));
        sendAsHexcheckBox->setChecked(true);

        horizontalLayout_10->addWidget(sendAsHexcheckBox);

        sendMsgLineEdit = new QLineEdit(groupBox_4);
        sendMsgLineEdit->setObjectName(QString::fromUtf8("sendMsgLineEdit"));
        sendMsgLineEdit->setMaxLength(10000);
        sendMsgLineEdit->setDragEnabled(false);

        horizontalLayout_10->addWidget(sendMsgLineEdit);

        sendmsgBtn = new QPushButton(groupBox_4);
        sendmsgBtn->setObjectName(QString::fromUtf8("sendmsgBtn"));
        sendmsgBtn->setMinimumSize(QSize(0, 23));
        sendmsgBtn->setMaximumSize(QSize(100, 23));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/images/send.png"), QSize(), QIcon::Normal, QIcon::Off);
        sendmsgBtn->setIcon(icon11);
        sendmsgBtn->setAutoDefault(false);
        sendmsgBtn->setDefault(false);

        horizontalLayout_10->addWidget(sendmsgBtn);


        verticalLayout_7->addLayout(horizontalLayout_10);


        gridLayout->addWidget(groupBox_4, 1, 1, 1, 2);

        EmterWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(EmterWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setMinimumSize(QSize(0, 0));
        mainToolBar->setMaximumSize(QSize(16777215, 55));
        QFont font1;
        font1.setPointSize(9);
        mainToolBar->setFont(font1);
        mainToolBar->setCursor(QCursor(Qt::PointingHandCursor));
        mainToolBar->setFocusPolicy(Qt::StrongFocus);
        mainToolBar->setContextMenuPolicy(Qt::NoContextMenu);
        mainToolBar->setMovable(false);
        mainToolBar->setAllowedAreas(Qt::NoToolBarArea);
        mainToolBar->setIconSize(QSize(20, 20));
        mainToolBar->setFloatable(true);
        EmterWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EmterWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        EmterWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionClose);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionAdd);
        mainToolBar->addAction(actionLoadfile);
        mainToolBar->addAction(actionWriteToFile);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionClearBytes);
        mainToolBar->addAction(actionCleanPort);

        retranslateUi(EmterWindow);

        portNameComboBox->setCurrentIndex(2);
        baudRateComboBox->setCurrentIndex(10);
        dataBitsComboBox->setCurrentIndex(3);
        parityComboBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(EmterWindow);
    } // setupUi

    void retranslateUi(QMainWindow *EmterWindow)
    {
        EmterWindow->setWindowTitle(QApplication::translate("EmterWindow", "QCom\344\270\262\345\217\243\350\260\203\350\257\225\345\212\251\346\211\213 1.0", 0));
        actionAdd->setText(QApplication::translate("EmterWindow", "\346\267\273\345\212\240\344\270\262\345\217\243", 0));
#ifndef QT_NO_TOOLTIP
        actionAdd->setToolTip(QApplication::translate("EmterWindow", "\346\267\273\345\212\240\344\270\262\345\217\243\350\256\276\345\244\207\346\226\207\344\273\266", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAdd->setStatusTip(QApplication::translate("EmterWindow", "\346\267\273\345\212\240\344\270\262\345\217\243\350\256\276\345\244\207\346\226\207\344\273\266", 0));
#endif // QT_NO_STATUSTIP
        actionOpen->setText(QApplication::translate("EmterWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", 0));
#ifndef QT_NO_STATUSTIP
        actionOpen->setStatusTip(QApplication::translate("EmterWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", 0));
#endif // QT_NO_STATUSTIP
        actionClose->setText(QApplication::translate("EmterWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", 0));
#ifndef QT_NO_STATUSTIP
        actionClose->setStatusTip(QApplication::translate("EmterWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", 0));
#endif // QT_NO_STATUSTIP
        actionExit->setText(QApplication::translate("EmterWindow", "\351\200\200\345\207\272\347\250\213\345\272\217", 0));
#ifndef QT_NO_STATUSTIP
        actionExit->setStatusTip(QApplication::translate("EmterWindow", "\351\200\200\345\207\272\347\250\213\345\272\217", 0));
#endif // QT_NO_STATUSTIP
        actionAbout->setText(QApplication::translate("EmterWindow", "\345\205\263\344\272\216Wincom", 0));
#ifndef QT_NO_STATUSTIP
        actionAbout->setStatusTip(QApplication::translate("EmterWindow", "\345\205\263\344\272\216Wincom", 0));
#endif // QT_NO_STATUSTIP
        actionSave->setText(QApplication::translate("EmterWindow", "\344\277\235\345\255\230\346\225\260\346\215\256", 0));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("EmterWindow", "\344\277\235\345\255\230\346\224\266\345\217\221\346\241\206\345\206\205\347\232\204\346\225\260\346\215\256", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSave->setStatusTip(QApplication::translate("EmterWindow", "\344\277\235\345\255\230\346\224\266\345\217\221\346\241\206\345\206\205\347\232\204\346\225\260\346\215\256", 0));
#endif // QT_NO_STATUSTIP
        actionClearBytes->setText(QApplication::translate("EmterWindow", "\350\256\241\346\225\260\346\270\205\351\233\266", 0));
#ifndef QT_NO_TOOLTIP
        actionClearBytes->setToolTip(QApplication::translate("EmterWindow", "\346\270\205\351\233\266\345\267\262\346\224\266\345\210\260\347\232\204\345\255\227\350\212\202\346\225\260", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionClearBytes->setStatusTip(QApplication::translate("EmterWindow", "\346\270\205\351\233\266\345\267\262\346\224\266\345\210\260\347\232\204\345\255\227\350\212\202\346\225\260", 0));
#endif // QT_NO_STATUSTIP
        actionLoadfile->setText(QApplication::translate("EmterWindow", "\350\257\273\345\217\226\346\226\207\344\273\266", 0));
#ifndef QT_NO_TOOLTIP
        actionLoadfile->setToolTip(QApplication::translate("EmterWindow", "\350\275\275\345\205\245\345\244\226\351\203\250\346\226\207\344\273\266\344\275\234\344\270\272\345\217\221\351\200\201\345\206\205\345\256\271", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionLoadfile->setStatusTip(QApplication::translate("EmterWindow", "\350\275\275\345\205\245\345\244\226\351\203\250\346\226\207\344\273\266\344\275\234\344\270\272\345\217\221\351\200\201\345\206\205\345\256\271", 0));
#endif // QT_NO_STATUSTIP
        actionCleanPort->setText(QApplication::translate("EmterWindow", "\346\270\205\347\251\272\344\270\262\345\217\243", 0));
#ifndef QT_NO_TOOLTIP
        actionCleanPort->setToolTip(QApplication::translate("EmterWindow", "\346\270\205\347\251\272\344\270\262\345\217\243\344\270\255I/O\346\225\260\346\215\256", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionCleanPort->setStatusTip(QApplication::translate("EmterWindow", "\346\270\205\347\251\272\344\270\262\345\217\243\344\270\255I/O\346\225\260\346\215\256", 0));
#endif // QT_NO_STATUSTIP
        actionWriteToFile->setText(QApplication::translate("EmterWindow", "\345\206\231\345\205\245\346\226\207\344\273\266", 0));
#ifndef QT_NO_TOOLTIP
        actionWriteToFile->setToolTip(QApplication::translate("EmterWindow", "\345\260\206\350\257\273\345\217\226\346\225\260\346\215\256\345\206\231\345\205\245\345\210\260\346\226\207\344\273\266", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionWriteToFile->setStatusTip(QApplication::translate("EmterWindow", "\345\260\206\350\257\273\345\217\226\346\225\260\346\215\256\345\206\231\345\205\245\345\210\260\346\226\207\344\273\266", 0));
#endif // QT_NO_STATUSTIP
        groupBox->setTitle(QApplication::translate("EmterWindow", "\344\270\262\345\217\243\350\256\276\347\275\256", 0));
        label->setText(QApplication::translate("EmterWindow", "\344\270\262\345\217\243", 0));
        portNameComboBox->clear();
        portNameComboBox->insertItems(0, QStringList()
         << QApplication::translate("EmterWindow", "ttyO0", 0)
         << QApplication::translate("EmterWindow", "ttyO1", 0)
         << QApplication::translate("EmterWindow", "ttyO2", 0)
         << QApplication::translate("EmterWindow", "ttyO3", 0)
         << QApplication::translate("EmterWindow", "ttyO4", 0)
         << QApplication::translate("EmterWindow", "ttyO5", 0)
         << QApplication::translate("EmterWindow", "ttyUSB0", 0)
         << QApplication::translate("EmterWindow", "ttyUSB1", 0)
         << QApplication::translate("EmterWindow", "ttyUSB2", 0)
         << QApplication::translate("EmterWindow", "ttyUSB3", 0)
         << QApplication::translate("EmterWindow", "ttyUSB4", 0)
        );
        label_2->setText(QApplication::translate("EmterWindow", "\346\263\242\347\211\271\347\216\207", 0));
        baudRateComboBox->clear();
        baudRateComboBox->insertItems(0, QStringList()
         << QApplication::translate("EmterWindow", "50", 0)
         << QApplication::translate("EmterWindow", "75", 0)
         << QApplication::translate("EmterWindow", "110", 0)
         << QApplication::translate("EmterWindow", "134", 0)
         << QApplication::translate("EmterWindow", "150", 0)
         << QApplication::translate("EmterWindow", "200", 0)
         << QApplication::translate("EmterWindow", "300", 0)
         << QApplication::translate("EmterWindow", "600", 0)
         << QApplication::translate("EmterWindow", "1200", 0)
         << QApplication::translate("EmterWindow", "1800", 0)
         << QApplication::translate("EmterWindow", "2400", 0)
         << QApplication::translate("EmterWindow", "4800", 0)
         << QApplication::translate("EmterWindow", "9600", 0)
         << QApplication::translate("EmterWindow", "14400", 0)
         << QApplication::translate("EmterWindow", "19200", 0)
         << QApplication::translate("EmterWindow", "38400", 0)
         << QApplication::translate("EmterWindow", "56000", 0)
         << QApplication::translate("EmterWindow", "57600", 0)
         << QApplication::translate("EmterWindow", "76800", 0)
         << QApplication::translate("EmterWindow", "115200", 0)
         << QApplication::translate("EmterWindow", "128000", 0)
         << QApplication::translate("EmterWindow", "256000", 0)
        );
        label_3->setText(QApplication::translate("EmterWindow", "\346\225\260\346\215\256\344\275\215", 0));
        dataBitsComboBox->clear();
        dataBitsComboBox->insertItems(0, QStringList()
         << QApplication::translate("EmterWindow", "5", 0)
         << QApplication::translate("EmterWindow", "6", 0)
         << QApplication::translate("EmterWindow", "7", 0)
         << QApplication::translate("EmterWindow", "8", 0)
        );
        label_4->setText(QApplication::translate("EmterWindow", "\346\240\241\351\252\214\344\275\215", 0));
        parityComboBox->clear();
        parityComboBox->insertItems(0, QStringList()
         << QApplication::translate("EmterWindow", "\346\227\240", 0)
         << QApplication::translate("EmterWindow", "\345\245\207", 0)
         << QApplication::translate("EmterWindow", "\345\201\266", 0)
        );
        label_5->setText(QApplication::translate("EmterWindow", "\345\201\234\346\255\242\344\275\215", 0));
        stopBitsComboBox->clear();
        stopBitsComboBox->insertItems(0, QStringList()
         << QApplication::translate("EmterWindow", "1", 0)
         << QApplication::translate("EmterWindow", "2", 0)
        );
        obocheckBox->setText(QApplication::translate("EmterWindow", "\350\277\236\347\273\255\345\217\221\351\200\201", 0));
        label_6->setText(QApplication::translate("EmterWindow", "\351\227\264\351\232\224(\346\257\253\347\247\222)", 0));
        groupBox_2->setTitle(QApplication::translate("EmterWindow", "\346\216\245\346\224\266\346\225\260\346\215\256", 0));
#ifndef QT_NO_TOOLTIP
        chradioButton->setToolTip(QApplication::translate("EmterWindow", "<html><head/><body><p>\344\273\245\345\215\201\345\205\255\350\277\233\345\210\266\346\226\271\345\274\217\346\230\276\347\244\272\346\225\260\346\215\256</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        chradioButton->setText(QApplication::translate("EmterWindow", "\345\215\201\345\205\255\350\277\233\345\210\266\345\275\242\345\274\217\346\230\276\347\244\272", 0));
#ifndef QT_NO_TOOLTIP
        recvbyteslcdNumber->setToolTip(QApplication::translate("EmterWindow", "\345\267\262\346\216\245\346\224\266\345\255\227\350\212\202\346\225\260", 0));
#endif // QT_NO_TOOLTIP
        clearUpBtn->setText(QApplication::translate("EmterWindow", "\346\270\205\347\251\272", 0));
        groupBox_3->setTitle(QApplication::translate("EmterWindow", "\350\247\243\346\236\220\346\225\260\346\215\256", 0));
        groupBox_4->setTitle(QApplication::translate("EmterWindow", "\345\217\221\351\200\201\346\225\260\346\215\256", 0));
        sendcomboBox->clear();
        sendcomboBox->insertItems(0, QStringList()
         << QApplication::translate("EmterWindow", "A\351\241\271\347\224\265\345\216\213", 0)
         << QApplication::translate("EmterWindow", "A\351\241\271\347\224\265\346\265\201", 0)
        );
        label_8->setText(QApplication::translate("EmterWindow", "\346\240\207\350\257\206\347\240\201:", 0));
        RulerID->setText(QApplication::translate("EmterWindow", "02010100", 0));
        label_9->setText(QApplication::translate("EmterWindow", "\347\224\265\350\241\250\345\234\260\345\235\200:", 0));
        addrcomboBox->clear();
        addrcomboBox->insertItems(0, QStringList()
         << QApplication::translate("EmterWindow", "000000000001", 0)
         << QApplication::translate("EmterWindow", "000000000002", 0)
        );
        dircomboBox->clear();
        dircomboBox->insertItems(0, QStringList()
         << QApplication::translate("EmterWindow", "\344\270\273\347\253\231\345\210\260\344\273\216\347\253\231(0)", 0)
         << QApplication::translate("EmterWindow", "\344\273\216\347\253\231\345\210\260\344\270\273\347\253\231(1)", 0)
        );
#ifndef QT_NO_TOOLTIP
        sendAsHexcheckBox->setToolTip(QApplication::translate("EmterWindow", "<html><head/><body><p>\344\273\245\345\215\201\345\205\255\350\277\233\345\210\266\346\226\271\345\274\217\345\217\221\351\200\201\346\225\260\346\215\256\357\274\210\351\273\230\350\256\244\344\270\272\345\255\227\347\254\246\346\226\271\345\274\217\357\274\211</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        sendAsHexcheckBox->setText(QApplication::translate("EmterWindow", "\345\215\201\345\205\255\350\277\233\345\210\266\345\217\221\351\200\201", 0));
        sendMsgLineEdit->setText(QApplication::translate("EmterWindow", "68 01 00 00 00 00 00 68 11 04 33 34 34 35 B6 16", 0));
        sendmsgBtn->setText(QApplication::translate("EmterWindow", "\345\217\221\351\200\201", 0));
    } // retranslateUi

};

namespace Ui {
    class EmterWindow: public Ui_EmterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMTER_WINDOW_H
