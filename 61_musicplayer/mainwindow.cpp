#include "mainwindow.h"
#include <QDir>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 1024, 600);

    musicPlayerLayout();
    musicPlayerInit();
    scanSongs();

    connect(pushButton[0], SIGNAL(clicked()), this, SLOT(btnPreviousClick()));
    connect(pushButton[1], SIGNAL(clicked()), this, SLOT(btnPlayClick()));
    connect(pushButton[2], SIGNAL(clicked()), this, SLOT(btnNextClick()));
    connect(musicPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(musicPlayerStateChange(QMediaPlayer::State)));
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)),
            this, SLOT(listWidgetItemClick(QListWidgetItem *)));
    connect(musicPlaylist, SIGNAL(currentIndexChanged(int)),
            this, SLOT(musicPlaylistCurrentIndexChange(int)));
    connect(musicPlayer, SIGNAL(durationChanged(qint64)),
            this, SLOT(musicPlayerDurationChange(qint64)));
    connect(musicPlayer, SIGNAL(positionChanged(qint64)),
            this, SLOT(musicPlayerPositionChange(qint64)));
    connect(progressSlider, SIGNAL(sliderReleased()), this, SLOT(progressSliderReleased()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::musicPlayerLayout()
{
    for(int i = 0; i < 4; i++)
        label[i] = new QLabel();
    listWidget = new QListWidget();
    for(int i = 0; i < 7; i++)
        pushButton[i] = new QPushButton();
    progressSlider = new QSlider(Qt::Horizontal);
    for(int i = 0; i < 3; i++)
        spacerItem[i] = new QSpacerItem(70, 600, QSizePolicy::Minimum, QSizePolicy::Preferred);
    for(int i = 3; i < 7; i++)
        spacerItem[i] = new QSpacerItem(350, 50, QSizePolicy::Minimum, QSizePolicy::Preferred);
    for(int i = 7; i < 9; i++)
        spacerItem[i] = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);
    for(int i = 9; i < 12; i++)
        spacerItem[i] = new QSpacerItem(30, 60, QSizePolicy::Minimum, QSizePolicy::Fixed);
    for(int i = 0; i < 4; i++)
        hWidget[i] = new QWidget();
    for(int i = 0; i < 2; i++)
        vWidget[i] = new QWidget();
    for(int i = 0; i < 4; i++)
        hLayout[i] = new QHBoxLayout();
    for(int i = 0; i < 2; i++)
        vLayout[i] = new QVBoxLayout();

    label[0]->setText("Q music, enjoy it!");
    label[1]->clear();
    label[2]->setText("00:00");
    label[3]->setText("00:00");
    label[0]->setObjectName("label0");
    label[1]->setObjectName("icon");
    label[2]->setObjectName("label2");
    label[3]->setObjectName("label3");
    label[0]->setMinimumWidth(350);
    label[0]->setFixedHeight(100);
    label[1]->setMinimumSize(350, 350);
    label[2]->setMinimumWidth(150);
    label[2]->setFixedHeight(30);
    label[3]->setMinimumWidth(150);
    label[3]->setFixedHeight(30);
    label[2]->setAlignment(Qt::AlignLeft);
    label[3]->setAlignment(Qt::AlignRight);

    QFont font;
    font.setPixelSize(27);
    listWidget->setFont(font);
    listWidget->setObjectName("listWidget");
    listWidget->setMinimumWidth(350);
    listWidget->setFixedHeight(300);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pushButton[0]->setObjectName("btn_previous");
    pushButton[1]->setObjectName("btn_play");
    pushButton[2]->setObjectName("btn_next");
    pushButton[3]->setObjectName("btn_favorite");
    pushButton[4]->setObjectName("btn_playMode");
    pushButton[5]->setObjectName("btn_menu");
    pushButton[6]->setObjectName("btn_volume");
    pushButton[1]->setCheckable(true);
    pushButton[1]->setChecked(false);
    pushButton[3]->setCheckable(true);
    pushButton[3]->setChecked(false);
    for(int i = 0; i < 3; i++)
        pushButton[i]->setFixedSize(100, 100);
    for(int i = 3; i < 7; i++)
        pushButton[i]->setFixedSize(60, 60);

    progressSlider->setMinimumWidth(350);
    progressSlider->setFixedHeight(50);

    this->setCentralWidget(hWidget[0]);
    hWidget[0]->setLayout(hLayout[0]);
    hLayout[0]->addSpacerItem(spacerItem[0]);
    hLayout[0]->addWidget(vWidget[0]);
    hLayout[0]->addSpacerItem(spacerItem[1]);
    hLayout[0]->addWidget(vWidget[1]);
    hLayout[0]->addSpacerItem(spacerItem[2]);

    vWidget[0]->setLayout(vLayout[0]);
    vLayout[0]->addSpacerItem(spacerItem[3]);
    vLayout[0]->addWidget(label[0]);
    vLayout[0]->addWidget(listWidget);
    vLayout[0]->addWidget(hWidget[1]);
    vLayout[0]->addSpacerItem(spacerItem[4]);

    hWidget[1]->setLayout(hLayout[1]);
    hLayout[1]->addWidget(pushButton[0]);
    hLayout[1]->addSpacerItem(spacerItem[7]);
    hLayout[1]->addWidget(pushButton[1]);
    hLayout[1]->addSpacerItem(spacerItem[8]);
    hLayout[1]->addWidget(pushButton[2]);

    vWidget[1]->setLayout(vLayout[1]);
    vLayout[1]->addSpacerItem(spacerItem[5]);
    vLayout[1]->addWidget(label[1]);
    vLayout[1]->addWidget(progressSlider);
    vLayout[1]->addWidget(hWidget[2]);
    vLayout[1]->addWidget(hWidget[3]);
    vLayout[1]->addSpacerItem(spacerItem[6]);

    hWidget[2]->setLayout(hLayout[2]);
    hLayout[2]->addWidget(label[2]);
    hLayout[2]->addWidget(label[3]);

    hWidget[3]->setLayout(hLayout[3]);
    hLayout[3]->addWidget(pushButton[3]);
    hLayout[3]->addSpacerItem(spacerItem[9]);
    hLayout[3]->addWidget(pushButton[4]);
    hLayout[3]->addSpacerItem(spacerItem[10]);
    hLayout[3]->addWidget(pushButton[5]);
    hLayout[3]->addSpacerItem(spacerItem[11]);
    hLayout[3]->addWidget(pushButton[6]);
}

void MainWindow::musicPlayerInit()
{
    musicPlayer = new QMediaPlayer(this);
    musicPlaylist = new QMediaPlaylist(this);
    musicPlayer->setPlaylist(musicPlaylist);
    musicPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
}

void MainWindow::scanSongs()
{
    QDir dir(QCoreApplication::applicationDirPath() + "/myMusic");
    QStringList nameFilters;
    nameFilters << "*.mp3";
    QStringList fileNameList = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    MediaFileInfo mediaFileInfo;
    for(int i = 0; i < fileNameList.count(); i++)
    {
        mediaFileInfo.filePathWithName = QCoreApplication::applicationDirPath() +
                "/myMusic/" + fileNameList.at(i);
        mediaFileInfo.fileNameFormat = fileNameList.at(i).split(".mp3").at(0).split("-").at(0) +
                "\n" + fileNameList.at(i).split(".mp3").at(0).split("-").at(1);
        musicFile.append(mediaFileInfo);
        musicPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(mediaFileInfo.filePathWithName)));
        listWidget->addItem(mediaFileInfo.fileNameFormat);
    }
}

void MainWindow::btnPreviousClick()
{
    if(0 == musicPlaylist->mediaCount())
        return;
    musicPlayer->stop();
    if(-1 == musicPlaylist->currentIndex())
        musicPlaylist->setCurrentIndex(0);
    musicPlaylist->previous();
    musicPlayer->play();
}

void MainWindow::btnPlayClick()
{
    QMediaPlayer::State state = musicPlayer->state();
    switch(state)
    {
        case QMediaPlayer::StoppedState:
            musicPlayer->play();
        break;
        case QMediaPlayer::PlayingState:
            musicPlayer->pause();
        break;
        case QMediaPlayer::PausedState:
            musicPlayer->play();
        break;
        default:
        break;
    }
}

void MainWindow::btnNextClick()
{
    if(0 == musicPlaylist->mediaCount())
        return;
    musicPlayer->stop();
    if(-1 == musicPlaylist->currentIndex())
        musicPlaylist->setCurrentIndex(0);
    musicPlaylist->next();
    musicPlayer->play();
}

void MainWindow::musicPlayerStateChange(QMediaPlayer::State state)
{
    switch(state)
    {
        case QMediaPlayer::StoppedState:
            pushButton[1]->setChecked(false);
        break;
        case QMediaPlayer::PlayingState:
            pushButton[1]->setChecked(true);
        break;
        case QMediaPlayer::PausedState:
            pushButton[1]->setChecked(false);
        break;
        default:
        break;
    }
}

void MainWindow::listWidgetItemClick(QListWidgetItem *item)
{
    musicPlayer->stop();
    musicPlaylist->setCurrentIndex(listWidget->row(item));
    musicPlayer->play();
}

void MainWindow::musicPlaylistCurrentIndexChange(int index)
{
    listWidget->setCurrentRow(index);
}

void MainWindow::musicPlayerDurationChange(qint64 duration)
{
    progressSlider->setRange(0, duration);

    int min = duration / 1000 / 60;
    int sec = duration / 1000 % 60;
    QString str;

    if(min > 9)
        str = QString::number(min);
    else
        str = "0" + QString::number(min);
    str += ":";
    if(sec > 9)
        str += QString::number(sec);
    else
        str += "0" + QString::number(sec);

    label[3]->setText(str);
}

void MainWindow::musicPlayerPositionChange(qint64 position)
{
    int min = position / 1000 / 60;
    int sec = position / 1000 % 60;
    QString str;

    if(min > 9)
        str = QString::number(min);
    else
        str = "0" + QString::number(min);
    str += ":";
    if(sec > 9)
        str += QString::number(sec);
    else
        str += "0" + QString::number(sec);

    label[2]->setText(str);

    if(!progressSlider->isSliderDown())
        progressSlider->setValue(position);
}

void MainWindow::progressSliderReleased()
{
    musicPlayer->setPosition(progressSlider->value());
}

