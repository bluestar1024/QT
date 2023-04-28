#include "mainwindow.h"
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    lineEdit = new QLineEdit(this);
    pushButton = new QPushButton(this);
    label = new QLabel(this);

    lineEdit->setGeometry(300, 200, 400, 50);
    pushButton->setGeometry(750, 200, 100, 50);
    label->setGeometry(300, 300, 600, 50);

    lineEdit->setStyleSheet("QLineEdit { background-color: rgba(10, 200, 10, 100%); }");
    pushButton->setStyleSheet("QPushButton { background-color: rgba(100, 10, 200, 100%); }");
    label->setStyleSheet("QLabel { background-color: rgba(10, 200, 10, 100%); }");

    lineEdit->setText("请输入网址");
    pushButton->setText("确认");
    label->setText("你输入的网址为:");

    connect(pushButton, SIGNAL(clicked()), this, SLOT(pushButtonClick()));
}

void MainWindow::pushButtonClick()
{
    label->setText("你输入的网址为:" + lineEdit->text());
    QDesktopServices::openUrl(QUrl(lineEdit->text()));
    lineEdit->clear();
}

MainWindow::~MainWindow()
{
}

