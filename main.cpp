#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qssFile(":/qss/style.qss");
    qssFile.open(QFile::ReadOnly); //以只读方式打开
    if(qssFile.isOpen())
    {
        QString qss = QLatin1String(qssFile.readAll());
        a.setStyleSheet(qss);
        qssFile.close();
    }
    else
    {
        qDebug() << "无法打开文件";
    }

    MainWindow w;
    w.show();
    return a.exec();
}
