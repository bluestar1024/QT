#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    widget = new QWidget(this);
    this->setCentralWidget(widget);

    tabWidget = new QTabWidget();

    hLayout = new QHBoxLayout();

    QList <QString>labelList;
    labelList << "标签一" << "标签二" << "标签三";

    QList <QString>tabList;
    tabList << "页面一" << "页面二" << "页面三";

    QList <QString>iconList;
    iconList << ":/icons/icon1" << ":/icons/icon2" << ":/icons/icon3";

    QFont font;
    font.setPointSize(20);
    for(int i = 0; i < 3; i++)
    {
        label[i] = new QLabel();
        label[i]->setFont(font);
        label[i]->setText(labelList[i]);
        label[i]->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(label[i], QIcon(iconList[i]), tabList[i]);
    }
    tabWidget->setTabsClosable(true);

    hLayout->addWidget(tabWidget);
    widget->setLayout(hLayout);
}
MainWindow::~MainWindow()
{
}

