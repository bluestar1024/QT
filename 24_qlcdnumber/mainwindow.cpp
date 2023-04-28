#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    lcdNumber = new QLCDNumber(this);
    lcdNumber->setGeometry(200, 150, 600, 300);
    lcdNumber->setDigitCount(8);
    lcdNumber->setSegmentStyle(QLCDNumber::Flat);

    QTime time = QTime::currentTime();
    lcdNumber->display(time.toString("hh:mm:ss"));

    timer = new QTimer(this);
    timer->start(1000);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeOut()));
}

void MainWindow::timerTimeOut()
{
    QTime time = QTime::currentTime();
    lcdNumber->display(time.toString("hh:mm:ss"));
}

MainWindow::~MainWindow()
{
}

