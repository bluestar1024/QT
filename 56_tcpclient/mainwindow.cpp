#include "mainwindow.h"
#include <QNetworkInterface>
#include <QHostInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    tcpSocket = new QTcpSocket(this);
    textBrowser = new QTextBrowser();
    pushButton[0] = new QPushButton();
    pushButton[1] = new QPushButton();
    pushButton[2] = new QPushButton();
    pushButton[3] = new QPushButton();
    label[0] = new QLabel();
    label[1] = new QLabel();
    comboBox = new QComboBox();
    spinBox = new QSpinBox();
    lineEdit = new QLineEdit();
    mainWidget = new QWidget();
    subWidget[0] = new QWidget();
    subWidget[1] = new QWidget();
    subWidget[2] = new QWidget();
    mainVLayout = new QVBoxLayout();
    subHLayout[0] = new QHBoxLayout();
    subHLayout[1] = new QHBoxLayout();
    subHLayout[2] = new QHBoxLayout();

    pushButton[0]->setText("连接服务器");
    pushButton[1]->setText("断开连接");
    pushButton[2]->setText("清空文本");
    pushButton[3]->setText("发送消息");
    pushButton[1]->setEnabled(false);

    label[0]->setText("服务器IP地址");
    label[1]->setText("服务器端口");
    label[0]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    label[1]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    spinBox->setRange(10000, 99999);

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
    subHLayout[0]->addWidget(spinBox);
    subHLayout[1]->addWidget(pushButton[0]);
    subHLayout[1]->addWidget(pushButton[1]);
    subHLayout[1]->addWidget(pushButton[2]);
    subHLayout[2]->addWidget(lineEdit);
    subHLayout[2]->addWidget(pushButton[3]);

    getHostIP();

    connect(pushButton[0], SIGNAL(clicked()), this, SLOT(toConnect()));
    connect(pushButton[1], SIGNAL(clicked()), this, SLOT(toDisconnect()));
    connect(pushButton[2], SIGNAL(clicked()), this, SLOT(clearTextBrowser()));
    connect(pushButton[3], SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(recvMessage()));
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socketStateChange(QAbstractSocket::SocketState)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::getHostIP()
{
#if 0
    QString hostName = QHostInfo::localHostName();
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    IPList << hostInfo.addresses();
    qDebug() << IPList << endl;
    foreach(QHostAddress ip, IPList)
    {
        if(ip.protocol() == QAbstractSocket::IPv4Protocol)
            comboBox->addItem(ip.toString());
    }
#endif
#if 1
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
#endif
}

void MainWindow::toConnect()
{
    if(tcpSocket->state() != QTcpSocket::ConnectedState)
        tcpSocket->connectToHost(IPList[comboBox->currentIndex()], spinBox->value());
}

void MainWindow::toDisconnect()
{
    tcpSocket->disconnectFromHost();

    tcpSocket->close();
}

void MainWindow::clearTextBrowser()
{
    textBrowser->clear();
}

void MainWindow::sendMessage()
{
    if(NULL == tcpSocket)
        return;

    if(tcpSocket->state() == QTcpSocket::ConnectedState)
    {
        tcpSocket->write(lineEdit->text().toUtf8());
        textBrowser->append("客户端:" + lineEdit->text());
    }
}

void MainWindow::connected()
{
    textBrowser->append("已经连上服务端");

    pushButton[0]->setEnabled(false);
    pushButton[1]->setEnabled(true);
    comboBox->setEnabled(false);
    spinBox->setEnabled(false);
}

void MainWindow::disconnected()
{
    textBrowser->append("已经断开服务端");

    pushButton[0]->setEnabled(true);
    pushButton[1]->setEnabled(false);
    comboBox->setEnabled(true);
    spinBox->setEnabled(true);
}

void MainWindow::recvMessage()
{
    textBrowser->append("服务端:" + tcpSocket->readAll());
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

