#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    fontComboBox = new QFontComboBox(this);
    label = new QLabel(this);

    fontComboBox->setGeometry(300, 100, 200, 50);
    label->setGeometry(300, 200, 300, 80);

    fontComboBox->setStyleSheet("QFontComboBox { background-color: rgba(10, 200, 10, 100%); }");
    label->setStyleSheet("QLabel { background-color: rgba(200, 10, 10, 100%); }");

    label->setText("请选择字体");

    connect(fontComboBox, SIGNAL(currentFontChanged(QFont)), this, SLOT(fontComboBoxFontChange(QFont)));
}

void MainWindow::fontComboBoxFontChange(QFont font)
{
    label->setFont(font);
    QString str = "用此标签显示字体效果\n你选择的字体为:" + fontComboBox->itemText(fontComboBox->currentIndex());
    label->setText(str);
}

MainWindow::~MainWindow()
{
}

