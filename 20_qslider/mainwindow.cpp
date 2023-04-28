#include "mainwindow.h"
#include <Qt>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    sliderHor = new QSlider(Qt::Horizontal, this);
    sliderVer = new QSlider(Qt::Vertical, this);
    label = new QLabel(this);

    sliderHor->setGeometry(300, 150, 200, 30);
    sliderVer->setGeometry(300, 200, 30, 200);
    label->setGeometry(450, 250, 100, 50);

    sliderHor->setStyleSheet("QSlider { background-color: rgba(100, 10, 200, 100%); }");
    sliderVer->setStyleSheet("QSlider { background-color: rgba(100, 10, 200, 100%); }");
    label->setStyleSheet("QLabel { background-color: rgba(100, 100, 100, 100%); }");

    sliderHor->setRange(0, 100);
    sliderVer->setRange(0, 100);

    label->setText("滑条值:0");

    connect(sliderHor, SIGNAL(valueChanged(int)), this, SLOT(sliderHorValueChange(int)));
    connect(sliderVer, SIGNAL(valueChanged(int)), this, SLOT(sliderVerValueChange(int)));
}

void MainWindow::sliderHorValueChange(int val)
{
    sliderVer->setSliderPosition(val);
    label->setText("滑条值:" + QString::number(val));
}
void MainWindow::sliderVerValueChange(int val)
{
    sliderHor->setSliderPosition(val);
}

MainWindow::~MainWindow()
{
}

