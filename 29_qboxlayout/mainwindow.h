#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *hWidget;
    QWidget *vWidget;

    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;

    QPushButton *pushButton[6];
};
#endif // MAINWINDOW_H
