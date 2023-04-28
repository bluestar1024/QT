#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    calendarWidget = new QCalendarWidget(this);
    calendarWidget->setGeometry(250, 100, 500, 300);

    QFont font;
    font.setPixelSize(10);
    calendarWidget->setFont(font);

    pushButton = new QPushButton("回到当前日期", this);
    pushButton->setGeometry(250, 420, 100, 50);

    label = new QLabel(this);
    label->setGeometry(500, 420, 250, 50);
    label->setText("当前选择的日期:" + calendarWidget->selectedDate().toString());

    connect(calendarWidget, SIGNAL(selectionChanged()), this, SLOT(calendarWidgetSelectChange()));
    connect(pushButton, SIGNAL(clicked()), this, SLOT(pushButtonClick()));
}

void MainWindow::calendarWidgetSelectChange()
{
    label->setText("当前选择日期为:" + calendarWidget->selectedDate().toString());
}
void MainWindow::pushButtonClick()
{
    calendarWidget->setSelectedDate(QDate::currentDate());
}

MainWindow::~MainWindow()
{
}

