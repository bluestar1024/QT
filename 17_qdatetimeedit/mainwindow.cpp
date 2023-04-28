#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    dateTimeEdit->setGeometry(300, 200, 200, 50);
    dateTimeEdit->setStyleSheet("QDateTimeEdit { background-color: rgba(200, 10, 10, 100%); }");
    dateTimeEdit->setCalendarPopup(true);

    timeEdit = new QTimeEdit(QTime::currentTime(), this);
    timeEdit->setGeometry(300, 300, 200, 50);
    timeEdit->setStyleSheet("QTimeEdit { background-color: rgba(200, 200, 10, 100%); }");

    dateEdit = new QDateEdit(QDate::currentDate(), this);
    dateEdit->setGeometry(300, 400, 200, 50);
    dateEdit->setStyleSheet("QDateEdit { background-color: rgba(10, 200, 10, 100%); }");
    dateEdit->setCalendarPopup(true);
}

MainWindow::~MainWindow()
{
}

