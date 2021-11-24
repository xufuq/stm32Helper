#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AsciiHexGroup=new QButtonGroup();
    AsciiHexGroup->addButton(ui->AsciiSelect);
    AsciiHexGroup->addButton(ui->HexSelected);

    ServerClientGroup=new QButtonGroup();
    ServerClientGroup->addButton(ui->ServerRadioButton);
    ServerClientGroup->addButton(ui->ClientRadioButton);

    // 定时器定时更新串口号
    PortTimer=new QTimer();
    PortTimer->start(100);
    MySerialPort=new QSerialPort();

    QString LocalIP = getLocalIP();
    ui->ServerIP->setText(LocalIP);

    MySocket=new QTcpSocket();
    MyServer=new QTcpServer();

    connect(PortTimer, SIGNAL(timeout()),this,SLOT(serialPortUpdate()));
    connect(ui->SerialConnectButton, SIGNAL(clicked()),this,SLOT(serialConnect()));
    connect(ui->ClearButton, SIGNAL(clicked()),this,SLOT(clearSerialText()));
    connect(ui->SerialSendButton, SIGNAL(clicked()),this,SLOT(serialSend()));
    connect(MySerialPort, SIGNAL(readyRead()),this,SLOT(serialReceive()));

    connect(ui->Download2stmButton, SIGNAL(clicked()),this,SLOT(yModemSend()));
    connect(ui->DownloadPathButton, SIGNAL(clicked()),this,SLOT(downloadPathSelect()));
    connect(ui->UploadPathButton, SIGNAL(clicked()),this,SLOT(uploadPathSelect()));
    connect(ui->UploadButton, SIGNAL(clicked()),this,SLOT(uploadBin2Database()));
    connect(ui->DownloadButton, SIGNAL(clicked()),this,SLOT(downloadBinFromDatabase()));
    connect(ui->DeleteButton, SIGNAL(clicked()),this,SLOT(deleteBinFromDatabase()));

    connect(ui->SocketConnectButton, SIGNAL(clicked()),this,SLOT(socketConnect()));
    connect(ui->SocketSendButton, SIGNAL(clicked()),this,SLOT(socketSendFile()));
    connect(ui->SocketReceivePathButton, SIGNAL(clicked()),this,SLOT(socketSetRecPath()));
    // socket部分
    connect(MySocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(onSocketStateChange(QAbstractSocket::SocketState)));
    connect(MySocket, SIGNAL(readyRead()),this,SLOT(socketRecFile()));


    db = QSqlDatabase::addDatabase("QSQLITE"); //数据库对象
    db.setHostName("127.0.0.1"); //设置数据库主机名
    db.setDatabaseName(QCoreApplication::applicationDirPath()+"/"+"bin.db"); //设置数据库名
    db.setUserName("root"); //设置数据库用户名
    db.setPassword("1234"); //设置数据库密码
    if (!db.open()) {
        qDebug() << "Error: Failed to connect database." << db.lastError();
    } else {
        qDebug() << "Succeed to connect database.";
    }

    query=QSqlQuery(db);
    if(!query.exec("CREATE TABLE binFile(id integer primary key, name varchar(10), username varchar(10), Admin bool, time varchar(14),  feature BLOB)"))
        qDebug() << "bin表已存在" << endl;

    model=new QSqlTableModel();
    model->setTable("binFile");
    model->setSort(0, Qt::AscendingOrder);
    // 这里的setHeaderData只是设置表头，而和数据库显示哪几行没有任何关系，如果不设置则按照默认显示
    model->setHeaderData(1, Qt::Horizontal, "文件");
    model->setHeaderData(2, Qt::Horizontal, "用户");
    model->setHeaderData(3, Qt::Horizontal, "权限");
    model->setHeaderData(4, Qt::Horizontal, "时间");
    model->select();

    ui->SqlShowView->setModel(model);
    ui->SqlShowView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->SqlShowView->hideColumn(5);
    ui->SqlShowView->resizeColumnsToContents();

    // 用户库
    query=QSqlQuery(db);
    if(!query.exec("CREATE TABLE userTable(id integer primary key, username varchar(10), password varchar(10), Admin bool)"))
        qDebug() << "用户表已存在";
    else
    {
        query.prepare("INSERT INTO userTable(id, username, password, Admin) VALUES(:id, :username, :password, :Admin)");
        query.bindValue(":username", "root");
        query.bindValue(":password", "123456");
        query.bindValue(":Admin", true);
        qDebug() << "插入表状态" << query.exec();
    }
    this->setWindowIcon(QIcon(":/qss/icon.ico"));
    DisableAll();

    userLogin=new LoginDialog(&db);
    connect(userLogin, SIGNAL(loginSuccess(QString,bool)), this, SLOT(loginSuccess(QString,bool)));
    userLogin->exec();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serialConnect()
{
    if(ui->SerialConnectButton->text()==tr("连接"))
    {
        if(ui->PortBox->count()==0)
        {
            ui->SerialScreenText->append("没有符合要求的CH340串口");
            return;
        }
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            if(info.portName()+" CH340 "==ui->PortBox->currentText())
            {
                MySerialPort->setPortName(info.portName());
                break;
            }
        }
        MySerialPort->setBaudRate(ui->BaudRateBox->currentText().toUInt());

        int databitString=ui->DataBox->currentText().toUInt();
        switch (databitString)
        {
        case 5:
            MySerialPort->setDataBits(QSerialPort::Data5);
            break;
        case 6:
            MySerialPort->setDataBits(QSerialPort::Data6);
            break;
        case 7:
            MySerialPort->setDataBits(QSerialPort::Data7);
            break;
        case 8:
            MySerialPort->setDataBits(QSerialPort::Data8);
            break;

        }

        QString parityString=ui->CheckBox->currentText();
        if(parityString==tr("无校验"))
        {
            MySerialPort->setParity(QSerialPort::NoParity);
        }
        else if(parityString==tr("奇校验"))
        {
            MySerialPort->setParity(QSerialPort::OddParity);
        }
        else if(parityString==tr("偶校验"))
        {
            MySerialPort->setParity(QSerialPort::EvenParity);
        }

        QString stopbitString=ui->StopBox->currentText();
        if(stopbitString==tr("1位"))
        {
            MySerialPort->setStopBits(QSerialPort::OneStop);
        }
        else if(stopbitString==tr("1.5位"))
        {
            MySerialPort->setStopBits(QSerialPort::OneAndHalfStop);
        }
        else if(stopbitString==tr("2位"))
        {
            MySerialPort->setStopBits(QSerialPort::TwoStop);
        }

        QString flowcontrolString=ui->FluidBox->currentText();

        if(flowcontrolString==tr("无流控"))
        {
            MySerialPort->setFlowControl(QSerialPort::NoFlowControl);
        }
        else if(flowcontrolString==tr("硬件流"))
        {
            MySerialPort->setFlowControl(QSerialPort::HardwareControl);
        }
        else if(flowcontrolString==tr("软件流"))
        {
            MySerialPort->setFlowControl(QSerialPort::SoftwareControl);
        }

        if(MySerialPort->open(QIODevice::ReadWrite)) // 串口打开成功
        {
            ui->PortBox->setEnabled(false);
            ui->BaudRateBox->setEnabled(false);
            ui->DataBox->setEnabled(false);
            ui->CheckBox->setEnabled(false);
            ui->StopBox->setEnabled(false);
            ui->FluidBox->setEnabled(false);
            ui->SerialSendButton->setEnabled(true);
            ui->Download2stmButton->setEnabled(true);  // 这里还要改，只有管理员账户才能生效
            ui->SerialConnectButton->setText(tr("断开"));
            ui->SerialScreenText->append("串口已打开");
        }
        else  // 串口打开失败
            ui->SerialScreenText->append("串口打开失败，请检车设置");
    }
    else if(ui->SerialConnectButton->text()==tr("断开"))
    {
        MySerialPort->close();
        ui->PortBox->setEnabled(true);
        ui->BaudRateBox->setEnabled(true);
        ui->DataBox->setEnabled(true);
        ui->CheckBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        ui->FluidBox->setEnabled(true);
        ui->SerialSendButton->setEnabled(false);
        ui->Download2stmButton->setEnabled(false);  // 这里还要改，只有管理员账户才能生效
        ui->SerialConnectButton->setText(tr("连接"));
        ui->SerialScreenText->append("串口已关闭");
    }
}

void MainWindow::serialPortUpdate()
{
    if(SerialPortCount!=QSerialPortInfo::availablePorts().count()) // 串口数量有变化
    {
        ui->PortBox->clear();
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            for(int i=0;i<ui->PortBox->count();i++) //如果所有串口都已存在则返回
            {
                if(info.portName()+" CH340 "==ui->PortBox->itemText(i))
                    return;
            }
            if(info.description() == "USB-SERIAL CH340")
                ui->PortBox->addItem(info.portName()+" CH340 ");
        }
    }
}

void MainWindow::clearSerialText()
{
    ui->SerialScreenText->clear();
}

void MainWindow::serialSend()
{
    QByteArray text=ui->SerialSendLine->text().toLatin1();
    MySerialPort->write(text, text.length());
    ui->SerialSendLine->clear();
}

void MainWindow::serialReceive()
{
    QByteArray text=MySerialPort->readAll();
    ui->SerialScreenText->setText(ui->SerialScreenText->toPlainText()+QString(text));
    ui->SerialScreenText->moveCursor(QTextCursor::End);
}

void MainWindow::yModemSend()
{
    int currentRow=ui->SqlShowView->currentIndex().row();
    if(currentRow<0)
    {
        ui->SqlText->append("There is no data selected!");
        return;
    }
    ui->SqlText->append("select Row: " + QString::number(currentRow));

    QModelIndex index=model->index(currentRow, 0);
    int id=model->data(index).toInt();

    QModelIndex fea=model->index(currentRow, 5);
    QByteArray bin=model->data(fea).toByteArray();
    qDebug() << bin.length() << endl;
    ui->SqlText->append("select ID : " + QString::number(id));

    QModelIndex name=model->index(currentRow, 1);
    QString filename=model->data(name).toString();


    disconnect(MySerialPort, SIGNAL(readyRead()),this,SLOT(serialReceive()));
    MyYModem=new YModem(bin,filename, ui->Download2stmBar, ui->SqlText, this);
    MyYModem->SetPort(MySerialPort);
    connect(MyYModem,SIGNAL(sgn_ftpEnd()),this,SLOT(yModemEnd()));
    MyYModem->YModem_send_Handle();

}

void MainWindow::yModemEnd()
{
    disconnect(MyYModem,SIGNAL(sgn_ftpEnd()),this,SLOT(yModemEnd()));
    connect(MySerialPort, SIGNAL(readyRead()),this,SLOT(serialReceive()));
    ui->SqlText->append("已下载到单片机！");
    delete MyYModem;
}

void MainWindow::downloadPathSelect()
{
    QString filepath = QFileDialog::getExistingDirectory();
    ui->DownloadPath->setText(filepath);
}

void MainWindow::uploadPathSelect()
{
    QString filePath = QCoreApplication::applicationDirPath();
    QString filename = QFileDialog::getOpenFileName(this, tr("选择目标bin文件"), filePath, tr("bin文件(*bin)"));
    ui->UpLoadPath->setText(filename);
}

void MainWindow::uploadBin2Database()
{
    if(ui->UpLoadPath->text().length()==0)
    {
        ui->SqlText->append("上传前请选择文件");
        return;
    }
    // 判断对应的表是否已经创建
    QDateTime current_time=QDateTime::currentDateTime();
    QString thistime=current_time.toString("yyyyMMddhhmmss");

    QFile *ftpfile=new QFile(ui->UpLoadPath->text());
    QFileInfo fi=QFileInfo(ui->UpLoadPath->text());
    QString filename=fi.fileName(); // 获取文件名，不包含路径
    if (!ftpfile->open(QFile::ReadOnly)){     //不能带QFile::Text，因为文本格式是不会去读0x0D的，导致读取到的数据会将0x0D去除掉
        qDebug()<<"Open file err";
    }
    QByteArray array=ftpfile->readAll(); // 获取到了bin文件的内容
    ftpfile->close();

    query=QSqlQuery(db);
    query.prepare("INSERT INTO binFile(id, name, username, Admin, time, feature) VALUES(:id, :name, :username, :Admin, :time, :feature)");
    query.bindValue(":name", filename);
    query.bindValue(":username", ui->UserNameLabel->text());
    query.bindValue(":Admin", IsAdmin);
    query.bindValue(":time", thistime);
    query.bindValue(":feature", array);
    qDebug() << "插入表状态" << query.exec();

    delete model;
    model=new QSqlTableModel();
    model->setTable("binFile");
    model->setSort(0, Qt::AscendingOrder);
    // 这里的setHeaderData只是设置表头，而和数据库显示哪几行没有任何关系，如果不设置则按照默认显示
    model->setHeaderData(1, Qt::Horizontal, "文件");
    model->setHeaderData(2, Qt::Horizontal, "用户");
    model->setHeaderData(3, Qt::Horizontal, "权限");
    model->setHeaderData(4, Qt::Horizontal, "时间");
    model->select();

    ui->SqlShowView->setModel(model);
    ui->SqlShowView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->SqlShowView->hideColumn(5);
    ui->SqlShowView->resizeColumnsToContents();
}

void MainWindow::downloadBinFromDatabase()
{
    int currentRow=ui->SqlShowView->currentIndex().row();
    if(currentRow<0)
    {
        ui->SqlText->append("There is no data selected!");
        return;
    }
    ui->SqlText->append("select Row: " + QString::number(currentRow));
    QModelIndex index=model->index(ui->SqlShowView->currentIndex().row(), 0);
    int id=model->data(index).toInt();
    QModelIndex fea=model->index(ui->SqlShowView->currentIndex().row(), 5);
    QByteArray bin=model->data(fea).toByteArray();
    qDebug() << bin.length() << endl;
    ui->SqlText->append("select ID : " + QString::number(id));

    QDateTime current_time=QDateTime::currentDateTime();
    QString thistime=current_time.toString("yyyyMMddhhmmss");
    QString dictory=QCoreApplication::applicationDirPath();
    if(ui->DownloadPath->text().length()) // 如果额外设置了路径，就用设置路径，否则就是软件路径
        dictory=ui->DownloadPath->text();
    QFile *myBinFile=new QFile(dictory + "/" + thistime + ".bin");
    myBinFile->open(QIODevice::WriteOnly);
    int writeBit = myBinFile->write(bin);
    ui->SqlText->append(QString::number(writeBit) + " bytes has been written!");
    myBinFile->close();
}
void MainWindow::deleteBinFromDatabase()
{
    int currentRow=ui->SqlShowView->currentIndex().row();
    if(currentRow<0)
    {
        ui->SqlText->append("There is no data selected!");
        return;
    }
    ui->SqlText->append("select Row: " + QString::number(currentRow));
    QModelIndex index=model->index(ui->SqlShowView->currentIndex().row(), 0);
    int id=model->data(index).toInt();
    ui->SqlText->append("select ID : " + QString::number(id));

    query=QSqlQuery(db);
    if(query.exec("DELETE FROM binFile WHERE  id = " + QString::number(id))) // 判断是否删除成功
    {
        ui->SqlText->append("Delete succeed!");
    }
    else
    {
        ui->SqlText->append("Delete failed!");
        return;
    }

    delete model;
    model=new QSqlTableModel();
    model->setTable("binFile");
    model->setSort(0, Qt::AscendingOrder);
    // 这里的setHeaderData只是设置表头，而和数据库显示哪几行没有任何关系，如果不设置则按照默认显示
    model->setHeaderData(1, Qt::Horizontal, "文件");
    model->setHeaderData(2, Qt::Horizontal, "用户");
    model->setHeaderData(3, Qt::Horizontal, "权限");
    model->setHeaderData(4, Qt::Horizontal, "时间");
    model->select();

    ui->SqlShowView->setModel(model);
    ui->SqlShowView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->SqlShowView->hideColumn(5);
    ui->SqlShowView->resizeColumnsToContents();
}

void MainWindow::socketConnect()
{
    if(ServerClientGroup->checkedButton()==ui->ServerRadioButton)
    {
        if(ifConnected==0) // server模式没有连接过,此时要连接
        {
            ui->SocketConnectButton->setText("正在连接");
            ui->ClientIP->setDisabled(true);
            ui->ClientRadioButton->setDisabled(true);
            ui->ServerRadioButton->setDisabled(true);
            ui->ClientRadioButton->setDisabled(true);
            ui->PortSpinBox->setDisabled(true);
            ui->ClientIP->setDisabled(true);

            connect(MyServer, &QTcpServer::newConnection, this, &MainWindow::serverNewConnect);
            if(!MyServer->listen(QHostAddress::Any, ui->PortSpinBox->value())) // 开始监听连接
            {
                qDebug() << "ifconnect set to be 0" << endl;
                ifConnected=0;
                ui->SocketConnectButton->setText("点击连接");
                ui->ClientIP->setEnabled(true);
                ui->ClientRadioButton->setEnabled(true);
                ui->ServerRadioButton->setEnabled(true);
                ui->ClientRadioButton->setEnabled(true);
                ui->PortSpinBox->setEnabled(true);
                ui->ClientIP->setEnabled(true);
                ui->SocketSendButton->setDisabled(true);

                qDebug()<<MyServer->errorString();    //错误信息
            }
        }
        else
            ServerSocket->disconnectFromHost();
    }
    else  // 客户端模式
    {
        if(MySocket->state()==QAbstractSocket::UnconnectedState)
            MySocket->connectToHost(ui->ClientIP->text(), ui->PortSpinBox->value());
        else if(MySocket->state()==QAbstractSocket::ConnectedState)
            MySocket->disconnectFromHost();
    }
}

void MainWindow::socketDisconnect()
{
    ui->SocketConnectButton->setText("点击连接");
    ui->ClientIP->setEnabled(true);
    ui->ClientRadioButton->setEnabled(true);
    ui->ServerRadioButton->setEnabled(true);
    ui->ClientRadioButton->setEnabled(true);
    ui->PortSpinBox->setEnabled(true);
    ui->ClientIP->setEnabled(true);
    ui->SocketSendButton->setDisabled(true);
    MyServer->disconnect();
    MyServer->close();
    ifConnected=0;  // 在监听中，准备重新连接
}

void MainWindow::serverNewConnect()
{
    ui->SocketConnectButton->setText("点击断开");
    ui->ClientIP->setDisabled(true);
    ui->ClientRadioButton->setDisabled(true);
    ui->ServerRadioButton->setDisabled(true);
    ui->ClientRadioButton->setDisabled(true);
    ui->PortSpinBox->setDisabled(true);
    ui->ClientIP->setDisabled(true);
    ui->SocketSendButton->setEnabled(true);

    ServerSocket=MyServer->nextPendingConnection();
    connect(ServerSocket, &QTcpSocket::disconnected, this, &MainWindow::socketDisconnect);
    connect(ServerSocket, &QTcpSocket::readyRead, this, &MainWindow::socketRecFile);
    ifConnected=1; // 连接上了
}

void MainWindow::socketSendFile()
{
    QTcpSocket *nowSocket;
    if(ServerClientGroup->checkedButton()==ui->ServerRadioButton)
        nowSocket=ServerSocket;
    else
        nowSocket=MySocket;
    if(nowSocket->state() == QAbstractSocket::ConnectedState)
    {
        ui->SocketTextOutput->append("开始发送文件！");
        ui->SocketBar->setValue(0);

        int currentRow=ui->SqlShowView->currentIndex().row();
        if(currentRow<0)
        {
            ui->SqlText->append("There is no data selected!");
            return;
        }
        ui->SqlText->append("select Row: " + QString::number(currentRow));

        QModelIndex index=model->index(currentRow, 0);
        int id=model->data(index).toInt();

        QModelIndex fea=model->index(currentRow, 5);
        QByteArray bin=model->data(fea).toByteArray();
        qDebug() << bin.length() << endl;
        ui->SqlText->append("select ID : " + QString::number(id));

        nowSocket->write(bin,bin.length());
        nowSocket->waitForBytesWritten();

        ui->SocketTextOutput->append("文件发送完成！");
        ui->SocketBar->setValue(100);
    }
}

void MainWindow::socketSetRecPath()
{
    QString filepath = QFileDialog::getExistingDirectory();
    ui->SocketReceivePath->setText(filepath);
}

void MainWindow::socketRecFile()
{
    QTcpSocket *nowSocket;
    if(ServerClientGroup->checkedButton()==ui->ServerRadioButton)
        nowSocket=ServerSocket;
    else
        nowSocket=MySocket;
    if(nowSocket->state() == QAbstractSocket::ConnectedState)
    {
        QByteArray bytes=NULL;
        while(nowSocket->waitForReadyRead(1000))
        {
            qDebug() << "receiving" <<endl;
            bytes.append((QByteArray)nowSocket->readAll());
        }
        qDebug() << "receive " << bytes.length() << endl;
        if(bytes.length()==0)
        {
            ui->SocketTextOutput->append("Received 0 byte(s), none to save!");
            return;
        }
        QDateTime current_time=QDateTime::currentDateTime();
        QString thistime=current_time.toString("yyyyMMddhhmmss");
        QString dictory=QCoreApplication::applicationDirPath();
        if(ui->SocketReceivePath->text().length()) // 如果额外设置了路径，就用设置路径，否则就是软件路径
            dictory=ui->SocketReceivePath->text();
        QFile *myBinFile=new QFile(dictory + "/" + thistime + ".bin");
        myBinFile->open(QIODevice::WriteOnly);
        int writeBit = myBinFile->write(bytes);
        ui->SocketTextOutput->append(QString::number(writeBit) + " bytes has been written!");
        myBinFile->close();
    }
}

void MainWindow::onSocketStateChange(QAbstractSocket::SocketState socketState)
{
    switch(socketState)
    {
    case QAbstractSocket::UnconnectedState:
        ui->SocketConnectButton->setText("点击连接");
        ui->ClientIP->setEnabled(true);
        ui->ClientRadioButton->setEnabled(true);
        ui->ServerRadioButton->setEnabled(true);
        ui->ClientRadioButton->setEnabled(true);
        ui->PortSpinBox->setEnabled(true);
        ui->ClientIP->setEnabled(true);
        ui->SocketSendButton->setDisabled(true);
        break;
    case QAbstractSocket::ConnectingState:
        ui->SocketConnectButton->setText("正在连接");
        ui->ClientIP->setDisabled(true);
        ui->ClientRadioButton->setDisabled(true);
        ui->ServerRadioButton->setDisabled(true);
        ui->ClientRadioButton->setDisabled(true);
        ui->PortSpinBox->setDisabled(true);
        ui->ClientIP->setDisabled(true);
        ui->SocketSendButton->setDisabled(true);
        break;
    case QAbstractSocket::ConnectedState:
        ui->SocketConnectButton->setText("点击断开");
        ui->ClientIP->setDisabled(true);
        ui->ClientRadioButton->setDisabled(true);
        ui->ServerRadioButton->setDisabled(true);
        ui->ClientRadioButton->setDisabled(true);
        ui->PortSpinBox->setDisabled(true);
        ui->ClientIP->setDisabled(true);
        ui->SocketSendButton->setEnabled(true);
        break;
    default:
        break;
    }
}

QString MainWindow::getLocalIP()
{
    QString hostName=QHostInfo::localHostName();//本地主机名
    QHostInfo   hostInfo=QHostInfo::fromName(hostName);
    QString   localIP="";

    QList<QHostAddress> addList=hostInfo.addresses();//

    if (!addList.isEmpty())
        for (int i=0;i<addList.count();i++)
        {
            QHostAddress aHost=addList.at(i);
            if (QAbstractSocket::IPv4Protocol==aHost.protocol())
            {
                localIP=aHost.toString();
                break;
            }
        }
    return localIP;
}


void MainWindow::loginSuccess(QString name, bool isadmin)
{

    ui->UserNameLabel->setText(name);
    if(isadmin)
    {
        ui->IsAdminLabel->setText("管理员用户");
        EnableForAdminUser();
    }
    else
    {
        ui->IsAdminLabel->setText("普通用户");
        EnableForAdminUser();
        EnableForNormalUser();
    }
    IsAdmin=isadmin;
}


void MainWindow::DisableAll()
{
    ui->centralwidget->setDisabled(true);
}
void MainWindow::EnableForNormalUser()
{
    ui->SerialGroup->setDisabled(true);
    ui->DisplayGriup->setDisabled(true);
    ui->DeleteButton->setDisabled(true);
}
void MainWindow::EnableForAdminUser()
{
    ui->centralwidget->setEnabled(true);
}
