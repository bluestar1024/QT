#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QRadioButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPlainTextEdit *plainTextEdit;
    QRadioButton *radioButton;

public slots:
    void radioButtonClick();
};
#endif // MAINWINDOW_H
