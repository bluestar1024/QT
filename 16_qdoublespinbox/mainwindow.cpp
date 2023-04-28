#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    doubleSpinBox = new QDoubleSpinBox(this);
    doubleSpinBox->setGeometry((this->width() - 250) / 2, (this->height() - 50) / 2, 250, 50);
    doubleSpinBox->setStyleSheet("QDoubleSpinBox { background-color: rgba(10, 200, 10, 100%); }");
    doubleSpinBox->setPrefix("窗口大小");
    doubleSpinBox->setSuffix("%");
    doubleSpinBox->setRange(50.0, 100.0);
    doubleSpinBox->setSingleStep(0.1);
    doubleSpinBox->setValue(100.0);

    connect(doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinBoxValueChange(double)));
}

void MainWindow::doubleSpinBoxValueChange(double value)
{
    int w = 1024 * value / 100;
    int h = 600 * value / 100;
    this->setGeometry(100, 100, w, h);
    doubleSpinBox->setGeometry((this->width() - 250) / 2, (this->height() - 50) / 2, 250, 50);
}

MainWindow::~MainWindow()
{
}

