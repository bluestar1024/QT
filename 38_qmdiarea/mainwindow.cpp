#include "mainwindow.h"
#include <QString>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    mdiArea = new QMdiArea(this);
    mdiArea->setGeometry(100, 50, 800, 500);

    pushButton1 = new QPushButton("创建mdi窗口", this);
    pushButton1->setGeometry(100, 0, 100, 50);
    pushButton2 = new QPushButton("关闭mdi窗口", this);
    pushButton2->setGeometry(250, 0, 100, 50);

    connect(pushButton1, SIGNAL(clicked()), this, SLOT(createMdiSubWindow()));
    connect(pushButton2, SIGNAL(clicked()), this, SLOT(closeMdiSubWindow()));

    Num = 0;
}

void MainWindow::createMdiSubWindow()
{
    QString str;

    lineEdit[Num] = new QLineEdit();
    lineEdit[Num]->setFixedSize(100, 50);

    mdiSubWindow[Num] = new QMdiSubWindow();
    mdiSubWindow[Num]->setWindowTitle("mdi窗口" + str.number(Num + 1));
    mdiSubWindow[Num]->setAttribute(Qt::WA_DeleteOnClose);

    mdiArea->addSubWindow(mdiSubWindow[Num]);

    mdiSubWindow[Num]->show();
    mdiSubWindow[Num]->sizePolicy();
    mdiSubWindow[Num]->setWidget(lineEdit[Num]);

    Num++;

    //mdiArea->cascadeSubWindows();
    mdiArea->tileSubWindows();
}
void MainWindow::closeMdiSubWindow()
{
    if(Num > 0)
        mdiSubWindow[--Num]->close();
}

MainWindow::~MainWindow()
{
}

