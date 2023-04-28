#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    spinBox = new QSpinBox(this);
    spinBox->setGeometry(300, 200, 250, 50);
    spinBox->setStyleSheet("QSpinBox { background-color: rgba(10, 200, 10, 100%); }");
    spinBox->setRange(0, 100);
    spinBox->setSingleStep(10);
    spinBox->setValue(100);
    spinBox->setSuffix("%不透明度");

    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(spinBoxValueChange(int)));
}

void MainWindow::spinBoxValueChange(int opacity)
{
    double doubleopacity = (double)opacity / 100;
    this->setWindowOpacity(doubleopacity);
}

MainWindow::~MainWindow()
{
}

