/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *SerialGroup;
    QLabel *label;
    QComboBox *PortBox;
    QComboBox *BaudRateBox;
    QLabel *label_2;
    QComboBox *DataBox;
    QLabel *label_3;
    QComboBox *CheckBox;
    QLabel *label_4;
    QComboBox *StopBox;
    QLabel *label_5;
    QComboBox *FluidBox;
    QLabel *label_6;
    QRadioButton *AsciiSelect;
    QRadioButton *HexSelected;
    QPushButton *ClearButton;
    QCheckBox *TimeCheckBox;
    QPushButton *SerialConnectButton;
    QGroupBox *DisplayGriup;
    QTextEdit *SerialScreenText;
    QLineEdit *SerialSendLine;
    QPushButton *SerialSendButton;
    QGroupBox *UserGroup;
    QLabel *UserNameLabel;
    QLabel *UserNameLabel_2;
    QLabel *label_7;
    QLabel *IsAdminLabel;
    QGroupBox *binGroup;
    QTableView *SqlShowView;
    QPushButton *UploadPathButton;
    QLineEdit *UpLoadPath;
    QLineEdit *DownloadPath;
    QPushButton *DownloadPathButton;
    QPushButton *UploadButton;
    QPushButton *DownloadButton;
    QPushButton *DeleteButton;
    QPushButton *Download2stmButton;
    QTextEdit *SqlText;
    QProgressBar *Download2stmBar;
    QGroupBox *SocketGroup;
    QRadioButton *ServerRadioButton;
    QRadioButton *ClientRadioButton;
    QLabel *label_8;
    QLineEdit *ServerIP;
    QLabel *label_9;
    QLineEdit *ClientIP;
    QLabel *label_10;
    QSpinBox *PortSpinBox;
    QPushButton *SocketConnectButton;
    QPushButton *SocketSendButton;
    QPushButton *SocketReceivePathButton;
    QProgressBar *SocketBar;
    QLineEdit *SocketReceivePath;
    QTextEdit *SocketTextOutput;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 698);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        SerialGroup = new QGroupBox(centralwidget);
        SerialGroup->setObjectName(QString::fromUtf8("SerialGroup"));
        SerialGroup->setGeometry(QRect(20, 90, 161, 291));
        label = new QLabel(SerialGroup);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 41, 16));
        PortBox = new QComboBox(SerialGroup);
        PortBox->setObjectName(QString::fromUtf8("PortBox"));
        PortBox->setGeometry(QRect(68, 30, 81, 21));
        BaudRateBox = new QComboBox(SerialGroup);
        BaudRateBox->addItem(QString());
        BaudRateBox->addItem(QString());
        BaudRateBox->addItem(QString());
        BaudRateBox->addItem(QString());
        BaudRateBox->addItem(QString());
        BaudRateBox->addItem(QString());
        BaudRateBox->addItem(QString());
        BaudRateBox->setObjectName(QString::fromUtf8("BaudRateBox"));
        BaudRateBox->setGeometry(QRect(70, 60, 69, 21));
        label_2 = new QLabel(SerialGroup);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 41, 16));
        DataBox = new QComboBox(SerialGroup);
        DataBox->addItem(QString());
        DataBox->addItem(QString());
        DataBox->addItem(QString());
        DataBox->addItem(QString());
        DataBox->setObjectName(QString::fromUtf8("DataBox"));
        DataBox->setGeometry(QRect(70, 90, 69, 21));
        label_3 = new QLabel(SerialGroup);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 90, 41, 16));
        CheckBox = new QComboBox(SerialGroup);
        CheckBox->addItem(QString());
        CheckBox->addItem(QString());
        CheckBox->addItem(QString());
        CheckBox->setObjectName(QString::fromUtf8("CheckBox"));
        CheckBox->setGeometry(QRect(70, 120, 69, 21));
        label_4 = new QLabel(SerialGroup);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 120, 41, 16));
        StopBox = new QComboBox(SerialGroup);
        StopBox->addItem(QString());
        StopBox->addItem(QString());
        StopBox->addItem(QString());
        StopBox->setObjectName(QString::fromUtf8("StopBox"));
        StopBox->setGeometry(QRect(70, 150, 69, 21));
        label_5 = new QLabel(SerialGroup);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 150, 41, 16));
        FluidBox = new QComboBox(SerialGroup);
        FluidBox->addItem(QString());
        FluidBox->addItem(QString());
        FluidBox->addItem(QString());
        FluidBox->setObjectName(QString::fromUtf8("FluidBox"));
        FluidBox->setGeometry(QRect(70, 180, 69, 21));
        label_6 = new QLabel(SerialGroup);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 180, 41, 21));
        AsciiSelect = new QRadioButton(SerialGroup);
        AsciiSelect->setObjectName(QString::fromUtf8("AsciiSelect"));
        AsciiSelect->setGeometry(QRect(20, 210, 51, 16));
        AsciiSelect->setChecked(true);
        HexSelected = new QRadioButton(SerialGroup);
        HexSelected->setObjectName(QString::fromUtf8("HexSelected"));
        HexSelected->setGeometry(QRect(100, 210, 41, 16));
        ClearButton = new QPushButton(SerialGroup);
        ClearButton->setObjectName(QString::fromUtf8("ClearButton"));
        ClearButton->setGeometry(QRect(20, 260, 121, 23));
        TimeCheckBox = new QCheckBox(SerialGroup);
        TimeCheckBox->setObjectName(QString::fromUtf8("TimeCheckBox"));
        TimeCheckBox->setGeometry(QRect(20, 230, 51, 21));
        SerialConnectButton = new QPushButton(SerialGroup);
        SerialConnectButton->setObjectName(QString::fromUtf8("SerialConnectButton"));
        SerialConnectButton->setGeometry(QRect(70, 230, 71, 23));
        DisplayGriup = new QGroupBox(centralwidget);
        DisplayGriup->setObjectName(QString::fromUtf8("DisplayGriup"));
        DisplayGriup->setGeometry(QRect(200, 0, 591, 381));
        SerialScreenText = new QTextEdit(DisplayGriup);
        SerialScreenText->setObjectName(QString::fromUtf8("SerialScreenText"));
        SerialScreenText->setGeometry(QRect(10, 20, 571, 321));
        SerialSendLine = new QLineEdit(DisplayGriup);
        SerialSendLine->setObjectName(QString::fromUtf8("SerialSendLine"));
        SerialSendLine->setGeometry(QRect(10, 350, 481, 20));
        SerialSendButton = new QPushButton(DisplayGriup);
        SerialSendButton->setObjectName(QString::fromUtf8("SerialSendButton"));
        SerialSendButton->setEnabled(false);
        SerialSendButton->setGeometry(QRect(500, 350, 81, 21));
        UserGroup = new QGroupBox(centralwidget);
        UserGroup->setObjectName(QString::fromUtf8("UserGroup"));
        UserGroup->setGeometry(QRect(20, 0, 161, 80));
        UserNameLabel = new QLabel(UserGroup);
        UserNameLabel->setObjectName(QString::fromUtf8("UserNameLabel"));
        UserNameLabel->setGeometry(QRect(70, 20, 81, 20));
        UserNameLabel_2 = new QLabel(UserGroup);
        UserNameLabel_2->setObjectName(QString::fromUtf8("UserNameLabel_2"));
        UserNameLabel_2->setGeometry(QRect(10, 20, 41, 16));
        label_7 = new QLabel(UserGroup);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 50, 54, 16));
        IsAdminLabel = new QLabel(UserGroup);
        IsAdminLabel->setObjectName(QString::fromUtf8("IsAdminLabel"));
        IsAdminLabel->setGeometry(QRect(70, 50, 81, 16));
        binGroup = new QGroupBox(centralwidget);
        binGroup->setObjectName(QString::fromUtf8("binGroup"));
        binGroup->setGeometry(QRect(10, 390, 451, 261));
        SqlShowView = new QTableView(binGroup);
        SqlShowView->setObjectName(QString::fromUtf8("SqlShowView"));
        SqlShowView->setGeometry(QRect(150, 80, 291, 171));
        UploadPathButton = new QPushButton(binGroup);
        UploadPathButton->setObjectName(QString::fromUtf8("UploadPathButton"));
        UploadPathButton->setGeometry(QRect(10, 20, 61, 23));
        UpLoadPath = new QLineEdit(binGroup);
        UpLoadPath->setObjectName(QString::fromUtf8("UpLoadPath"));
        UpLoadPath->setGeometry(QRect(80, 20, 361, 21));
        DownloadPath = new QLineEdit(binGroup);
        DownloadPath->setObjectName(QString::fromUtf8("DownloadPath"));
        DownloadPath->setGeometry(QRect(80, 50, 361, 20));
        DownloadPathButton = new QPushButton(binGroup);
        DownloadPathButton->setObjectName(QString::fromUtf8("DownloadPathButton"));
        DownloadPathButton->setGeometry(QRect(10, 50, 61, 23));
        UploadButton = new QPushButton(binGroup);
        UploadButton->setObjectName(QString::fromUtf8("UploadButton"));
        UploadButton->setGeometry(QRect(10, 80, 61, 23));
        DownloadButton = new QPushButton(binGroup);
        DownloadButton->setObjectName(QString::fromUtf8("DownloadButton"));
        DownloadButton->setGeometry(QRect(80, 80, 61, 23));
        DeleteButton = new QPushButton(binGroup);
        DeleteButton->setObjectName(QString::fromUtf8("DeleteButton"));
        DeleteButton->setGeometry(QRect(10, 110, 131, 23));
        Download2stmButton = new QPushButton(binGroup);
        Download2stmButton->setObjectName(QString::fromUtf8("Download2stmButton"));
        Download2stmButton->setEnabled(false);
        Download2stmButton->setGeometry(QRect(10, 140, 131, 23));
        SqlText = new QTextEdit(binGroup);
        SqlText->setObjectName(QString::fromUtf8("SqlText"));
        SqlText->setGeometry(QRect(10, 200, 131, 51));
        Download2stmBar = new QProgressBar(binGroup);
        Download2stmBar->setObjectName(QString::fromUtf8("Download2stmBar"));
        Download2stmBar->setGeometry(QRect(10, 170, 131, 20));
        Download2stmBar->setValue(0);
        SocketGroup = new QGroupBox(centralwidget);
        SocketGroup->setObjectName(QString::fromUtf8("SocketGroup"));
        SocketGroup->setGeometry(QRect(480, 390, 301, 261));
        ServerRadioButton = new QRadioButton(SocketGroup);
        ServerRadioButton->setObjectName(QString::fromUtf8("ServerRadioButton"));
        ServerRadioButton->setGeometry(QRect(20, 20, 61, 21));
        ServerRadioButton->setChecked(true);
        ClientRadioButton = new QRadioButton(SocketGroup);
        ClientRadioButton->setObjectName(QString::fromUtf8("ClientRadioButton"));
        ClientRadioButton->setGeometry(QRect(20, 50, 61, 21));
        label_8 = new QLabel(SocketGroup);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(100, 20, 41, 21));
        ServerIP = new QLineEdit(SocketGroup);
        ServerIP->setObjectName(QString::fromUtf8("ServerIP"));
        ServerIP->setEnabled(false);
        ServerIP->setGeometry(QRect(160, 20, 131, 20));
        label_9 = new QLabel(SocketGroup);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(100, 50, 41, 21));
        ClientIP = new QLineEdit(SocketGroup);
        ClientIP->setObjectName(QString::fromUtf8("ClientIP"));
        ClientIP->setGeometry(QRect(160, 50, 131, 20));
        label_10 = new QLabel(SocketGroup);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 80, 41, 21));
        PortSpinBox = new QSpinBox(SocketGroup);
        PortSpinBox->setObjectName(QString::fromUtf8("PortSpinBox"));
        PortSpinBox->setGeometry(QRect(90, 80, 61, 21));
        PortSpinBox->setMaximum(10000);
        PortSpinBox->setValue(8080);
        SocketConnectButton = new QPushButton(SocketGroup);
        SocketConnectButton->setObjectName(QString::fromUtf8("SocketConnectButton"));
        SocketConnectButton->setGeometry(QRect(160, 80, 61, 23));
        SocketSendButton = new QPushButton(SocketGroup);
        SocketSendButton->setObjectName(QString::fromUtf8("SocketSendButton"));
        SocketSendButton->setEnabled(false);
        SocketSendButton->setGeometry(QRect(230, 80, 61, 23));
        SocketReceivePathButton = new QPushButton(SocketGroup);
        SocketReceivePathButton->setObjectName(QString::fromUtf8("SocketReceivePathButton"));
        SocketReceivePathButton->setGeometry(QRect(20, 108, 81, 23));
        SocketBar = new QProgressBar(SocketGroup);
        SocketBar->setObjectName(QString::fromUtf8("SocketBar"));
        SocketBar->setGeometry(QRect(120, 110, 171, 21));
        SocketBar->setValue(0);
        SocketReceivePath = new QLineEdit(SocketGroup);
        SocketReceivePath->setObjectName(QString::fromUtf8("SocketReceivePath"));
        SocketReceivePath->setGeometry(QRect(20, 140, 271, 20));
        SocketTextOutput = new QTextEdit(SocketGroup);
        SocketTextOutput->setObjectName(QString::fromUtf8("SocketTextOutput"));
        SocketTextOutput->setGeometry(QRect(20, 170, 271, 81));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        PortBox->setCurrentIndex(-1);
        BaudRateBox->setCurrentIndex(6);
        DataBox->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "stm32Downloader", nullptr));
        SerialGroup->setTitle(QApplication::translate("MainWindow", "\344\270\262\345\217\243\350\256\276\347\275\256", nullptr));
        label->setText(QApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267", nullptr));
        BaudRateBox->setItemText(0, QApplication::translate("MainWindow", "2400", nullptr));
        BaudRateBox->setItemText(1, QApplication::translate("MainWindow", "4800", nullptr));
        BaudRateBox->setItemText(2, QApplication::translate("MainWindow", "9600", nullptr));
        BaudRateBox->setItemText(3, QApplication::translate("MainWindow", "19200", nullptr));
        BaudRateBox->setItemText(4, QApplication::translate("MainWindow", "38400", nullptr));
        BaudRateBox->setItemText(5, QApplication::translate("MainWindow", "57600", nullptr));
        BaudRateBox->setItemText(6, QApplication::translate("MainWindow", "115200", nullptr));

        label_2->setText(QApplication::translate("MainWindow", "\346\263\242\347\211\271\347\216\207", nullptr));
        DataBox->setItemText(0, QApplication::translate("MainWindow", "5", nullptr));
        DataBox->setItemText(1, QApplication::translate("MainWindow", "6", nullptr));
        DataBox->setItemText(2, QApplication::translate("MainWindow", "7", nullptr));
        DataBox->setItemText(3, QApplication::translate("MainWindow", "8", nullptr));

        label_3->setText(QApplication::translate("MainWindow", "\346\225\260\346\215\256\344\275\215", nullptr));
        CheckBox->setItemText(0, QApplication::translate("MainWindow", "\346\227\240\346\240\241\351\252\214", nullptr));
        CheckBox->setItemText(1, QApplication::translate("MainWindow", "\345\245\207\346\240\241\351\252\214", nullptr));
        CheckBox->setItemText(2, QApplication::translate("MainWindow", "\345\201\266\346\240\241\351\252\214", nullptr));

        label_4->setText(QApplication::translate("MainWindow", "\346\240\241\351\252\214\344\275\215", nullptr));
        StopBox->setItemText(0, QApplication::translate("MainWindow", "1", nullptr));
        StopBox->setItemText(1, QApplication::translate("MainWindow", "1.5", nullptr));
        StopBox->setItemText(2, QApplication::translate("MainWindow", "2", nullptr));

        label_5->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\344\275\215", nullptr));
        FluidBox->setItemText(0, QApplication::translate("MainWindow", "\346\227\240\346\265\201\346\216\247", nullptr));
        FluidBox->setItemText(1, QApplication::translate("MainWindow", "\347\241\254\344\273\266\346\265\201", nullptr));
        FluidBox->setItemText(2, QApplication::translate("MainWindow", "\350\275\257\344\273\266\346\265\201", nullptr));

        label_6->setText(QApplication::translate("MainWindow", "\346\265\201\346\216\247\345\210\266", nullptr));
        AsciiSelect->setText(QApplication::translate("MainWindow", "ASCII", nullptr));
        HexSelected->setText(QApplication::translate("MainWindow", "HEX", nullptr));
        ClearButton->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\346\230\276\347\244\272\345\214\272", nullptr));
        TimeCheckBox->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264", nullptr));
        SerialConnectButton->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        DisplayGriup->setTitle(QApplication::translate("MainWindow", "\344\270\262\345\217\243\346\230\276\347\244\272\345\214\272", nullptr));
        SerialSendButton->setText(QApplication::translate("MainWindow", "\345\217\221  \351\200\201", nullptr));
        UserGroup->setTitle(QApplication::translate("MainWindow", "\345\275\223\345\211\215\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        UserNameLabel->setText(QString());
        UserNameLabel_2->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\347\261\273\345\236\213\357\274\232", nullptr));
        IsAdminLabel->setText(QString());
        binGroup->setTitle(QApplication::translate("MainWindow", "bin\346\226\207\344\273\266\344\270\213\350\275\275", nullptr));
        UploadPathButton->setText(QApplication::translate("MainWindow", "\344\270\212\344\274\240\350\267\257\345\276\204", nullptr));
        DownloadPathButton->setText(QApplication::translate("MainWindow", "\344\270\213\350\275\275\350\267\257\345\276\204", nullptr));
        UploadButton->setText(QApplication::translate("MainWindow", "\344\270\212\344\274\240\346\226\207\344\273\266", nullptr));
        DownloadButton->setText(QApplication::translate("MainWindow", "\344\270\213\350\275\275\346\226\207\344\273\266", nullptr));
        DeleteButton->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\346\211\200\351\200\211\346\225\260\346\215\256\345\272\223\346\226\207\344\273\266", nullptr));
        Download2stmButton->setText(QApplication::translate("MainWindow", "\344\270\213\350\275\275\346\211\200\351\200\211\346\226\207\344\273\266\345\210\260\345\215\225\347\211\207\346\234\272", nullptr));
        SocketGroup->setTitle(QApplication::translate("MainWindow", "bin\346\226\207\344\273\266\347\275\221\347\273\234\345\205\261\344\272\253", nullptr));
        ServerRadioButton->setText(QApplication::translate("MainWindow", "Server", nullptr));
        ClientRadioButton->setText(QApplication::translate("MainWindow", "Client", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "\346\234\254\346\234\272IP\357\274\232", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "\345\257\271\346\226\271IP\357\274\232", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "\347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        SocketConnectButton->setText(QApplication::translate("MainWindow", "\347\202\271\345\207\273\350\277\236\346\216\245", nullptr));
        SocketSendButton->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        SocketReceivePathButton->setText(QApplication::translate("MainWindow", "\346\216\245\345\217\227\346\226\207\344\273\266\345\234\260\345\235\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
