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

private:
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QPushButton *pushButton3;
    QPushButton *pushButton4;

public slots:
    void pushButton1ChangeColor();
    void pushButton2ChangeColor();
    void pushButton3ChangeColor();
    void pushButton4ChangeColor();
};
#endif // MAINWINDOW_H
