#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(700, 350, 1024, 600);
    pushButton1 = new QPushButton("窗口皮肤1", this);
    pushButton2 = new QPushButton("窗口皮肤2", this);
    pushButton3 = new QPushButton("按钮皮肤1", this);
    pushButton4 = new QPushButton("按钮皮肤2", this);
    pushButton1->setGeometry(350, 360, 100, 60);
    pushButton2->setGeometry(574, 360, 100, 60);
    pushButton3->setGeometry(800, 210, 100, 60);
    pushButton4->setGeometry(800, 330, 100, 60);

    connect(pushButton1, SIGNAL(clicked()), this, SLOT(pushButton1ChangeColor()));
    connect(pushButton2, SIGNAL(clicked()), this, SLOT(pushButton2ChangeColor()));
    connect(pushButton3, SIGNAL(clicked()), this, SLOT(pushButton3ChangeColor()));
    connect(pushButton4, SIGNAL(clicked()), this, SLOT(pushButton4ChangeColor()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::pushButton1ChangeColor()
{
    this->setStyleSheet("QMainWindow { background-color: rgba(10, 250, 20, 100%); }");
}
void MainWindow::pushButton2ChangeColor()
{
    this->setStyleSheet("QMainWindow { background-color: rgba(10, 20, 250, 100%); }");
}
void MainWindow::pushButton3ChangeColor()
{
    pushButton1->setStyleSheet("QPushButton { background-color: rgba(250, 10, 10, 100%); }");
    pushButton2->setStyleSheet("QPushButton { background-color: rgba(250, 10, 10, 100%); }");
    pushButton3->setStyleSheet("QPushButton { background-color: rgba(250, 10, 10, 100%); }");
    pushButton4->setStyleSheet("QPushButton { background-color: rgba(250, 10, 10, 100%); }");
}
void MainWindow::pushButton4ChangeColor()
{
    pushButton1->setStyleSheet("QPushButton { background-color: rgba(250, 250, 10, 100%); }");
    pushButton2->setStyleSheet("QPushButton { background-color: rgba(250, 250, 10, 100%); }");
    pushButton3->setStyleSheet("QPushButton { background-color: rgba(250, 250, 10, 100%); }");
    pushButton4->setStyleSheet("QPushButton { background-color: rgba(250, 250, 10, 100%); }");
}
