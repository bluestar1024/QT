#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setGeometry(100, 100, 1024, 600);
    this->setWindowTitle("图像浏览器");
    graphicsView = new QGraphicsView(this);
    this->setCentralWidget(graphicsView);

    graphicsScence = new QGraphicsScene(this);
    graphicsView->setScene(graphicsScence);

    action = new QAction("打开", this);
    ui->menubar->addAction(action);

    connect(action, SIGNAL(triggered()), this, SLOT(actionTrigger()));
}

void MainWindow::actionTrigger()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", ".",
                            "Images(*.png *.bmp *.jpeg *.jpg)");
    QPixmap image(fileName);
    if(image.isNull())
        return;

    image = image.scaled(graphicsView->width(), graphicsView->height(),
                 Qt::KeepAspectRatio, Qt::FastTransformation);

    graphicsScence->clear();
    graphicsScence->addPixmap(image);

    ui->statusbar->showMessage("文件名:" + fileName);
}

MainWindow::~MainWindow()
{
    delete ui;
}

