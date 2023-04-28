#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    QPixmap pixmap(":images/openedv.png");

    labelImage = new QLabel(this);
    labelImage->setGeometry(300, 200, 452, 132);
    labelImage->setPixmap(pixmap);
    labelImage->setScaledContents(true);

    labelString = new QLabel(this);
    labelString->setGeometry(480, 360, 100, 50);
    labelString->setText("标签演示文本");
}

MainWindow::~MainWindow()
{
}

