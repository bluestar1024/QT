#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    hWidget = new QWidget(this);
    hWidget->setGeometry(0, 0, 1024, 300);

    vWidget = new QWidget(this);
    vWidget->setGeometry(0, 300, 1024, 300);

    hLayout = new QHBoxLayout();
    vLayout = new QVBoxLayout();

    QList <QString>pushButtonName;
    pushButtonName << "按钮一" << "按钮二" << "按钮三" << "按钮四" << "按钮五" << "按钮六";

    for(int i = 0; i < 6; i++)
    {
        pushButton[i] = new QPushButton();
        pushButton[i]->setText(pushButtonName[i]);
        if(i < 3)
            hLayout->addWidget(pushButton[i]);
        else
            vLayout->addWidget(pushButton[i]);
    }

    hLayout->setSpacing(50);
    vLayout->setSpacing(20);

    hWidget->setLayout(hLayout);
    vWidget->setLayout(vLayout);
}

MainWindow::~MainWindow()
{
}

