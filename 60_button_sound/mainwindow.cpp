#include "mainwindow.h"
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);
    pushButton = new QPushButton(this);
    pushButton->setText("按键音效");
    pushButton->setGeometry((this->width() - 100) / 2,
                            (this->height() - 50) / 2,
                            100,
                            50);

    connect(pushButton, SIGNAL(clicked()), this, SLOT(pushButtonClick()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::pushButtonClick()
{
    QSound::play(":/audio/bell.wav");
}

