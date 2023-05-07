#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QPushButton>
#include <QWidget>
#include <QBoxLayout>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTextBrowser *textBrowser;
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QWidget *mainWidget;
    QWidget *pushButtonWidget;
    QVBoxLayout *mainVLayout;
    QHBoxLayout *subHLayout;
    QTimer *timer;

    QString getHostInfo();
    void showHostInfo();

private slots:
    void timerStart();
    void timerTimeout();
    void clearTextInfo();
};
#endif // MAINWINDOW_H
