#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label;

public slots:
    void pushButtonClick();
};
#endif // MAINWINDOW_H
