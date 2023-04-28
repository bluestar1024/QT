#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);
    mainWidget = new QWidget(this);
    subWidget = new QWidget();
    mainHLayout = new QHBoxLayout();
    subVLayout = new QVBoxLayout();
    undoStack = new QUndoStack(this);
    undoView = new QUndoView(undoStack);
    pushButton = new QPushButton();
    label = new QLabel();
    count = 0;

    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(mainHLayout);
    mainHLayout->addWidget(subWidget);
    mainHLayout->addWidget(undoView);
    subWidget->setLayout(subVLayout);
    subVLayout->addWidget(label);
    subVLayout->addWidget(pushButton);

    subWidget->setMinimumWidth(this->width() / 2);
    label->setMinimumSize(200, 50);
    label->setText("计算结果:" + QString::number(count));
    label->setAlignment(Qt::AlignCenter);
    pushButton->setMinimumSize(100, 50);
    pushButton->setText("加一");

    connect(pushButton, SIGNAL(clicked()), this, SLOT(pushButtonClick()));
    connect(undoStack, SIGNAL(indexChanged(int)), this, SLOT(showCount(int)));
}

void MainWindow::pushButtonClick()
{
    QUndoCommand *cmd = new AddCommand(&count);
    undoStack->push(cmd);
}

void MainWindow::showCount(int)
{
    label->setText("计算结果:" + QString::number(count));
}

MainWindow::~MainWindow()
{
}

