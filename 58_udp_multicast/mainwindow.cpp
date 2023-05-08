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
    label[0] = new QLabel();
    label[1] = new QLabel();
    label[2] = new QLabel();
    comboBox[0] = new QComboBox();
    comboBox[1] = new QComboBox();
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

    pushButton[0]->setText("加入组播");
    pushButton[1]->setText("退出组播");
    pushButton[2]->setText("清除文本");
    pushButton[3]->setText("组播消息");
    pushButton[1]->setEnabled(false);
    label[0]->setText("本地IP地址:");
    label[1]->setText("组播IP地址:");
    label[2]->setText("端口:");
    label[0]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    label[1]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    label[2]->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    comboBox[1]->addItem("239.255.0.255");
    comboBox[1]->setEditable(true);
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
    subHLayout[0]->addWidget(comboBox[0]);
    subHLayout[0]->addWidget(label[1]);
    subHLayout[0]->addWidget(comboBox[1]);
    subHLayout[0]->addWidget(label[2]);
    subHLayout[0]->addWidget(spinBox);
    subHLayout[1]->addWidget(pushButton[0]);
    subHLayout[1]->addWidget(pushButton[1]);
    subHLayout[1]->addWidget(pushButton[2]);
    subHLayout[2]->addWidget(lineEdit);
    subHLayout[2]->addWidget(pushButton[3]);

    getLocalHostIP();

    connect(pushButton[0], SIGNAL(clicked()), this, SLOT(joinGroup()));
    connect(pushButton[1], SIGNAL(clicked()), this, SLOT(leaveGroup()));
    connect(pushButton[2], SIGNAL(clicked()), this, SLOT(clearTextBrowser()));
    connect(pushButton[3], SIGNAL(clicked()), this, SLOT(sendMessage()));
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
                if((address.ip().protocol() == QAbstractSocket::IPv4Protocol) &&
                    (!address.ip().isLoopback()))
                {
                    comboBox[0]->addItem(address.ip().toString());
                    IPList << address.ip();
                }
            }
        }
}

void MainWindow::joinGroup()
{
    if(udpSocket->state() != QAbstractSocket::UnconnectedState)
        udpSocket->close();
    udpSocket->bind(QHostAddress::AnyIPv4, spinBox->value(), QAbstractSocket::ShareAddress);

    QHostAddress groupAddress = QHostAddress(comboBox[1]->currentText());
    bool ok = udpSocket->joinMulticastGroup(groupAddress);
    textBrowser->append(ok ? "成功加入组播" : "加入组播失败");
    textBrowser->append("组播IP地址:" + groupAddress.toString());
    textBrowser->append("端口" + spinBox->text());

    pushButton[0]->setEnabled(false);
    pushButton[1]->setEnabled(true);
    comboBox[0]->setEnabled(false);
    comboBox[1]->setEnabled(false);
    spinBox->setEnabled(false);
}

void MainWindow::leaveGroup()
{
    QHostAddress groupAddress = QHostAddress(comboBox[1]->currentText());
    bool ok = udpSocket->leaveMulticastGroup(groupAddress);
    textBrowser->append(ok ? "成功退出组播" : "退出组播失败");
    udpSocket->abort();

    pushButton[0]->setEnabled(true);
    pushButton[1]->setEnabled(false);
    comboBox[0]->setEnabled(true);
    comboBox[1]->setEnabled(true);
    spinBox->setEnabled(true);
}

void MainWindow::clearTextBrowser()
{
    textBrowser->clear();
}

void MainWindow::sendMessage()
{
    QHostAddress groupAddress = QHostAddress(comboBox[1]->currentText());
    udpSocket->writeDatagram(lineEdit->text().toUtf8(), groupAddress, spinBox->value());

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
                            + dataGram);
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

