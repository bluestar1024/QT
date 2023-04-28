#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    toolBox = new QToolBox(this);
    toolBox->setGeometry(300, 100, 400, 400);
    toolBox->setStyleSheet("QToolBox { background-color: rgba(0, 0, 0, 30%); }");

    for(int i = 0; i < 2; i++)
    {
        groupBox[i] = new QGroupBox();
        vLayout[i] = new QVBoxLayout();
    }

    QList <QString>strList;
    strList << "李白" << "王昭君" << "上官婉儿" << "钟馗" << "程咬金" << "李元芳";

    QList <QString>iconList;
    iconList << ":/icons/libai" << ":/icons/wangzhaojun" << ":/icons/shangguanwaner"
         << ":/icons/zhongkui" << ":/icons/chengyaojin" << ":/icons/liyuanfang";

    for(int i = 0; i < 6; i++)
    {
        toolButton[i] = new QToolButton();
        toolButton[i]->setIcon(QIcon(iconList[i]));
        toolButton[i]->setIconSize(QSize(40, 40));
        toolButton[i]->setText(strList[i]);
        toolButton[i]->setFixedSize(200, 50);
        toolButton[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        if(i < 3)
        {
            vLayout[0]->addWidget(toolButton[i]);
            vLayout[0]->addStretch(1);
        }
        else
        {
            vLayout[1]->addWidget(toolButton[i]);
            vLayout[1]->addStretch(1);
        }
    }

    groupBox[0]->setLayout(vLayout[0]);
    groupBox[1]->setLayout(vLayout[1]);

    toolBox->addItem(groupBox[0], "好友");
    toolBox->addItem(groupBox[1], "黑名单");
}

MainWindow::~MainWindow()
{
}

