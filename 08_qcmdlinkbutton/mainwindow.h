#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCommandLinkButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QCommandLinkButton *cmdLinkButton1;
    QCommandLinkButton *cmdLinkButton2;

public slots:
    void cmdLinkButton1Click();
    void cmdLinkButton2Click();
};
#endif // MAINWINDOW_H
