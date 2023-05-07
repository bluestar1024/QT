#include "mainwindow.h"
#include <QHostInfo>
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    textBrowser = new QTextBrowser();
    pushButton1 = new QPushButton();
    pushButton2 = new QPushButton();
    mainWidget = new QWidget();
    pushButtonWidget = new QWidget();
    mainVLayout = new QVBoxLayout();
    subHLayout = new QHBoxLayout();
    timer = new QTimer();

    pushButton1->setText("获取主机信息");
    pushButton2->setText("清除文本信息");
    pushButton1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pushButton2->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(mainVLayout);
    mainVLayout->addWidget(textBrowser);
    mainVLayout->addWidget(pushButtonWidget);
    pushButtonWidget->setLayout(subHLayout);
    subHLayout->addWidget(pushButton1);
    subHLayout->addWidget(pushButton2);

    connect(pushButton1, SIGNAL(clicked()), this, SLOT(timerStart()));
    connect(pushButton2, SIGNAL(clicked()), this, SLOT(clearTextInfo()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
}

MainWindow::~MainWindow()
{
}

QString MainWindow::getHostInfo()
{
    QString str = "主机名称:" + QHostInfo::localHostName() + "\n";

    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface interface, interfaceList)
    {
        str += "网络设备:" + interface.name() + "\n";
        str += "MAC地址:" + interface.hardwareAddress() + "\n";

        QList<QNetworkAddressEntry> addressList = interface.addressEntries();
        foreach(QNetworkAddressEntry address, addressList)
        {
            if(address.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                str += "IP地址:" + address.ip().toString() + "\n";
                str += "子网掩码:" + address.netmask().toString() + "\n";
                str += "广播地址:" + address.broadcast().toString() + "\n\n";
            }
        }
    }

    return str;
}

void MainWindow::showHostInfo()
{
    textBrowser->insertPlainText(getHostInfo());
}

void MainWindow::timerStart()
{
    textBrowser->clear();
    timer->start(1000);
}

void MainWindow::timerTimeout()
{
    timer->stop();
    showHostInfo();
}

void MainWindow::clearTextInfo()
{
    if(!textBrowser->toPlainText().isEmpty())
        textBrowser->clear();
}

