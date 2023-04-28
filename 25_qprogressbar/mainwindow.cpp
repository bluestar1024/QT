#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    progressBar = new QProgressBar(this);
    progressBar->setGeometry(300, 200, 400, 120);

    progressBar->setRange(0, 100);
    value = 0;
    progressBar->setValue(value++);
    progressBar->setFormat("当前进度%p%");

    timer = new QTimer(this);
    timer->start(100);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeOut()));
}

void MainWindow::timerTimeOut()
{
    progressBar->setValue(value++);
    if(value > 100)
        value = 0;
}

MainWindow::~MainWindow()
{
}

