#include "mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);
    this->setPalette(QPalette(Qt::gray));
    this->setAutoFillBackground(true);

    timer = new QTimer(this);
    angle = 0;
    timer->start(100);

    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeOut()));
}

void MainWindow::timerTimeOut()
{
    this->update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if(360 == angle++)
        angle = 0;
    QPixmap image(":/images/牛郎织女.png");
    QRectF rect((this->width() - image.width()) / 2,
                (this->height() - image.height()) / 2,
                image.width(),
                image.height());

    painter.drawImage(rect, image.toImage(), image.rect());
    painter.drawRect(rect);
    painter.translate(rect.x() + rect.width() / 2, rect.y() + rect.height() / 2);
    painter.rotate(angle);
    painter.translate(0 - rect.x() - rect.width() / 2, 0 - rect.y() - rect.height() / 2);
    //painter.drawImage(rect, image.toImage(), image.rect());
    //painter.drawRect(rect);
}

MainWindow::~MainWindow()
{
}

