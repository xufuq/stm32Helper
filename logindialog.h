#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QSqlDatabase *db, QWidget *parent = nullptr);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
    QSqlDatabase *Logindb;

private slots:
    void loginPush();
    void createPush();

signals:
    void loginSuccess(QString name, bool admin);
};

#endif // LOGINDIALOG_H
