#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QPushButton>

class WorkThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    WorkThread *workThread;
    QPushButton *pushButton;

private slots:
    void pushButtonClick();
    void handleRunStatusSignal(const QString &);
};

class WorkThread : public QThread
{
    Q_OBJECT

public:
    WorkThread(QWidget *parent = nullptr)
    {
        Q_UNUSED(parent);
    }

protected:
    void run() override
    {
        QString str = "线程运行中";
        while(1)
        {
            sleep(2);
            emit runStatusSignal(str);
        }
    }

signals:
    void runStatusSignal(const QString &);
};

#endif // MAINWINDOW_H
