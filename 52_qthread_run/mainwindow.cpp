#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    workThread = new WorkThread();
    pushButton = new QPushButton(this);

    pushButton->resize(100, 50);
    pushButton->setText("创建线程");

    connect(pushButton, SIGNAL(clicked()), this, SLOT(pushButtonClick()));
    connect(workThread, SIGNAL(runStatusSignal(const QString &)), this, SLOT(handleRunStatusSignal(const QString &)));
}

MainWindow::~MainWindow()
{
    workThread->quit();

    if(workThread->wait(1000))
        qDebug() << "线程结束" << endl;
    else
        qDebug() << "线程未结束" << endl;
}

void MainWindow::pushButtonClick()
{
    if(!workThread->isRunning())
        workThread->start();
}

void MainWindow::handleRunStatusSignal(const QString &str)
{
    qDebug() << str << endl;
}

