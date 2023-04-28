#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    keySeqEdit = new QKeySequenceEdit(this);
    keySeqEdit->setGeometry(300, 200, 200, 50);
    keySeqEdit->setStyleSheet("QKeySequenceEdit { background-color: rgba(10, 200, 10, 100%); }");

    connect(keySeqEdit, SIGNAL(keySequenceChanged(const QKeySequence &)), this, SLOT(keySeqEditChange(const QKeySequence &)));
}

void MainWindow::keySeqEditChange(const QKeySequence & keySeq)
{
    if(keySeq == QKeySequence("Ctrl+Q"))
        this->close();
    else
        qDebug() << keySeq.toString() << endl;
}

MainWindow::~MainWindow()
{
}

