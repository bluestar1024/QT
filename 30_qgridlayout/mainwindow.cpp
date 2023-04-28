#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    gWidget = new QWidget(this);
    gWidget->setGeometry(0, 0, 1024, 600);

    gLayout = new QGridLayout();

    QList <QString>pushButtonName;
    pushButtonName << "按钮一" << "按钮二" << "按钮三" << "按钮四" << "按钮五";

    for(int i = 0; i < 5; i++)
    {
        pushButton[i] = new QPushButton();
        pushButton[i]->setText(pushButtonName[i]);
        pushButton[i]->setMinimumSize(100, 50);
        pushButton[i]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        switch(i)
        {
            case 0:
                gLayout->addWidget(pushButton[i], 0, 0);
                break;
            case 1:
                gLayout->addWidget(pushButton[i], 0, 1);
                break;
            case 2:
                gLayout->addWidget(pushButton[i], 1, 0);
                break;
            case 3:
                gLayout->addWidget(pushButton[i], 1, 1);
                break;
            case 4:
                gLayout->addWidget(pushButton[i], 1, 2);
                break;
            default:
                break;
        }
    }

    gLayout->setRowStretch(0, 1);
    gLayout->setRowStretch(1, 2);
    gLayout->setColumnStretch(0, 1);
    gLayout->setColumnStretch(1, 2);
    gLayout->setColumnStretch(2, 3);

    gWidget->setLayout(gLayout);
}

MainWindow::~MainWindow()
{
}

