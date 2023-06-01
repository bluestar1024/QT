#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QListWidget>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QSpacerItem>
#include <QWidget>
#include <QBoxLayout>

struct mediaFileInfo{
    QString filePathWithName;
    QString fileNameFormat;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMediaPlayer *videoPlayer;
    QMediaPlaylist *videoPlaylist;
    QList<mediaFileInfo> videoFile;
    QVideoWidget *videoWidget;
    QListWidget *listWidget;
    QSlider *progressSlider;
    QSlider *volumeSlider;
    QPushButton *pushButton[6];
    QLabel *label[2];
    QSpacerItem *spacerItem[2];
    QWidget *hWidget[2];
    QWidget *vWidget[2];
    QHBoxLayout *hLayout[2];
    QVBoxLayout *vLayout[2];

    void videoPlayerLayout();
    void videoPlayerInit();
    void scanVideoFiles();

private slots:
    void btnPlayClicked();
    void btnNextClicked();
    void btnVolumeUpClicked();
    void btnVolumeDownClicked();
    void btnFullScreenClicked();
    void btnHalfScreenClicked();
    void videoPlayerStateChanged(QMediaPlayer::State);
    void listWidgetItemClicked(QListWidgetItem *);
    void videoPlaylistCurrentIndexChanged(int);
    void videoPlayerDurationChanged(qint64);
    void videoPlayerPositionChanged(qint64);
    void progressSliderRelease();
    void volumeSliderRelease();
};
#endif // MAINWINDOW_H
