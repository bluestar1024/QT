#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 600, 0);

    widget = new QWidget(this);
    this->setCentralWidget(widget);

    hSpacerItem = new QSpacerItem(50, 220, QSizePolicy::Fixed, QSizePolicy::Fixed);
    vSpacerItem = new QSpacerItem(180, 80, QSizePolicy::Fixed, QSizePolicy::Fixed);

    mainBoxLayout = new QHBoxLayout();
    hBoxLayout = new QHBoxLayout();
    vBoxLayout = new QVBoxLayout();

    hBoxLayout->addSpacerItem(hSpacerItem);
    vBoxLayout->addSpacerItem(vSpacerItem);

    QList <QString>pushButtonName;
    pushButtonName << "按钮一" << "按钮二" << "按钮三" << "按钮四";

    for(int i = 0; i < 4; i++)
    {
        pushButton[i] = new QPushButton();
        pushButton[i]->setText(pushButtonName[i]);
        if(0 == i)
        {
            pushButton[i]->setFixedSize(100, 100);
            vBoxLayout->addWidget(pushButton[i]);
        }
        else
        {
            pushButton[i]->setFixedSize(60, 60);
            hBoxLayout->addWidget(pushButton[i]);
        }
    }

    mainBoxLayout->addLayout(vBoxLayout);
    mainBoxLayout->addLayout(hBoxLayout);
    mainBoxLayout->setSpacing(0);

    widget->setLayout(mainBoxLayout);
}

MainWindow::~MainWindow()
{
}

