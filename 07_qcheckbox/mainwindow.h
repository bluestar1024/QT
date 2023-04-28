#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCheckBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QCheckBox *checkBox1;
    QCheckBox *checkBox2;

public slots:
    void checkBox1Click(int);
    void checkBox2Click(int);
};
#endif // MAINWINDOW_H
