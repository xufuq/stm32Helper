/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLineEdit *Username;
    QLabel *label_2;
    QLineEdit *Password;
    QPushButton *LoginInButton;
    QWidget *tab_2;
    QLineEdit *NewPassword;
    QLineEdit *NewUsername;
    QLabel *label_3;
    QPushButton *CreateCount;
    QLabel *label_4;
    QLineEdit *RootPassword;
    QLabel *label_5;
    QCheckBox *isAdminChecked;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(318, 426);
        QFont font;
        font.setPointSize(9);
        LoginDialog->setFont(font);
        tabWidget = new QTabWidget(LoginDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 301, 411));
        QFont font1;
        font1.setPointSize(15);
        tabWidget->setFont(font1);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 261, 51));
        Username = new QLineEdit(tab);
        Username->setObjectName(QString::fromUtf8("Username"));
        Username->setGeometry(QRect(50, 80, 161, 31));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 120, 261, 51));
        Password = new QLineEdit(tab);
        Password->setObjectName(QString::fromUtf8("Password"));
        Password->setGeometry(QRect(50, 180, 171, 31));
        LoginInButton = new QPushButton(tab);
        LoginInButton->setObjectName(QString::fromUtf8("LoginInButton"));
        LoginInButton->setGeometry(QRect(70, 270, 131, 51));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        NewPassword = new QLineEdit(tab_2);
        NewPassword->setObjectName(QString::fromUtf8("NewPassword"));
        NewPassword->setGeometry(QRect(60, 140, 171, 31));
        NewUsername = new QLineEdit(tab_2);
        NewUsername->setObjectName(QString::fromUtf8("NewUsername"));
        NewUsername->setGeometry(QRect(60, 70, 161, 31));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 110, 261, 31));
        CreateCount = new QPushButton(tab_2);
        CreateCount->setObjectName(QString::fromUtf8("CreateCount"));
        CreateCount->setGeometry(QRect(70, 320, 131, 51));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 30, 251, 31));
        RootPassword = new QLineEdit(tab_2);
        RootPassword->setObjectName(QString::fromUtf8("RootPassword"));
        RootPassword->setGeometry(QRect(60, 230, 171, 31));
        RootPassword->setInputMethodHints(Qt::ImhNone);
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 190, 261, 31));
        isAdminChecked = new QCheckBox(tab_2);
        isAdminChecked->setObjectName(QString::fromUtf8("isAdminChecked"));
        isAdminChecked->setGeometry(QRect(30, 280, 221, 31));
        tabWidget->addTab(tab_2, QString());

        retranslateUi(LoginDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "\347\224\250\346\210\267\347\231\273\351\231\206\346\263\250\345\206\214", nullptr));
        label->setText(QApplication::translate("LoginDialog", " \347\224\250\346\210\267\345\220\215\357\274\2101-10\344\270\252\345\255\227\347\254\246\345\255\227\347\254\246\357\274\211", nullptr));
        Username->setText(QString());
        label_2->setText(QApplication::translate("LoginDialog", "  \345\257\206\347\240\201\357\274\2101-10\344\270\252\345\255\227\347\254\246\345\255\227\347\254\246\357\274\211", nullptr));
        Password->setText(QString());
        LoginInButton->setText(QApplication::translate("LoginDialog", "\347\231\273 \351\231\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("LoginDialog", "\347\231\273\351\231\206\347\225\214\351\235\242", nullptr));
        NewPassword->setText(QString());
        NewUsername->setText(QString());
        label_3->setText(QApplication::translate("LoginDialog", "  \345\257\206\347\240\201\357\274\2101-10\344\270\252\345\255\227\347\254\246\345\255\227\347\254\246\357\274\211", nullptr));
        CreateCount->setText(QApplication::translate("LoginDialog", "\346\263\250 \345\206\214", nullptr));
        label_4->setText(QApplication::translate("LoginDialog", " \347\224\250\346\210\267\345\220\215\357\274\2101-10\344\270\252\345\255\227\347\254\246\345\255\227\347\254\246\357\274\211", nullptr));
        RootPassword->setText(QString());
        label_5->setText(QApplication::translate("LoginDialog", "root\345\257\206\347\240\201\357\274\2101-10\344\270\252\345\255\227\347\254\246\345\255\227\347\254\246\357\274\211", nullptr));
        isAdminChecked->setText(QApplication::translate("LoginDialog", "\346\230\257\345\220\246\345\210\233\345\273\272\344\270\272\347\256\241\347\220\206\345\221\230\350\264\246\346\210\267", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("LoginDialog", "\346\263\250\345\206\214\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
