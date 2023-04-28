#include "mainwindow.h"
#include <QDir>
#include <QCoreApplication>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    plainTextEdit = new QPlainTextEdit(this);
    radioButton = new QRadioButton(this);

    plainTextEdit->setGeometry(0, 100, 1024, 500);
    radioButton->setGeometry(800, 50, 100, 50);

    plainTextEdit->setStyleSheet("QPlainTextEdit { background-color: rgba(10, 200, 10, 100%); }");
    radioButton->setStyleSheet("QRadioButton { background-color: rgba(100, 10, 200, 100%); }");

    radioButton->setText("只读模式");

    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QFile file("moc_mainwindow.cpp");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    plainTextEdit->insertPlainText(in.readAll());

    connect(radioButton, SIGNAL(clicked()), this, SLOT(radioButtonClick()));
}

void MainWindow::radioButtonClick()
{
    if(radioButton->isChecked())
        plainTextEdit->setReadOnly(true);
    else
        plainTextEdit->setReadOnly(false);
}

MainWindow::~MainWindow()
{
}

