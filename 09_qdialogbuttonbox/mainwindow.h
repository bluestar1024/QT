#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialogButtonBox>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QDialogButtonBox *dialogButtonBox;
    QPushButton *pushButton;

public slots:
    void dialogButtonBoxClick(QAbstractButton *button);
};
#endif // MAINWINDOW_H
