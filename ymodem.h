#ifndef YMODEM_H
#define YMODEM_H

#include <QObject>
#include <QEventLoop>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QProgressBar>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>

class YModem : public QObject
{
    Q_OBJECT
public:
    explicit YModem(QByteArray binData, QString filename, QProgressBar *ftProgress, QTextEdit *outputText, QObject *parent = nullptr);

    void SetPort(QSerialPort *P);       //初始化串口端口

    qint16 GetCrc(QByteArray Data);

    int ackwait(int to);

    void YModem_send_Handle();     //发送处理

private:
    QSerialPort *Port;

    QString FileName;
    QString *recString;

    QByteArray TxData;
    QByteArray RxData;
    qint32 PackNumber;      //发送文件的包数
    qint32 PackCnt;         //已发送的包数
    qint32 PackIndex;       //包序号
    qint32 PackSize;        //1包字节数
    qint32 SendLen;         //发送一帧数据的实际长度

    //QTimer *tm_timeout;

    qint8 Step;

    quint8 AckFlag;

    //子窗口
    // QProgressBar *pb_ftpProgress;

    QLineEdit *led_filePath;
    QTextEdit *OutputText;
    QPushButton *btn_fileOpen;
    QPushButton *btn_fileSend;
    QProgressBar *pb_ftpProgress;
signals:
    void sgn_ftpEnd();
    void sgn_recvACK();

private slots:
    void YModem_rec_Handle();      //接收处理


signals:

};

#endif // YMODEM_H
