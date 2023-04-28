#include "mainwindow.h"
#include <QStyle>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    lineHor = new QFrame(this);
    lineVer = new QFrame(this);
    boxFrame = new QFrame(this);
    panelFrame = new QFrame(this);
    winPanelFrame = new QFrame(this);
    stylePanelFrame = new QFrame(this);

    lineHor->setGeometry(300, 200, 400, 50);
    lineVer->setGeometry(400, 150, 50, 300);
    boxFrame->setGeometry(350, 220, 300, 160);
    panelFrame->setGeometry(600, 250, 300, 200);
    winPanelFrame->setGeometry(100, 100, 300, 200);
    stylePanelFrame->setGeometry(200, 350, 300, 200);

    lineHor->setFrameShape(QFrame::HLine);
    lineVer->setFrameShape(QFrame::VLine);
    boxFrame->setFrameShape(QFrame::Box);
    panelFrame->setFrameShape(QFrame::Panel);
    winPanelFrame->setFrameShape(QFrame::WinPanel);
    stylePanelFrame->setFrameShape(QFrame::StyledPanel);

    lineHor->setFrameShadow(QFrame::Raised);
    lineVer->setFrameShadow(QFrame::Sunken);
    boxFrame->setFrameShadow(QFrame::Sunken);
    panelFrame->setFrameShadow(QFrame::Raised);
    winPanelFrame->setFrameShadow(QFrame::Sunken);
    //stylePanelFrame->setFrameShadow(QFrame::Raised);
    //stylePanelFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
}

MainWindow::~MainWindow()
{
}

