#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    listView = new QListView(this);
    this->setCentralWidget(listView);

    QStringList strList;
    strList << "高三(1)班" << "高三(2)班" << "高三(3)班";

    stringListModel = new QStringListModel(strList);

    listView->setModel(stringListModel);
    listView->setViewMode(QListView::IconMode);
    listView->setDragEnabled(false);
}

MainWindow::~MainWindow()
{
}

