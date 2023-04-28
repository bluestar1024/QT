#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeySequenceEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QKeySequenceEdit *keySeqEdit;

private slots:
    void keySeqEditChange(const QKeySequence &);
};
#endif // MAINWINDOW_H
