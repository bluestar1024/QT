#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    comboBox = new QComboBox(this);
    comboBox->setGeometry(300, 200, 80, 40);
    comboBox->setStyleSheet("QComboBox { background-color: rgba(10, 200, 10, 100%); }");
    comboBox->addItem("晚风");
    comboBox->addItem("月亮");
    comboBox->addItem("树影");
    comboBox->addItem("碎叶");
    comboBox->addItem("轻声");

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(comboBoxIndexChange(int)));
}

void MainWindow::comboBoxIndexChange(int index)
{
    qDebug() << "最美风景之一:" << comboBox->itemText(index) << endl;
}

MainWindow::~MainWindow()
{
}

