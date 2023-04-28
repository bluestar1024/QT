#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QRadioButton *radioButton1;
    QRadioButton *radioButton2;
    QRadioButton *radioButton3;
    QRadioButton *radioButton4;
};
#endif // MAINWINDOW_H
