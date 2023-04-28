#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(200, 200, 1024, 600);

    toolBar = new QToolBar(this);
    toolBar->setGeometry(50, 50, 300, 100);
    toolBar->setStyleSheet("QToolBar { background-color: rgba(250, 250, 10, 100%); }");

    style = QApplication::style();
    icon1 = style->standardIcon(QStyle::SP_DesktopIcon);
    icon2 = style->standardIcon(QStyle::SP_MessageBoxInformation);
    icon3 = style->standardIcon(QStyle::SP_TitleBarContextHelpButton);
    icon4 = style->standardIcon(QStyle::SP_DirClosedIcon);

    toolButton1 = new QToolButton();
    toolButton1->setIcon(icon1);
    toolButton1->setText("桌面");
    toolButton1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    toolButton2 = new QToolButton();
    toolButton2->setIcon(icon2);
    toolButton2->setText("消息");
    toolButton2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    toolButton3 = new QToolButton();
    toolButton3->setIcon(icon3);
    toolButton3->setText("帮助");
    toolButton3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    toolButton4 = new QToolButton();
    toolButton4->setIcon(icon4);
    toolButton4->setText("关闭");
    toolButton4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    toolBar->addWidget(toolButton1);
    toolBar->addWidget(toolButton2);
    toolBar->addWidget(toolButton3);
    toolBar->addWidget(toolButton4);

    connect(toolButton1, SIGNAL(click()), this, SLOT(buttonTextOutput1()));
    connect(toolButton2, SIGNAL(click()), this, SLOT(buttonTextOutput2()));
    connect(toolButton3, SIGNAL(click()), this, SLOT(buttonTextOutput3()));
    connect(toolButton4, SIGNAL(click()), this, SLOT(buttonClose()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::buttonTextOutput1()
{
    toolButton1->setText("桌面被点击了");
}
void MainWindow::buttonTextOutput2()
{
    toolButton2->setText("消息被点击了");
}
void MainWindow::buttonTextOutput3()
{
    toolButton3->setText("帮助被点击了");
}
void MainWindow::buttonClose()
{
    toolBar->close();
}
