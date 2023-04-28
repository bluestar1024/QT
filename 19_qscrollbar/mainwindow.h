#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QScrollBar *scrollBarHor;
    QScrollBar *scrollBarVer;
    QLabel *label;
};
#endif // MAINWINDOW_H
