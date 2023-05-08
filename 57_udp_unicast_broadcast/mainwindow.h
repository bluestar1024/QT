#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QTextBrowser>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QHostAddress>
#include <QWidget>
#include <QBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QUdpSocket *udpSocket;
    QTextBrowser *textBrowser;
    QPushButton *pushButton[5];
    QLabel *label[3];
    QComboBox *comboBox;
    QSpinBox *spinBox[2];
    QLineEdit *lineEdit;
    QList<QHostAddress> IPList;
    QWidget *mainWidget;
    QWidget *subWidget[3];
    QVBoxLayout *mainVLayout;
    QHBoxLayout *subHLayout[3];
    void getLocalHostIP();

private slots:
    void bindPort();
    void unbindPort();
    void clearTextBrowser();
    void sendMessage();
    void sendBroadMessage();
    void recvMessage();
    void socketStateChange(QAbstractSocket::SocketState);
};
#endif // MAINWINDOW_H
