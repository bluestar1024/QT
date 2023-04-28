#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    tableWidget = new QTableWidget(this);
    this->setCentralWidget(tableWidget);
    tableWidget->setRowCount(2);
    tableWidget->setColumnCount(2);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "姓名" << "性别");

    QList <QString>str;
    str << "小明" << "男" << "小红" << "女";

    for(int i = 0; i < 4; i++)
    {
        tableWidgetItem[i] = new QTableWidgetItem(str[i]);
        tableWidgetItem[i]->setTextAlignment(Qt::AlignCenter);
    }

    tableWidget->setItem(0, 0, tableWidgetItem[0]);
    tableWidget->setItem(0, 1, tableWidgetItem[1]);
    tableWidget->setItem(1, 0, tableWidgetItem[2]);
    tableWidget->setItem(1, 1, tableWidgetItem[3]);
}

MainWindow::~MainWindow()
{
}

