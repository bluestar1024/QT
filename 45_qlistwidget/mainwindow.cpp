#include "mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    listWidget = new QListWidget(this);
    listWidget->setGeometry(0, 0, 512, 600);
    listWidget->addItem("请单击右边的添加项添加文件");

    pushButton = new QPushButton(this);
    pushButton->setGeometry(568, 400, 400, 100);
    pushButton->setText("添加项");

    connect(pushButton, SIGNAL(clicked()), this, SLOT(pushButtonClick()));
}

void MainWindow::pushButtonClick()
{
    QString fileName = QFileDialog::getOpenFileName(this, "添加项", "", "Files(*.mp3)");
    if(NULL != fileName)
        listWidget->addItem(fileName);
}

MainWindow::~MainWindow()
{
}

