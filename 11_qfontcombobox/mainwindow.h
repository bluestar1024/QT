#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontComboBox>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QFontComboBox *fontComboBox;
    QLabel *label;

public slots:
    void fontComboBoxFontChange(QFont);
};
#endif // MAINWINDOW_H
