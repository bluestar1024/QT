#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QIODevice>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setGeometry(100, 100, 1024, 600);
    this->setWindowTitle("文本浏览器");
    textBrowser = new QTextBrowser(this);
    this->setCentralWidget(textBrowser);

    action = new QAction(this);
    action->setText("打开");
    ui->menubar->addAction(action);

    connect(action, SIGNAL(triggered()), this, SLOT(actionTrigger()));
}

void MainWindow::actionTrigger()
{
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件", "",
                            "Files(*.txt *.cpp *.h *.html *.htm)");
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString text = in.readAll();

    if(fileName.endsWith("html") || fileName.endsWith("htm"))
        textBrowser->setHtml(text);
    else
        textBrowser->setPlainText(text);

    ui->statusbar->showMessage("文件名:" + fileName);
}

MainWindow::~MainWindow()
{
    delete ui;
}

