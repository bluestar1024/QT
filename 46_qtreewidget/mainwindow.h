#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QTreeWidget *treeWidget;
    QTreeWidgetItem *parentItem[2];
    QTreeWidgetItem *subItem1[2];
    QTreeWidgetItem *subItem2[3];

    void updateParentState(QTreeWidgetItem *item);

private slots:
    void treeItemChange(QTreeWidgetItem *, int);
};
#endif // MAINWINDOW_H
