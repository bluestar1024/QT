#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QFrame *lineHor;
    QFrame *lineVer;
    QFrame *boxFrame;
    QFrame *panelFrame;
    QFrame *winPanelFrame;
    QFrame *stylePanelFrame;
};
#endif // MAINWINDOW_H
