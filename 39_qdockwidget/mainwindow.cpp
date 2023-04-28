#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    textEdit = new QTextEdit("文本初始内容");

    dockWidget = new QDockWidget("停靠窗口", this);
    dockWidget->setWidget(textEdit);
    dockWidget->setFixedSize(800, 500);

    this->addDockWidget(Qt::BottomDockWidgetArea, dockWidget);
}

MainWindow::~MainWindow()
{
}

