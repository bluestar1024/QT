#include "mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    mainWidget = new QWidget(this);
    subWidget = new QWidget();
    mainVLayout = new QVBoxLayout();
    subHLayout = new QHBoxLayout();
    textEdit = new QTextEdit();
    openPushButton = new QPushButton();
    closePushButton = new QPushButton();

    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(mainVLayout);
    mainVLayout->addWidget(textEdit);
    mainVLayout->addWidget(subWidget);
    subWidget->setLayout(subHLayout);
    subHLayout->addWidget(openPushButton);
    subHLayout->addWidget(closePushButton);

    textEdit->setText("文本初始内容");
    openPushButton->setMaximumWidth(120);
    openPushButton->setMinimumHeight(50);
    openPushButton->setText("打开");
    closePushButton->setMaximumWidth(120);
    closePushButton->setMinimumHeight(50);
    closePushButton->setText("关闭");
    closePushButton->setEnabled(false);

    connect(openPushButton, SIGNAL(clicked()), this, SLOT(openFileToTextEdit()));
    connect(closePushButton, SIGNAL(clicked()), this, SLOT(closeFileFromTextEdit()));
}

void MainWindow::openFileToTextEdit()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择文件", "", "Files(*)");
    file.setFileName(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    textEdit->setPlainText(file.readAll());
    openPushButton->setEnabled(false);
    closePushButton->setEnabled(true);
    file.close();
}
void MainWindow::closeFileFromTextEdit()
{
    QString str = textEdit->toPlainText();
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QByteArray strbytes = str.toUtf8();
    file.write(strbytes);
    textEdit->clear();
    openPushButton->setEnabled(true);
    closePushButton->setEnabled(false);
    file.close();
}

MainWindow::~MainWindow()
{
}

