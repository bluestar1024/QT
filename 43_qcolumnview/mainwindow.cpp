#include "mainwindow.h"
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    columnView = new QColumnView;
    this->setCentralWidget(columnView);

    QStandardItemModel *sdiModel = new QStandardItemModel;

    QStandardItem *school = new QStandardItem(QStringLiteral("第一中学"));
    QStandardItem *grade1 = new QStandardItem(QStringLiteral("高一"));
    QStandardItem *grade2 = new QStandardItem(QStringLiteral("高二"));
    QStandardItem *grade3 = new QStandardItem(QStringLiteral("高三"));
    QStandardItem *class1 = new QStandardItem(QStringLiteral("高一(13)班"));
    QStandardItem *class2 = new QStandardItem(QStringLiteral("高二(5)班"));
    QStandardItem *class3 = new QStandardItem(QStringLiteral("高三(3)班"));

    sdiModel->setHorizontalHeaderLabels(QStringList() << QStringLiteral("学校")
                                                      << QStringLiteral("年级")
                                                      << QStringLiteral("班级"));

    school->appendRow(grade1);
    school->appendRow(grade2);
    school->appendRow(grade3);
    grade1->appendRow(class1);
    grade2->appendRow(class2);
    grade3->appendRow(class3);
    sdiModel->appendRow(school);

    columnView->setModel(sdiModel);
}

MainWindow::~MainWindow()
{
}

