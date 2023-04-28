#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTextEdit *textEdit;
    QPushButton *pushButtonSelectAll;
    QPushButton *pushButtonClearAll;

public slots:
    void pushButtonSelectAllClick();
    void pushButtonClearAllClick();
};
#endif // MAINWINDOW_H
