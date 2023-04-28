#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    widget = new QWidget(this);
    this->setCentralWidget(widget);
    hLayout = new QHBoxLayout();
    listWidget = new QListWidget();
    stackWidget = new QStackedWidget();

    QList <QString>listList;
    listList << "窗口一" << "窗口二" << "窗口三";

    QList <QString>labelList;
    labelList << "标签一" << "标签二" << "标签三";

    for(int i = 0; i < 3; i++)
        listWidget->insertItem(i, listList[i]);

    for(int i = 0; i < 3; i++)
    {
        label[i] = new QLabel();
        label[i]->setText(labelList[i]);
        label[i]->setAlignment(Qt::AlignCenter);

        stackWidget->addWidget(label[i]);
    }

    listWidget->setMaximumWidth(160);
    hLayout->addWidget(listWidget);
    hLayout->addWidget(stackWidget);
    widget->setLayout(hLayout);

    connect(listWidget, SIGNAL(currentRowChanged(int)), stackWidget, SLOT(setCurrentIndex(int)));
}

MainWindow::~MainWindow()
{
}

