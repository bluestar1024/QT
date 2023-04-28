#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBox>
#include <QGroupBox>
#include <QBoxLayout>
#include <QToolButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QToolBox *toolBox;
    QGroupBox *groupBox[2];
    QVBoxLayout *vLayout[2];
    QToolButton *toolButton[6];
};
#endif // MAINWINDOW_H
