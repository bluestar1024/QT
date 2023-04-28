#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    dial = new QDial(this);
    dial->setGeometry(300, 80, 400, 400);
    dial->setStyleSheet("QDial { background-color: rgba(10, 200, 10, 100%); }");

    dial->setRange(0, 100);
    dial->setPageStep(10);
    dial->setNotchTarget(1.0);
    dial->setNotchesVisible(true);
    //dial->setWrapping(true);

    label = new QLabel(this);
    label->setGeometry(420, 500, 100, 50);
    label->setStyleSheet("QLabel { background-color: rgba(100, 100, 100, 100%); }");
    label->setText("0km/h");

    connect(dial, SIGNAL(valueChanged(int)), this, SLOT(dialValueChange(int)));
}

void MainWindow::dialValueChange(int value)
{
    label->setText(QString::number(value) + "km/h");
}

MainWindow::~MainWindow()
{
}

