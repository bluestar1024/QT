#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QChart>
#include <QSplineSeries>
#include <QValueAxis>
#include <QChartView>
#include <QTimer>

QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QChart *chart;
    QSplineSeries *spline;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QChartView *chartView;
    int maxPointNum;
    int maxAsixX;
    int maxAsixY;
    QList <int>data;
    QTimer *timer;

private slots:
    void timerTimeout();
};
#endif // MAINWINDOW_H
