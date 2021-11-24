#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QTimer>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QHeaderView>
#include <QDateTime>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostInfo>
#include <QIcon>
#include "ymodem.h"
#include "logindialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // 串口通信相关
    QSerialPort *MySerialPort;
    QTimer *PortTimer;
    QButtonGroup *AsciiHexGroup;
    int SerialPortCount=0;
    // bin文件下载到单片机相关
    YModem *MyYModem;

    // 数据库相关
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlQuery query;

    // socket通信相关
    QTcpSocket *MySocket, *ServerSocket;
    QTcpServer *MyServer;
    QByteArray socketArray;
    QButtonGroup *ServerClientGroup;
    int ifConnected=0, hasConnected=0;

    // 用户设置相关
    LoginDialog *userLogin;


    // 用户权限相关部分
    void DisableAll();
    void EnableForNormalUser();
    void EnableForAdminUser();
    bool IsAdmin;
private slots:

    // 串口通信相关
    void serialConnect();
    void serialPortUpdate();
    void clearSerialText();
    void serialSend();
    void serialReceive();
    // 发送bin文件
    void yModemSend();
    void yModemEnd();
    void downloadPathSelect();
    void uploadPathSelect();
    // 保存到数据库操作
    void uploadBin2Database();
    void downloadBinFromDatabase();
    void deleteBinFromDatabase();

    // socket通信部分, server/socket完全分开处理
    void socketConnect();
    void socketDisconnect();
    void serverNewConnect();
    void socketSendFile();
    void socketRecFile();
    void socketSetRecPath();
    void onSocketStateChange(QAbstractSocket::SocketState socketState);
    QString getLocalIP();

    // 用户登陆部分
    void loginSuccess(QString, bool);
};
#endif // MAINWINDOW_H
