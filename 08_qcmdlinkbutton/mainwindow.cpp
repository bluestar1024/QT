#include "mainwindow.h"
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    cmdLinkButton1 = new QCommandLinkButton("打开/home目录", "点击就能打开/home目录", this);
    cmdLinkButton2 = new QCommandLinkButton("打开百度浏览器", "点击就能打开百度浏览器", this);

    cmdLinkButton1->setGeometry(300, 200, 200, 50);
    cmdLinkButton2->setGeometry(300, 300, 200, 50);

    cmdLinkButton1->setStyleSheet("QCommandLinkButton { background-color: rgba(200, 200, 10, 100%); }");
    cmdLinkButton2->setStyleSheet("QCommandLinkButton { background-color: rgba(200, 200, 10, 100%); }");

    connect(cmdLinkButton1, SIGNAL(clicked()), this, SLOT(cmdLinkButton1Click()));
    connect(cmdLinkButton2, SIGNAL(clicked()), this, SLOT(cmdLinkButton2Click()));
}

void MainWindow::cmdLinkButton1Click()
{
    QDesktopServices::openUrl(QUrl("file:////home/"));
}
void MainWindow::cmdLinkButton2Click()
{
    QDesktopServices::openUrl(QUrl("https://www.baidu.com/"));
}

MainWindow::~MainWindow()
{
}

