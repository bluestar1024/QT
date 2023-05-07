#include "mainwindow.h"
#include <QNetworkInterface>
#include <QHostInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    tcpServer = new QTcpServer(this);
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

    pushButton[0]->setText("开始监听");
    pushButton[1]->setText("停止监听");
    pushButton[2]->setText("清空文本");
    pushButton[3]->setText("发送消息");
    pushButton[1]->setEnabled(false);

    label[0]->setText("监听IP地址");
    label[1]->setText("监听端口");
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

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));
    connect(pushButton[0], SIGNAL(clicked()), this, SLOT(startListen()));
    connect(pushButton[1], SIGNAL(clicked()), this, SLOT(stopListen()));
    connect(pushButton[2], SIGNAL(clicked()), this, SLOT(clearTextBrowser()));
    connect(pushButton[3], SIGNAL(clicked()), this, SLOT(sendMessage()));
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

void MainWindow::clientConnected()
{
    tcpSocket = tcpServer->nextPendingConnection();
    QString ip = tcpSocket->peerAddress().toString();
    quint16 port = tcpSocket->peerPort();

    textBrowser->append("客户端已连接");
    textBrowser->append("客户端IP地址:" + ip);
    textBrowser->append("客户端端口号:" + QString::number(port));

    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(recvMessage()));
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socketStateChange(QAbstractSocket::SocketState)));
}

void MainWindow::startListen()
{
    if(comboBox->currentIndex() != -1)
    {
        if(tcpSocket->state() != QTcpSocket::ConnectedState)
            tcpServer->listen(IPList[comboBox->currentIndex()], spinBox->value());

        pushButton[0]->setEnabled(false);
        pushButton[1]->setEnabled(true);
        comboBox->setEnabled(false);
        spinBox->setEnabled(false);

        textBrowser->append("正在监听服务器IP地址:" + comboBox->currentText());
        textBrowser->append("正在监听服务器端口:" + spinBox->text());
    }
}

void MainWindow::stopListen()
{
    tcpServer->close();

    if(tcpSocket->state() == QTcpSocket::ConnectedState)
        tcpSocket->disconnectFromHost();

    pushButton[0]->setEnabled(true);
    pushButton[1]->setEnabled(false);
    comboBox->setEnabled(true);
    spinBox->setEnabled(true);

    textBrowser->append("已停止监听服务器IP地址:" + comboBox->currentText());
    textBrowser->append("已停止监听服务器端口:" + spinBox->text());
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
        textBrowser->append("服务端:" + lineEdit->text());
    }
}

void MainWindow::recvMessage()
{
    textBrowser->append("客户端:" + tcpSocket->readAll());
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

