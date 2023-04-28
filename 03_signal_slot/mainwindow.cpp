#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(1024,600);
    pushButton = new QPushButton(this);
    pushButton->setText("我是个按钮");

    connect(pushButton, SIGNAL(clicked()), this, SLOT(buttonTextClick()));
    connect(this, SIGNAL(buttonTextChangeSignal()), this, SLOT(buttonTextChange()));

    n = 0;
}

MainWindow::~MainWindow()
{
}

void MainWindow::buttonTextClick()
{
    n++;
    emit buttonTextChangeSignal();
}

void MainWindow::buttonTextChange()
{
    QString string1, string2;
    string2 = string1.number(n);
    pushButton->setText("我被点击了" + string2 + "次");
}
