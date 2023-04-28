#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    fWidget = new QWidget(this);
    fWidget->setGeometry(300, 200, 300, 100);
    fWidget->setStyleSheet("QWidget { background-color: rgba(200, 200, 200, 100%); }");

    userName = new QLineEdit();
    passWord = new QLineEdit();

    formLayout = new QFormLayout();

    formLayout->addRow("用户名:", userName);
    formLayout->addRow("密码    :", passWord);

    formLayout->setSpacing(10);
    formLayout->setMargin(20);

    fWidget->setLayout(formLayout);
}

MainWindow::~MainWindow()
{
}

