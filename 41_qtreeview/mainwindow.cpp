#include "mainwindow.h"
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    treeView = new QTreeView(this);
    this->setCentralWidget(treeView);

    QStandardItemModel *sdiModel = new QStandardItemModel(treeView);
    sdiModel->setHorizontalHeaderLabels(QStringList() << QStringLiteral("标题")
                                                            << QStringLiteral("名称"));

    for(int i = 0; i < 5; i++)
    {
        QList <QStandardItem *>items1;
        QStandardItem *item1 = new QStandardItem(QString().number(i));
        QStandardItem *item2 = new QStandardItem(QStringLiteral("一级标题"));
        items1.append(item1);
        items1.append(item2);
        sdiModel->appendRow(items1);
        for(int j = 0; j < 5; j++)
        {
            QList <QStandardItem *>items2;
            QStandardItem *item3 = new QStandardItem(QString().number(j));
            QStandardItem *item4 = new QStandardItem(QStringLiteral("二级标题"));
            items2.append(item3);
            items2.append(item4);
            item1->appendRow(items2);
        }
    }

    treeView->setModel(sdiModel);
}

MainWindow::~MainWindow()
{
}

