#include "mainwindow.h"
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    udpSocket = new QUdpSocket(this);
    textBrowser = new QTextBrowser();
    pushButton[0] = new QPushButton();
    pushButton[1] = new QPushButton();
    pushButton[2] = new QPushButton();
    pushButton[3] = new QPushButton();
    pushButton[4] = new QPushButton();
    label[0] = new QLabel();
    label[1] = new QLabel();
    label[2] = new QLabel();
    comboBox = new QComboBox();
    spinBox[0] = new QSpinBox();
    spinBox[1] = new QSpinBox();
    lineEdit = new QLineEdit();
    mainWidget = new QWidget();
    subWidget[0] = new QWidget();
    subWidget[1] = new QWidget();
    subWidget[2] = new QWidget();
    mainVLayout = new QVBoxLayout();
    subHLayout[0] = new QHBoxLayout();
    subHLayout[1] = new QHBoxLayout();
    subHLayout[2] = new QHBoxLayout();

    pushButton[0]->setText("绑定端口");
    pushButton[1]->setText("解除绑定");
    pushButton[2]->setText("清除文本");
    pushButton[3]->setText("发送消息");
    pushButton[4]->setText("广播消息");
    pushButton[1]->setEnabled(false);
    label[0]->setText("目标IP地址:");
    label[1]->setText("绑定端口:");
    label[2]->setText("目标端口:");
    label[0]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    label[1]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    label[2]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    spinBox[0]->setRange(10000, 99999);
    spinBox[1]->setRange(10000, 99999);

    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(mainVLayout);
    mainVLayout->addWidget(textBrowser);
    mainVLayout->addWidget(subWidget[0]);
    mainVLayout->addWidget(subWidget[1]);
    mainVLayout->addWidget(subWidget[2]);
    subWidget[0]->setLayout(subHLayout[0]);
    subWidget[1]->setLayout(subHLayout[1]);
    subWidget[2]->setLayout(subHLayout[2]);
    subHLayout[0]->addWidget(label[0]);
    subHLayout[0]->addWidget(comboBox);
    subHLayout[0]->addWidget(label[1]);
    subHLayout[0]->addWidget(spinBox[0]);
    subHLayout[0]->addWidget(label[2]);
    subHLayout[0]->addWidget(spinBox[1]);
    subHLayout[1]->addWidget(pushButton[0]);
    subHLayout[1]->addWidget(pushButton[1]);
    subHLayout[1]->addWidget(pushButton[2]);
    subHLayout[2]->addWidget(lineEdit);
    subHLayout[2]->addWidget(pushButton[3]);
    subHLayout[2]->addWidget(pushButton[4]);

    getLocalHostIP();

    connect(pushButton[0], SIGNAL(clicked()), this, SLOT(bindPort()));
    connect(pushButton[1], SIGNAL(clicked()), this, SLOT(unbindPort()));
    connect(pushButton[2], SIGNAL(clicked()), this, SLOT(clearTextBrowser()));
    connect(pushButton[3], SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(pushButton[4], SIGNAL(clicked()), this, SLOT(sendBroadMessage()));
    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(recvMessage()));
    connect(udpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socketStateChange(QAbstractSocket::SocketState)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::getLocalHostIP()
{
    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface interface, interfaceList)
    {
        QList<QNetworkAddressEntry> addressList = interface.addressEntries();
        foreach(QNetworkAddressEntry address, addressList)
        {
            if(address.ip().protocol() == QAbstractSocket::IPv4Protocol)
            {
                comboBox->addItem(address.ip().toString());
                IPList << address.ip();
            }
        }
    }
}

void MainWindow::bindPort()
{
    if(udpSocket->state() == QAbstractSocket::ConnectedState)
        udpSocket->close();
    udpSocket->bind(spinBox[0]->value());

    pushButton[0]->setEnabled(false);
    pushButton[1]->setEnabled(true);
    comboBox->setEnabled(false);
    spinBox[0]->setEnabled(false);
    spinBox[1]->setEnabled(false);

    textBrowser->append("已绑定端口");
}

void MainWindow::unbindPort()
{
    udpSocket->abort();

    pushButton[0]->setEnabled(true);
    pushButton[1]->setEnabled(false);
    comboBox->setEnabled(true);
    spinBox[0]->setEnabled(true);
    spinBox[1]->setEnabled(true);

    textBrowser->append("已解绑端口");
}

void MainWindow::clearTextBrowser()
{
    textBrowser->clear();
}

void MainWindow::sendMessage()
{
    udpSocket->writeDatagram(lineEdit->text().toUtf8().data(),
                             lineEdit->text().toUtf8().size(),
                             IPList[comboBox->currentIndex()],
                             spinBox[1]->value());

    textBrowser->append("发送:" + lineEdit->text());
}

void MainWindow::sendBroadMessage()
{
    udpSocket->writeDatagram(lineEdit->text().toUtf8().data(),
                             lineEdit->text().toUtf8().size(),
                             QHostAddress::Broadcast,
                             spinBox[1]->value());

    textBrowser->append("发送:" + lineEdit->text());
}

void MainWindow::recvMessage()
{
    QByteArray dataGram;
    QHostAddress address;
    quint16 port;

    while(udpSocket->hasPendingDatagrams())
    {
        dataGram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(dataGram.data(), dataGram.size(),
                                &address, &port);

        textBrowser->append("接收:" + address.toString() + ":" + QString::number(port) + ":"
                            + dataGram.data());
    }
}

void MainWindow::socketStateChange(QAbstractSocket::SocketState state)
{
    switch(state)
    {
        case QAbstractSocket::ConnectedState:
        textBrowser->append("socket状态:ConnectedState");
        break;
        case QAbstractSocket::UnconnectedState:
        textBrowser->append("socket状态:UnconnectedState");
        break;
        case QAbstractSocket::ConnectingState:
        textBrowser->append("socket状态:ConnectingState");
        break;
        case QAbstractSocket::HostLookupState:
        textBrowser->append("socket状态:HostLookupState");
        break;
        case QAbstractSocket::BoundState:
        textBrowser->append("socket状态:BoundState");
        break;
        case QAbstractSocket::ListeningState:
        textBrowser->append("socket状态:ListeningState");
        break;
        case QAbstractSocket::ClosingState:
        textBrowser->append("socket状态:ClosingState");
        break;
        default:
        break;
    }
}

