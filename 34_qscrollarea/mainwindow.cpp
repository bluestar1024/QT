#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    scrollArea = new QScrollArea(this);
    scrollArea->setGeometry(200, 100, 600, 400);

    label = new QLabel(this);
    QImage image(":/images/bulestar.png");
    label->setPixmap(QPixmap::fromImage(image));

    scrollArea->setWidget(label);
}

MainWindow::~MainWindow()
{
}

