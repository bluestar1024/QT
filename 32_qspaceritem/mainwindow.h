#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpacerItem>
#include <QPushButton>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSpacerItem *hSpacerItem;
    QSpacerItem *vSpacerItem;
    QPushButton *pushButton[4];
    QWidget *widget;
    QHBoxLayout *hBoxLayout;
    QHBoxLayout *mainBoxLayout;
    QVBoxLayout *vBoxLayout;

};
#endif // MAINWINDOW_H
