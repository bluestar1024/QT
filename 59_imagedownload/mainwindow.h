#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QProgressBar>
#include <QWidget>
#include <QBoxLayout>
#include <QNetworkReply>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QNetworkAccessManager *networkAccessManager;
    QLabel *label[3];
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QProgressBar *progressBar;
    QWidget *mainWidget;
    QWidget *subWidget[2];
    QVBoxLayout *mainVLayout;
    QHBoxLayout *subHLayout[2];

private slots:
    void startDownload();
    void readyReadData();
    void replyFinish();
    void imageDownloadProgress(qint64, qint64);
    void networkReplyError(QNetworkReply::NetworkError);
};
#endif // MAINWINDOW_H
