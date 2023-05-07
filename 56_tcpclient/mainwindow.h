#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextBrowser>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QWidget>
#include <QBoxLayout>
#include <QHostAddress>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTcpSocket *tcpSocket;
    QTextBrowser *textBrowser;
    QPushButton *pushButton[4];
    QLabel *label[2];
    QComboBox *comboBox;
    QSpinBox *spinBox;
    QLineEdit *lineEdit;
    QWidget *mainWidget;
    QWidget *subWidget[3];
    QVBoxLayout *mainVLayout;
    QHBoxLayout *subHLayout[3];
    QList<QHostAddress> IPList;
    void getHostIP();

private slots:
    void toConnect();
    void toDisconnect();
    void clearTextBrowser();
    void sendMessage();
    void connected();
    void disconnected();
    void recvMessage();
    void socketStateChange(QAbstractSocket::SocketState);
};
#endif // MAINWINDOW_H
