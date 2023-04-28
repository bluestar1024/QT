#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    dialogButtonBox = new QDialogButtonBox(this);
    dialogButtonBox->setGeometry(300, 200, 150, 30);
    //dialogButtonBox->setGeometry(0, 0, 400, 200);
    //dialogButtonBox->setStyleSheet("QDialogButtonBox { background-color: rgba(200, 10, 10, 100%); }");
    dialogButtonBox->addButton(QDialogButtonBox::Cancel);
    //dialogButtonBox->button(QDialogButtonBox::Cancel)->setGeometry(0, 0, 200, 150);
    dialogButtonBox->button(QDialogButtonBox::Cancel)->setStyleSheet("QPushButton { background-color: rgba(200, 200, 10, 100%); }");
    dialogButtonBox->button(QDialogButtonBox::Cancel)->setText("取消");

    pushButton = new QPushButton("自定义");
    //pushButton->setGeometry(250, 0, 100, 50);
    pushButton->setStyleSheet("QPushButton { background-color: rgba(200, 200, 10, 100%); }");
    dialogButtonBox->addButton(pushButton, QDialogButtonBox::ActionRole);

    connect(dialogButtonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(dialogButtonBoxClick(QAbstractButton *)));
}

void MainWindow::dialogButtonBoxClick(QAbstractButton *button)
{
    if(button == dialogButtonBox->button(QDialogButtonBox::Cancel))
        qDebug() << "单击了取消按键" << endl;
    else if(button == pushButton)
        qDebug() << "单击了自定义按键" << endl;
}

MainWindow::~MainWindow()
{
}

