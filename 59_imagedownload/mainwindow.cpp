#include "mainwindow.h"
#include <QMessageBox> 
#include <QNetworkRequest>
#include <QCoreApplication>
#include <QFile>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);
    
    networkAccessManager = new QNetworkAccessManager(this);
    label[0] = new QLabel();
    label[1] = new QLabel();
    label[2] = new QLabel();
    pushButton = new QPushButton();
    lineEdit = new QLineEdit();
    progressBar = new QProgressBar();
    mainWidget = new QWidget();
    subWidget[0] = new QWidget();
    subWidget[1] = new QWidget();
    mainVLayout = new QVBoxLayout();
    subHLayout[0] = new QHBoxLayout();
    subHLayout[1] = new QHBoxLayout();
    
    label[1]->setText("URL链接:");
    label[2]->setText("文件下载进度:");
    label[0]->setMinimumSize(this->width(), this->height() * 0.75);
    label[1]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    label[2]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pushButton->setText("下载");
    lineEdit->setText("https://img1.baidu.com/it/u=3908406816,"
                      "2850982836&fm=253&fmt=auto&app=120&f=JPEG?w=889&h=500");
    
    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(mainVLayout);
    mainVLayout->addWidget(label[0]);
    mainVLayout->addWidget(subWidget[0]);
    mainVLayout->addWidget(subWidget[1]);
    subWidget[0]->setLayout(subHLayout[0]);
    subWidget[1]->setLayout(subHLayout[1]);
    subHLayout[0]->addWidget(label[1]);
    subHLayout[0]->addWidget(lineEdit);
    subHLayout[0]->addWidget(pushButton);
    subHLayout[1]->addWidget(label[2]);
    subHLayout[1]->addWidget(progressBar);
    
    connect(pushButton, SIGNAL(clicked()), this, SLOT(startDownload()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::startDownload()
{
    QUrl newUrl(QUrl(lineEdit->text()));
    if(!newUrl.isValid())
    {
        QMessageBox::information(this, "error", "invalid url");
        return;
    }
    
    QNetworkRequest networkRequest;
    networkRequest.setUrl(newUrl);
    QNetworkReply *reply = networkAccessManager->get(networkRequest);

    pushButton->setEnabled(false);
    
    connect(reply, SIGNAL(finished()), this, SLOT(replyFinish()));
    //connect(reply, SIGNAL(readyRead()), this, SLOT(readyReadData()));
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)),
            this, SLOT(imageDownloadProgress(qint64, qint64)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(networkReplyError(QNetworkReply::NetworkError)));
}

void MainWindow::readyReadData()
{
    QFile imageFile;
    imageFile.setFileName(QCoreApplication::applicationDirPath() + "/下载.jpg");
    if(imageFile.exists())
        imageFile.remove();
    
    QNetworkReply *reply = (QNetworkReply *)sender();
    QByteArray data = reply->readAll();
    if(data.isEmpty())
    {
        qDebug() << "data is empty" << endl;
        return;
    }
    /*if(!(data[0] == (char)0xff && data[1] == (char)0xd8
         && data[data.size() - 2] == (char)0xff
         && data[data.size() - 1] == (char)0xd9))
    {
        qDebug() << "image is not jpg" << endl;
        return;
    }*/

    QPixmap pixmap;
    bool ok = pixmap.loadFromData(data);
    ok ? qDebug() << "生成成功" << endl : qDebug() << "生成失败" << endl;
    ok = pixmap.save(imageFile.fileName());
    ok ? qDebug() << "保存成功" << endl : qDebug() << "保存失败" << endl;
    //bool ok = pixmap.loadFromData(data);
    //ok ? qDebug() << "生成成功" << endl : qDebug() << "生成失败" << endl;
    //ok = pixmap.save(QCoreApplication::applicationDirPath() + "/下载.jpg");
    //ok ? qDebug() << "保存成功" << endl : qDebug() << "保存失败" << endl;
}

void MainWindow::replyFinish()
{
    QNetworkReply *reply = (QNetworkReply *)sender();
    reply->deleteLater();

    readyReadData();

    QFile imageFile;
    imageFile.setFileName(QCoreApplication::applicationDirPath() + "/下载.jpg");
    if(imageFile.exists())
    {
        label[0]->setPixmap(QPixmap(imageFile.fileName()));
        qDebug() << "已经成功下载，文件路径为:" << imageFile.fileName() << endl;
    }
    else
        label[0]->clear();

    pushButton->setEnabled(true);
}

void MainWindow::imageDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    progressBar->setRange(0, bytesTotal);
    progressBar->setValue(bytesReceived);
}

void MainWindow::networkReplyError(QNetworkReply::NetworkError error)
{
    switch(error)
    {
        case QNetworkReply::ConnectionRefusedError:
            qDebug() << "error状态:连接拒绝" << endl;
        break;
        case QNetworkReply::RemoteHostClosedError:
            qDebug() << "error状态:远程主机关闭" << endl;
        break;
        case QNetworkReply::HostNotFoundError:
            qDebug() << "error状态:找不到主机" << endl;
        break;
        case QNetworkReply::TimeoutError:
            qDebug() << "error状态:超时" << endl;
        break;
        default:
        break;
    }
}

