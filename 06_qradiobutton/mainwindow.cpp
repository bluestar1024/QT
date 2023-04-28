#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);
    this->setStyleSheet("QMainWindow { background-color: rgba(250, 250, 10, 100%); }");

    radioButton1 = new QRadioButton(this);
    radioButton2 = new QRadioButton(this);
    radioButton3 = new QRadioButton(this);
    radioButton4 = new QRadioButton(this);

    radioButton1->setStyleSheet("QRadioButton { background-color: rgba(250, 250, 250, 100%); }");
    radioButton2->setStyleSheet("QRadioButton { background-color: rgba(250, 10, 250, 100%); }");
    radioButton3->setStyleSheet("QRadioButton { background-color: rgba(10, 250, 10, 100%); }");
    radioButton4->setStyleSheet("QRadioButton { background-color: rgba(250, 10, 10, 100%); }");

    radioButton1->setGeometry(300, 200, 100, 50);
    radioButton2->setGeometry(400, 200, 100, 50);
    radioButton3->setGeometry(500, 200, 100, 50);
    radioButton4->setGeometry(600, 200, 100, 50);

    radioButton1->setText("选项一");
    radioButton2->setText("选项二");
    radioButton3->setText("选项三");
    radioButton4->setText("选项四");

    radioButton1->setChecked(false);
    radioButton2->setChecked(false);
    radioButton3->setChecked(false);
    radioButton4->setChecked(false);
}

MainWindow::~MainWindow()
{
}

