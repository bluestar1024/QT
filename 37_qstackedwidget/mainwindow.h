#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *widget;
    QHBoxLayout *hLayout;
    QListWidget *listWidget;
    QStackedWidget *stackWidget;
    QLabel *label[3];
};
#endif // MAINWINDOW_H
