#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    groupBox = new QGroupBox(this);
    groupBox->setGeometry(300, 150, 400, 300);
    groupBox->setTitle("QGroupBox示例");

    vLayout = new QVBoxLayout();

    QList <QString>pushButtonName;
    pushButtonName << "按钮一" << "按钮二" << "按钮三";

    for(int i = 0; i < 3; i++)
    {
        pushButton[i] = new QPushButton();
        pushButton[i]->setText(pushButtonName[i]);
        vLayout->addWidget(pushButton[i]);
    }

    //vLayout->addStretch(1);
    groupBox->setLayout(vLayout);
}

MainWindow::~MainWindow()
{
}

