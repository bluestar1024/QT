#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void buttonTextChangeSignal();

public slots:
    void buttonTextClick();
    void buttonTextChange();

private:
    QPushButton *pushButton;
    int n;
};
#endif // MAINWINDOW_H
