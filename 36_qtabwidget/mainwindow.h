#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTabWidget>
#include <QBoxLayout>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *widget;
    QTabWidget *tabWidget;
    QHBoxLayout *hLayout;
    QLabel *label[3];
};
#endif // MAINWINDOW_H
