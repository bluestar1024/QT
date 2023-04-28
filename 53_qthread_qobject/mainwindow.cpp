#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    pushButton1 = new QPushButton(this);
    pushButton2 = new QPushButton(this);
    pushButton1->setGeometry(0, 0, 100, 50);
    pushButton2->setGeometry(100, 0, 100, 50);
    pushButton1->setText("开启线程");
    pushButton2->setText("打断线程");

    worker = new Worker();
    worker->moveToThread(&workThread);

    connect(pushButton1, SIGNAL(clicked()), this, SLOT(pushButton1Click()));
    connect(pushButton2, SIGNAL(clicked()), this, SLOT(pushButton2Click()));
    connect(this, SIGNAL(startWork(const QString &)), worker, SLOT(doWork1(const QString &)));
    connect(worker, SIGNAL(workResult(const QString &)), this, SLOT(handleResult(const QString &)));
    connect(&workThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(&workThread, SIGNAL(finished()), &workThread, SLOT(deleteLater()));
}

MainWindow::~MainWindow()
{
    worker->stopWork();
    workThread.quit();

    if(workThread.wait(2000))
        qDebug() << "线程结束" << endl;
}

void MainWindow::pushButton1Click()
{
    const QString str = "正在运行";
    if(!workThread.isRunning())
        workThread.start();
    emit startWork(str);
}

void MainWindow::pushButton2Click()
{
    if(workThread.isRunning())
        worker->stopWork();
}

void MainWindow::handleResult(const QString &str)
{
    qDebug() << "线程的状态：" << str << endl;
}

