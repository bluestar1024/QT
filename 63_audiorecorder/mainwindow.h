#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioRecorder>
#include <QAudioProbe>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QWidget>
#include <QBoxLayout>

struct FileInfo{
    QString fileNameWithPath;
    QString fileName;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private:
    QAudioRecorder *audioRecorder;
    QAudioProbe *audioProbe;
    QMediaPlayer *audioPlayer;
    QMediaPlaylist *audioPlaylist;
    QList<FileInfo> audioFile;
    QVector<QVariant> devVars;
    QVector<QVariant> codecVars;
    QVector<QVariant> bitRateVars;
    QVector<QVariant> sampleRateVars;
    QVector<QVariant> qualityVars;
    QVector<QVariant> channelCountVars;
    QListWidget *listWidget;
    QPushButton *pushButton[4];
    QLabel *levelLabel;
    QProgressBar *progressBar[4];
    QWidget *hWidget[2];
    QWidget *vWidget[2];
    QHBoxLayout *hLayout[2];
    QVBoxLayout *vLayout[2];
    
    void audioRecorderlayout();
    void audioRecorderInit();
    void scanAudioFile();
    void clearRecordWidget();
    QVector<qreal> getAudioLevels(const QAudioBuffer &buffer);
    template<typename T>
    QVector<qreal> getAudioLevels(const T *buffer, int frames, int channels);
    
private slots:
    void btRecordClicked();
    void listWidgetCurrentItemChanged(QListWidgetItem *, QListWidgetItem *);
    void listWidgetItemClicked(QListWidgetItem *);
    void audioPlayerStateChanged(QMediaPlayer::State);
    void btPreviousClicked();
    void btNextClicked();
    void btRemoveClicked();
    void audioRecorderDurationChanged(qint64);
    void audioPlayerPositionChanged(qint64);
    void processBuffer(const QAudioBuffer &);
};
#endif // MAINWINDOW_H
