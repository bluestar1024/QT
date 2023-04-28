#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    textEdit = new QTextEdit(this);
    pushButtonSelectAll = new QPushButton(this);
    pushButtonClearAll = new QPushButton(this);

    textEdit->setGeometry(0, 0, 1024, 480);
    pushButtonSelectAll->setGeometry(200, 500, 100, 50);
    pushButtonClearAll->setGeometry(500, 500, 100, 50);

    textEdit->setStyleSheet("QTextEdit { background-color: rgba(10, 200, 10, 100%); }");
    pushButtonSelectAll->setStyleSheet("QPushButton { background-color: rgba(100, 10, 200, 100%); }");
    pushButtonClearAll->setStyleSheet("QPushButton { background-color: rgba(100, 10, 200, 100%); }");

    textEdit->setText("文本初始内容");
    pushButtonSelectAll->setText("全选");
    pushButtonClearAll->setText("清除");

    connect(pushButtonSelectAll, SIGNAL(clicked()), this, SLOT(pushButtonSelectAllClick()));
    connect(pushButtonClearAll, SIGNAL(clicked()), this, SLOT(pushButtonClearAllClick()));
}

void MainWindow::pushButtonSelectAllClick()
{
    textEdit->setFocus();
    if(!textEdit->toPlainText().isEmpty())
        textEdit->selectAll();
}
void MainWindow::pushButtonClearAllClick()
{
    textEdit->clear();
}

MainWindow::~MainWindow()
{
}

