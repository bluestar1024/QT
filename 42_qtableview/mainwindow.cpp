#include "mainwindow.h"
#include <QStandardItemModel>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    tableView = new QTableView(this);
    this->setCentralWidget(tableView);
    tableView->setShowGrid(true);

    QStandardItemModel *sdiModel = new QStandardItemModel();
    QString str = "数学,英语,语文,物理,化学,生物,历史,政治,地理";
    QStringList strList = str.simplified().split(",");
    sdiModel->setHorizontalHeaderLabels(strList);

    QStandardItem *item = NULL;
    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            item = new QStandardItem("99");
            sdiModel->setItem(i, j, item);
        }
    }

    tableView->setModel(sdiModel);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
}

