#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QPushButton>
#include <QMutex>
#include <QDebug>

class Worker;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Worker *worker;
    QThread workThread;
    QPushButton *pushButton1;
    QPushButton *pushButton2;

private slots:
    void pushButton1Click();
    void pushButton2Click();
    void handleResult(const QString &);

signals:
    void startWork(const QString &);
};

class Worker : public QObject
{
    Q_OBJECT

private:
    QMutex lock;
    bool isRun;

private slots:
    void doWork1(const QString &str)
    {
        isRun = true;
        while(1)
        {
            {
                QMutexLocker locker(&lock);
                if(!isRun)
                    break;
            }
            QThread::sleep(2);
            emit workResult(str + "doWork1函数");
        }
        emit workResult("打断doWork1函数");
    }

public:
    void stopWork()
    {
        qDebug() << "打断线程" << endl;

        QMutexLocker locker(&lock);
        isRun = false;
    }

signals:
    void workResult(const QString &);
};

#endif // MAINWINDOW_H
