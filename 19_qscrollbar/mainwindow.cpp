#include "mainwindow.h"
#include <Qt>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    scrollBarHor = new QScrollBar(Qt::Horizontal,  this);
    scrollBarVer = new QScrollBar(Qt::Vertical, this);
    label = new QLabel(this);

    scrollBarHor->setGeometry(0, 550, 1024, 50);
    scrollBarVer->setGeometry(970, 0, 50, 550);
    label->setGeometry(400, 250, 100, 50);

    scrollBarHor->setStyleSheet("QScrollBar { background-color: rgba(150, 150, 150, 100%); }");
    scrollBarVer->setStyleSheet("QScrollBar { background-color: rgba(150, 150, 150, 100%); }");
    label->setStyleSheet("QLabel { background-color: rgba(100, 100, 100, 100%); }");

    label->setText("文本初始内容");
}

MainWindow::~MainWindow()
{
}

