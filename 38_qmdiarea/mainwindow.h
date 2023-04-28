#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QPushButton>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMdiArea *mdiArea;
    QMdiSubWindow *mdiSubWindow[100];
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QLineEdit *lineEdit[100];
    int Num;

private slots:
    void createMdiSubWindow();
    void closeMdiSubWindow();
};
#endif // MAINWINDOW_H
