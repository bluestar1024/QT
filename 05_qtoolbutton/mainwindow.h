#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QStyle>
#include <QToolBar>
#include <QToolButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QToolBar *toolBar;
    QStyle *style;
    QIcon icon1;
    QIcon icon2;
    QIcon icon3;
    QIcon icon4;
    QToolButton *toolButton1;
    QToolButton *toolButton2;
    QToolButton *toolButton3;
    QToolButton *toolButton4;

public slots:
    void buttonTextOutput1();
    void buttonTextOutput2();
    void buttonTextOutput3();
    void buttonClose();
};
#endif // MAINWINDOW_H
