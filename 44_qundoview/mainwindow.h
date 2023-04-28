#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QBoxLayout>
#include <QUndoView>
#include <QUndoStack>
#include <QPushButton>
#include <QLabel>
#include "command.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *mainWidget;
    QWidget *subWidget;
    QHBoxLayout *mainHLayout;
    QVBoxLayout *subVLayout;
    QUndoView *undoView;
    QUndoStack *undoStack;
    QPushButton *pushButton;
    QLabel *label;
    int count;

private slots:
    void pushButtonClick();
    void showCount(int);
};
#endif // MAINWINDOW_H
