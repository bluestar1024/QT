#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    treeWidget = new QTreeWidget(this);
    this->setCentralWidget(treeWidget);
    treeWidget->clear();

    QList <QString>famous;
    famous << "圣人" << "高人";
    QList <QString>person1;
    person1 << "墨子" << "王阳明";
    QList <QString>person2;
    person2 << "嬴政" << "韩信" << "诸葛亮";

    for(int i = 0; i < 2; i++)
    {
        parentItem[i] = new QTreeWidgetItem(treeWidget);
        parentItem[i]->setText(0, famous[i]);
        parentItem[i]->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        parentItem[i]->setCheckState(0, Qt::Unchecked);
        if(0 == i)
        {
            for(int j = 0; j < 2; j++)
            {
                subItem1[j] = new QTreeWidgetItem(parentItem[i]);
                subItem1[j]->setText(0, person1[j]);
                subItem1[j]->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem1[j]->setCheckState(0, Qt::Unchecked);
            }
        }
        if(1 == i)
        {
            for(int j = 0; j < 3; j++)
            {
                subItem2[j] = new QTreeWidgetItem(parentItem[i]);
                subItem2[j]->setText(0, person2[j]);
                subItem2[j]->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                subItem2[j]->setCheckState(0, Qt::Unchecked);
            }
        }
    }

    connect(treeWidget, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(treeItemChange(QTreeWidgetItem *, int)));
}

void MainWindow::updateParentState(QTreeWidgetItem *item)
{
    QTreeWidgetItem *parent = item->parent();
    if(NULL == parent)
        return;
    int count = parent->childCount();
    int checkCount = 0;

    for(int i = 0; i < count; i++)
    {
        if(Qt::Checked == parent->child(i)->checkState(0))
            checkCount++;
    }

    if(checkCount <= 0)
        parent->setCheckState(0, Qt::Unchecked);
    if((checkCount > 0) && (checkCount < count))
        parent->setCheckState(0, Qt::PartiallyChecked);
    if(checkCount == count)
        parent->setCheckState(0, Qt::Checked);
}

void MainWindow::treeItemChange(QTreeWidgetItem *item, int)
{
    int count = item->childCount();
    if(count > 0)
    {
        if(Qt::Checked == item->checkState(0))
        {
            for(int i = 0; i < count; i++)
                item->child(i)->setCheckState(0, Qt::Checked);
        }
        if(Qt::Unchecked == item->checkState(0))
        {
            for(int i = 0; i < count; i++)
                item->child(i)->setCheckState(0, Qt::Unchecked);
        }
    }
    else
        updateParentState(item);
}

MainWindow::~MainWindow()
{
}

