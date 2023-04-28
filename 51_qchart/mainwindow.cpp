#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    maxPointNum = 51;
    maxAsixX = 50;
    maxAsixY = 40;

    chart = new QChart();
    spline = new QSplineSeries();
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    chartView = new QChartView();
    timer = new QTimer(this);

    chart->legend()->hide();
    chart->setTitle("温度随机数曲线图");
    chart->addSeries(spline);

    axisY->setLabelFormat("%i");
    axisY->setTitleText("温度/C");
    //chart->addAxis(axisY, Qt::AlignBottom);
    //chart->addAxis(axisY, Qt::AlignRight);
    chart->addAxis(axisY, Qt::AlignLeft);
    axisY->setRange(0, maxAsixY);
    spline->attachAxis(axisY);

    axisX->setLabelFormat("%i");
    axisX->setTitleText("时间/s");
    //chart->addAxis(axisX, Qt::AlignLeft);
    //chart->addAxis(axisX, Qt::AlignTop);
    chart->addAxis(axisX, Qt::AlignBottom);
    axisX->setRange(0, maxAsixX);
    spline->attachAxis(axisX);

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    this->setCentralWidget(chartView);

    timer->start(200);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
    qsrand(time(NULL));
}

MainWindow::~MainWindow()
{
}

void MainWindow::timerTimeout()
{
    data.append(qrand() % maxAsixY);

    while(data.size() > maxPointNum)
        data.removeFirst();

    spline->clear();

    int xSpace = maxAsixX / (maxPointNum - 1);

    for(int i = 0; i < data.size(); i++)
        spline->append(xSpace * i, data.at(i));
}

