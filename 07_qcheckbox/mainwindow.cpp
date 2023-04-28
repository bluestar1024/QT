#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);
    //this->setStyleSheet("QMainWindow { background-color: rgba(250, 10, 250, 100%); }");

    checkBox1 = new QCheckBox(this);
    checkBox2 = new QCheckBox(this);

    checkBox1->setGeometry(300, 200, 100, 50);
    checkBox2->setGeometry(400, 200, 100, 50);

    checkBox1->setStyleSheet("QCheckBox { background-color: rgba(250, 250, 10, 100%); }");
    checkBox2->setStyleSheet("QCheckBox { background-color: rgba(10, 200, 10, 100%); }");

    checkBox1->setText("选项一");
    checkBox2->setText("选项二");

    checkBox1->setCheckState(Qt::Unchecked);
    checkBox2->setCheckState(Qt::Unchecked);

    checkBox1->setTristate();
    checkBox2->setTristate();

    connect(checkBox1, SIGNAL(stateChanged(int)), this, SLOT(checkBox1Click(int)));
    connect(checkBox2, SIGNAL(stateChanged(int)), this, SLOT(checkBox2Click(int)));
}

void MainWindow::checkBox1Click(int state)
{
    switch(state)
    {
        case Qt::Unchecked:
            checkBox1->setText("不选");
            break;
        case Qt::PartiallyChecked:
            checkBox1->setText("半选");
            break;
        case Qt::Checked:
            checkBox1->setText("全选");
            break;
        default:
            break;
    }
}
void MainWindow::checkBox2Click(int state)
{
    switch(state)
    {
        case Qt::Unchecked:
            checkBox2->setText("不选");
            break;
        case Qt::PartiallyChecked:
            checkBox2->setText("半选");
            break;
        case Qt::Checked:
            checkBox2->setText("全选");
            break;
        default:
            break;
    }
}

MainWindow::~MainWindow()
{
}

