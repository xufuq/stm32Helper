#include "logindialog.h"
#include "ui_logindialog.h"
#include "mainwindow.h"

LoginDialog::LoginDialog(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    Logindb=db;
    connect(ui->LoginInButton, SIGNAL(clicked()),this,SLOT(loginPush()));
    connect(ui->CreateCount, SIGNAL(clicked()),this,SLOT(createPush()));
    ui->Password->setEchoMode(QLineEdit::Password);
    ui->NewPassword->setEchoMode(QLineEdit::Password);
    ui->RootPassword->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::loginPush()
{
    QSqlQuery query=QSqlQuery(*Logindb);
    qDebug() << "查找成功？" <<  query.exec("select * from userTable where username = '" + ui->Username->text()+"'"); // 注意这个小单引号，字符串需要这样标注

    if(query.first())
    {
        QString password=query.value(2).toString(); // 这里确保没有同名用户
        bool admin=query.value(3).toBool();
        if(password==ui->Password->text())
        {
            emit loginSuccess(query.value(1).toString(),admin);
            this->close();
            return;
        }
    }
    QMessageBox::information(NULL, "登陆失败", "用户名或密码错误！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void LoginDialog::createPush()
{
    QSqlQuery query=QSqlQuery(*Logindb);
    // 如果没有查找成功就可以创建
    qDebug() << "查找成功？" <<  query.exec("select * from userTable where username = '" + ui->NewUsername->text()+"'");
    if(!query.first() && ui->RootPassword->text()=="123456") // 这里的root密码可以改，需要和mainwindow中的密码一块改
    {
        query.prepare("INSERT INTO userTable(id, username, password, Admin) VALUES(:id, :username, :password, :Admin)");
        query.bindValue(":username", ui->NewUsername->text());
        query.bindValue(":password", ui->NewPassword->text());
        if(ui->isAdminChecked->isChecked())
            query.bindValue(":Admin", true);
        else
            query.bindValue(":Admin", false);
        qDebug() << "插入表状态" << query.exec();
        emit loginSuccess(ui->NewUsername->text(),ui->isAdminChecked->isChecked());
        this->close();
    }
    else
        QMessageBox::information(NULL, "创建失败", "用户名已存在或root密码错误！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}
