#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSlider *sliderHor;
    QSlider *sliderVer;
    QLabel *label;

private slots:
    void sliderHorValueChange(int);
    void sliderVerValueChange(int);
};
#endif // MAINWINDOW_H
