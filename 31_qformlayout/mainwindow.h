#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *fWidget;
    QFormLayout *formLayout;
    QLineEdit *userName;
    QLineEdit *passWord;
};
#endif // MAINWINDOW_H
