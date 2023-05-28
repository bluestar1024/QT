#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSlider>
#include <QSpacerItem>
#include <QWidget>
#include <QBoxLayout>

struct MediaFileInfo{
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
    QMediaPlayer *musicPlayer;
    QMediaPlaylist *musicPlaylist;
    QList<MediaFileInfo> musicFile;

    QLabel *label[4];
    QListWidget *listWidget;
    QPushButton *pushButton[7];
    QSlider *progressSlider;
    QSpacerItem *spacerItem[12];
    QWidget *hWidget[4];
    QWidget *vWidget[2];
    QHBoxLayout *hLayout[4];
    QVBoxLayout *vLayout[2];

    void musicPlayerLayout();
    void musicPlayerInit();
    void scanSongs();

private slots:
    void btnPreviousClick();
    void btnPlayClick();
    void btnNextClick();
    void musicPlayerStateChange(QMediaPlayer::State);
    void listWidgetItemClick(QListWidgetItem *);
    void musicPlaylistCurrentIndexChange(int);
    void musicPlayerDurationChange(qint64);
    void musicPlayerPositionChange(qint64);
    void progressSliderReleased();
};
#endif // MAINWINDOW_H
