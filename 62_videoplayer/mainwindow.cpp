#include "mainwindow.h"
#include <QDir>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    videoPlayerLayout();
    videoPlayerInit();
    scanVideoFiles();

    connect(pushButton[0], SIGNAL(clicked()), this, SLOT(btnPlayClicked()));
    connect(pushButton[1], SIGNAL(clicked()), this, SLOT(btnNextClicked()));
    connect(pushButton[2], SIGNAL(clicked()), this, SLOT(btnVolumeDownClicked()));
    connect(pushButton[3], SIGNAL(clicked()), this, SLOT(btnVolumeUpClicked()));
    connect(pushButton[4], SIGNAL(clicked()), this, SLOT(btnFullScreenClicked()));
    connect(pushButton[5], SIGNAL(clicked()), this, SLOT(btnHalfScreenClicked()));
    connect(videoPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),
            this, SLOT(videoPlayerStateChanged(QMediaPlayer::State)));
    connect(listWidget, SIGNAL(itemClicked(QListWidgetItem *)),
            this, SLOT(listWidgetItemClicked(QListWidgetItem *)));
    connect(videoPlaylist, SIGNAL(currentIndexChanged(int)),
            this, SLOT(videoPlaylistCurrentIndexChanged(int)));
    connect(videoPlayer, SIGNAL(durationChanged(qint64)),
            this, SLOT(videoPlayerDurationChanged(qint64)));
    connect(videoPlayer, SIGNAL(positionChanged(qint64)),
            this, SLOT(videoPlayerPositionChanged(qint64)));
    connect(progressSlider, SIGNAL(sliderReleased()),
            this, SLOT(progressSliderRelease()));
    connect(volumeSlider, SIGNAL(sliderReleased()),
            this, SLOT(volumeSliderRelease()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::videoPlayerLayout()
{
    this->setGeometry(100, 100, 1024, 600);

    videoWidget = new QVideoWidget();
    listWidget = new QListWidget();
    progressSlider = new QSlider(Qt::Horizontal);
    volumeSlider = new QSlider(Qt::Horizontal);
    for(int i = 0; i < 6; i++)
    {
        pushButton[i] = new QPushButton();
    }
    pushButton[5]->setParent(this);
    for(int i = 0; i < 2; i++)
    {
        label[i] = new QLabel();
    }
    spacerItem[0] = new QSpacerItem(300, 90, QSizePolicy::Fixed, QSizePolicy::Fixed);
    spacerItem[1] = new QSpacerItem(400, 50, QSizePolicy::Minimum, QSizePolicy::Minimum);
    for(int i = 0; i < 2; i++)
    {
        hWidget[i] = new QWidget();
        vWidget[i] = new QWidget();
        hLayout[i] = new QHBoxLayout();
        vLayout[i] = new QVBoxLayout();
    }
    vWidget[1]->setParent(this);

    videoWidget->setMinimumSize(this->width() - 300, this->height());
    videoWidget->setStyleSheet("border-image: none; background: transparent; border: none;");

    listWidget->setObjectName("listWidget");
    listWidget->setFixedSize(300, this->height() - 90);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    progressSlider->setObjectName("progressSlider");
    progressSlider->setFixedSize(this->width(), 20);

    volumeSlider->setObjectName("volumeSlider");
    volumeSlider->setFixedSize(100, 20);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);

    pushButton[0]->setObjectName("btn_play");
    pushButton[1]->setObjectName("btn_next");
    pushButton[2]->setObjectName("btn_volume_down");
    pushButton[3]->setObjectName("btn_volume_up");
    pushButton[4]->setObjectName("btn_full_screen");
    pushButton[5]->setObjectName("btn_half_screen");
    for(int i = 0; i < 5; i++)
    {
        pushButton[i]->setFixedSize(50, 50);
    }
    pushButton[0]->setCheckable(true);
    pushButton[0]->setChecked(false);
    pushButton[5]->setGeometry(this->width() - 50, 0, 50, 50);
    pushButton[5]->raise();
    pushButton[5]->setVisible(false);

    for(int i = 0; i < 2; i++)
    {
        label[i]->setFixedSize(65, 40);
    }
    label[0]->setText("00:00");
    label[1]->setText("/00:00");

    this->setCentralWidget(hWidget[0]);
    hWidget[0]->setObjectName("hWidget0");
    hWidget[0]->setLayout(hLayout[0]);
    hLayout[0]->addWidget(videoWidget);
    hLayout[0]->addWidget(vWidget[0]);
    hLayout[0]->setContentsMargins(0, 0, 0, 0);

    vWidget[0]->setObjectName("vWidget0");
    vWidget[0]->setLayout(vLayout[0]);
    vLayout[0]->addWidget(listWidget);
    vLayout[0]->addSpacerItem(spacerItem[0]);
    vLayout[0]->setContentsMargins(0, 0, 0, 0);

    vWidget[1]->setObjectName("vWidget1");
    vWidget[1]->setGeometry(0, this->height() - 90, this->width(), 90);
    vWidget[1]->setLayout(vLayout[1]);
    vLayout[1]->addWidget(progressSlider);
    vLayout[1]->addWidget(hWidget[1]);
    vLayout[1]->addSpacing(20);
    vLayout[1]->setContentsMargins(0, 0, 0, 0);
    vWidget[1]->raise();

    hWidget[1]->setObjectName("hWidget1");
    hWidget[1]->setLayout(hLayout[1]);
    hLayout[1]->addSpacing(20);
    hLayout[1]->addWidget(pushButton[0]);
    hLayout[1]->addSpacing(20);
    hLayout[1]->addWidget(pushButton[1]);
    hLayout[1]->addSpacing(20);
    hLayout[1]->addWidget(pushButton[2]);
    hLayout[1]->addWidget(volumeSlider);
    hLayout[1]->addWidget(pushButton[3]);
    hLayout[1]->addSpacing(20);
    hLayout[1]->addWidget(label[0]);
    hLayout[1]->addWidget(label[1]);
    hLayout[1]->addSpacerItem(spacerItem[1]);
    hLayout[1]->addWidget(pushButton[4]);
    hLayout[1]->setContentsMargins(0, 0, 0, 0);
    hLayout[1]->addSpacing(20);
}

void MainWindow::videoPlayerInit()
{
    videoPlayer = new QMediaPlayer(this);
    videoPlaylist = new QMediaPlaylist(this);
    videoPlayer->setPlaylist(videoPlaylist);
    videoPlayer->setVideoOutput(videoWidget);
    videoPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
    videoPlayer->setVolume(50);
}

void MainWindow::scanVideoFiles()
{
    QDir dir(QCoreApplication::applicationDirPath() + "/myVideo");
    QStringList nameFilters;
    nameFilters << "*.mp4" << "*.mkv" << "*.wmv" << "*.avi";
    QStringList fileNameList = dir.entryList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
    mediaFileInfo fileInfo;
    for(int i = 0; i < fileNameList.count(); i++)
    {
        fileInfo.filePathWithName = QCoreApplication::applicationDirPath() + "/myVideo/" +
                fileNameList.at(i);
        fileInfo.fileNameFormat = fileNameList.at(i);
        videoFile.append(fileInfo);
        videoPlaylist->addMedia(QMediaContent(QUrl::fromLocalFile(fileInfo.filePathWithName)));
        listWidget->addItem(fileInfo.fileNameFormat);
    }
}

void MainWindow::btnPlayClicked()
{
    QMediaPlayer::State state = videoPlayer->state();
    switch(state)
    {
        case QMediaPlayer::StoppedState:
            videoPlayer->play();
        break;
        case QMediaPlayer::PlayingState:
            videoPlayer->pause();
        break;
        case QMediaPlayer::PausedState:
            videoPlayer->play();
        break;
        default:
        break;
    }
}

void MainWindow::btnNextClicked()
{
    if(0 == videoPlaylist->mediaCount())
        return;
    videoPlayer->stop();
    if(-1 == videoPlaylist->currentIndex())
        videoPlaylist->setCurrentIndex(0);
    videoPlaylist->next();
    videoPlayer->play();
}

void MainWindow::btnVolumeUpClicked()
{
    volumeSlider->setValue(volumeSlider->value() + 5);
    videoPlayer->setVolume(volumeSlider->value());
}

void MainWindow::btnVolumeDownClicked()
{
    volumeSlider->setValue(volumeSlider->value() - 5);
    videoPlayer->setVolume(volumeSlider->value());
}

void MainWindow::btnFullScreenClicked()
{
    vWidget[0]->setVisible(false);
    vWidget[1]->setVisible(false);
    pushButton[5]->setVisible(true);
    pushButton[5]->raise();
}

void MainWindow::btnHalfScreenClicked()
{
    vWidget[0]->setVisible(true);
    vWidget[1]->setVisible(true);
    pushButton[5]->setVisible(false);
}

void MainWindow::videoPlayerStateChanged(QMediaPlayer::State state)
{
    switch(state)
    {
        case QMediaPlayer::StoppedState:
            pushButton[0]->setChecked(false);
        break;
        case QMediaPlayer::PlayingState:
            pushButton[0]->setChecked(true);
        break;
        case QMediaPlayer::PausedState:
            pushButton[0]->setChecked(false);
        break;
        default:
        break;
    }
}

void MainWindow::listWidgetItemClicked(QListWidgetItem *item)
{
    videoPlayer->stop();
    videoPlaylist->setCurrentIndex(listWidget->row(item));
    videoPlayer->play();
}

void MainWindow::videoPlaylistCurrentIndexChanged(int index)
{
    listWidget->setCurrentRow(index);
}

void MainWindow::videoPlayerDurationChanged(qint64 duration)
{
    progressSlider->setRange(0, duration);
    int min = duration / 1000 / 60;
    int sec = duration / 1000 % 60;
    QString str;

    str = "/";
    if(min > 9)
        str += QString::number(min);
    else
        str += "0" + QString::number(min);
    str += ":";
    if(sec > 9)
        str += QString::number(sec);
    else
        str += "0" + QString::number(sec);

    label[1]->setText(str);
}

void MainWindow::videoPlayerPositionChanged(qint64 position)
{
    if(!progressSlider->isSliderDown())
        progressSlider->setValue(position);

    int min = position / 1000 / 60;
    int sec = position / 1000 % 60;
    QString str;

    if(min > 9)
        str += QString::number(min);
    else
        str += "0" + QString::number(min);
    str += ":";
    if(sec > 9)
        str += QString::number(sec);
    else
        str += "0" + QString::number(sec);

    label[0]->setText(str);
}

void MainWindow::progressSliderRelease()
{
    videoPlayer->setPosition(progressSlider->value());
}

void MainWindow::volumeSliderRelease()
{
    videoPlayer->setVolume(volumeSlider->value());
}

