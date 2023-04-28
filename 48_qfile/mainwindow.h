#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QFile>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *mainWidget;
    QWidget *subWidget;
    QVBoxLayout *mainVLayout;
    QHBoxLayout *subHLayout;
    QTextEdit *textEdit;
    QPushButton *openPushButton;
    QPushButton *closePushButton;
    QFile file;

private slots:
    void openFileToTextEdit();
    void closeFileFromTextEdit();
};
#endif // MAINWINDOW_H
