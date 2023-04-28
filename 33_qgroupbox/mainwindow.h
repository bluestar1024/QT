#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGroupBox *groupBox;
    QVBoxLayout *vLayout;
    QPushButton *pushButton[3];
};
#endif // MAINWINDOW_H
