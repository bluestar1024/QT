#include "mainwindow.h"
#include <QCoreApplication>
#include <QDir>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    audioRecorderlayout();
    audioRecorderInit();
    scanAudioFile();

    devVars.append(QVariant(QString()));
    for(auto &audioInput: audioRecorder->audioInputs())
        devVars.append(QVariant(audioInput));
    codecVars.append(QVariant(QString()));
    for(auto &audioCodec: audioRecorder->supportedAudioCodecs())
        codecVars.append(QVariant(audioCodec));
    bitRateVars.append(QVariant(0));
    bitRateVars.append(QVariant(32000));
    bitRateVars.append(QVariant(64000));
    bitRateVars.append(QVariant(96000));
    bitRateVars.append(QVariant(128000));
    sampleRateVars.append(QVariant(0));
    for(int &sampleRate: audioRecorder->supportedAudioSampleRates())
        sampleRateVars.append(QVariant(sampleRate));
    qualityVars.append(QVariant(int(QMultimedia::LowQuality)));
    qualityVars.append(QVariant(int(QMultimedia::NormalQuality)));
    qualityVars.append(QVariant(int(QMultimedia::HighQuality)));
    channelCountVars.append(QVariant(-1));
    channelCountVars.append(QVariant(1));
    channelCountVars.append(QVariant(2));
    channelCountVars.append(QVariant(4));

    connect(pushButton[0], &QPushButton::clicked, this, &MainWindow::btRecordClicked);

    connect(listWidget,
            static_cast<void (QListWidget::*)(QListWidgetItem *,QListWidgetItem *)>
            (&QListWidget::currentItemChanged),
            this,
            static_cast<void (MainWindow::*)(QListWidgetItem *,QListWidgetItem *)>
            (&MainWindow::listWidgetCurrentItemChanged));

    connect(listWidget,
            static_cast<void (QListWidget::*)(QListWidgetItem *)>
            (&QListWidget::itemClicked),
            this,
            static_cast<void (MainWindow::*)(QListWidgetItem *)>
            (&MainWindow::listWidgetItemClicked));

    connect(audioPlayer,
            static_cast<void (QMediaPlayer::*)(QMediaPlayer::State)>
            (&QMediaPlayer::stateChanged),
            this,
            static_cast<void (MainWindow::*)(QMediaPlayer::State)>
            (&MainWindow::audioPlayerStateChanged));

    connect(pushButton[1], &QPushButton::clicked, this, &MainWindow::btPreviousClicked);

    connect(pushButton[2], &QPushButton::clicked, this, &MainWindow::btNextClicked);

    connect(pushButton[3], &QPushButton::clicked, this, &MainWindow::btRemoveClicked);

    connect(audioRecorder,
            static_cast<void (QAudioRecorder::*)(qint64)>
            (&QAudioRecorder::durationChanged),
            this,
            static_cast<void (MainWindow::*)(qint64)>
            (&MainWindow::audioRecorderDurationChanged));

    connect(audioPlayer,
            static_cast<void (QMediaPlayer::*)(qint64)>
            (&QMediaPlayer::positionChanged),
            this,
            static_cast<void (MainWindow::*)(qint64)>
            (&MainWindow::audioPlayerPositionChanged));

    connect(audioProbe,
            static_cast<void (QAudioProbe::*)(const QAudioBuffer &)>
            (&QAudioProbe::audioBufferProbed),
            this,
            static_cast<void (MainWindow::*)(const QAudioBuffer &)>
            (&MainWindow::processBuffer));
}

MainWindow::~MainWindow()
{
}

void MainWindow::audioRecorderlayout()
{
    this->setGeometry(100, 100, 1024, 600);
    listWidget = new QListWidget();
    for(int i = 0; i < 4; i++)
        pushButton[i] = new QPushButton();
    levelLabel = new QLabel();
    for(int i = 0; i < 4; i++)
        progressBar[i] = new QProgressBar();
    for(int i = 0; i < 2; i++)
    {
        hWidget[i] = new QWidget();
        vWidget[i] = new QWidget();
        hLayout[i] = new QHBoxLayout();
        vLayout[i] = new QVBoxLayout();
    }
    vWidget[1]->setParent(this);

    listWidget->setFixedSize(this->width(), this->height() - 100);
    listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    pushButton[0]->setObjectName("btn_record");
    pushButton[1]->setObjectName("btn_previous");
    pushButton[2]->setObjectName("btn_next");
    pushButton[3]->setObjectName("btn_remove");
    for(int i = 0; i < 4; i++)
        pushButton[i]->setFixedSize(this->height() / 6 - 20, this->height() / 6 - 20);
    for(int i = 0; i < 4; i++)
    {
        progressBar[i]->setOrientation(Qt::Vertical);
        progressBar[i]->setTextVisible(false);
    }

    this->setCentralWidget(vWidget[0]);
    vWidget[0]->setObjectName("vWidget0");
    vWidget[0]->setLayout(vLayout[0]);
    vLayout[0]->addWidget(listWidget);
    vLayout[0]->addWidget(hWidget[0]);
    vLayout[0]->setContentsMargins(0, 0, 0, 0);

    hWidget[0]->setObjectName("hWidget0");
    hWidget[0]->setLayout(hLayout[0]);
    for(int i = 0; i < 4; i++)
        hLayout[0]->addWidget(pushButton[i]);
    hLayout[0]->setContentsMargins(0, 0, 0, 0);

    vWidget[1]->setObjectName("vWidget1");
    vWidget[1]->setGeometry(this->width() / 2 - 200,
                            this->height() / 2 - 150, 400, 300);
    levelLabel->setFixedHeight(vWidget[1]->height() / 4);
    vWidget[1]->setLayout(vLayout[1]);
    vLayout[1]->addWidget(levelLabel);
    vLayout[1]->addWidget(hWidget[1]);
    vLayout[1]->setContentsMargins(0, 0, 0, 0);

    hWidget[1]->setObjectName("hWidget1");
    for(int i = 0; i < 4; i++)
        progressBar[i]->setMaximumWidth(vWidget[1]->width());
    hWidget[1]->setLayout(hLayout[1]);
    for(int i = 0; i < 4; i++)
        hLayout[1]->addWidget(progressBar[i]);
    hLayout[1]->setContentsMargins(0, 0, 0, 0);

    levelLabel->setAlignment(Qt::AlignCenter);
    clearRecordWidget();

    vWidget[1]->raise();
    vWidget[1]->hide();
}

void MainWindow::audioRecorderInit()
{
    audioRecorder = new QAudioRecorder(this);
    audioProbe = new QAudioProbe(this);
    audioPlayer = new QMediaPlayer(this);
    audioPlaylist = new QMediaPlaylist(this);
    audioProbe->setSource(audioRecorder);
    audioPlayer->setPlaylist(audioPlaylist);
    audioPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

void MainWindow::scanAudioFile()
{
    audioFile.clear();
    audioPlaylist->clear();
    listWidget->clear();
    QString str = QCoreApplication::applicationDirPath() + "/Sounds";
    QDir dir(str);
    QStringList filters;
    filters << "*.mp3";
    QStringList fileNameList = dir.entryList(filters,
                                             QDir::Files | QDir::Readable,
                                             QDir::Name);
    FileInfo fileInfo;
    foreach(QString fileName, fileNameList)
    {
        fileInfo.fileNameWithPath = QCoreApplication::applicationDirPath() +
                                    "/Sounds/" + fileName;
        fileInfo.fileName = fileName;
        audioFile << fileInfo;
        audioPlaylist->addMedia(QMediaContent(QUrl::
                                              fromLocalFile(fileInfo.fileNameWithPath)));
        listWidget->addItem(new QListWidgetItem(QIcon(":/icons/play.png"), fileInfo.fileName));
    }
}

void MainWindow::clearRecordWidget()
{
    levelLabel->setText("已录制0S");
    for(int i = 0; i < 4; i++)
        progressBar[i]->setValue(0);
}

QVector<qreal> MainWindow::getAudioLevels(const QAudioBuffer &buffer)
{
    QVector<qreal> values;
    QAudioFormat format = buffer.format();
    int channelCount = format.channelCount();
    values.fill(0, channelCount);
    if(!format.isValid() || QAudioFormat::LittleEndian != format.byteOrder() ||
                            "audio/pcm" != format.codec())
        return values;
    int frameCount = buffer.frameCount();
    qreal peakValue;

    switch(format.sampleType())
    {
        case QAudioFormat::Unknown:

        case QAudioFormat::UnSignedInt:
            switch(format.sampleSize())
            {
                case 8:
                    values = getAudioLevels(buffer.constData<quint8>(),
                                            frameCount,
                                            channelCount);
                    peakValue = UCHAR_MAX;
                    break;
                case 16:
                    values = getAudioLevels(buffer.constData<quint16>(),
                                            frameCount,
                                            channelCount);
                    peakValue = USHRT_MAX;
                    break;
                case 32:
                    values = getAudioLevels(buffer.constData<quint32>(),
                                            frameCount,
                                            channelCount);
                    peakValue = UINT_MAX;
                    break;
                default:
                    return values;
            }
            for(int i = 0; i < values.size(); i++)
                values[i] = qAbs(values[i] - peakValue / 2) / (peakValue / 2);
            break;

        case QAudioFormat::Float:
            if(32 == format.sampleSize())
            {
                values = getAudioLevels(buffer.constData<float>(),
                                        frameCount,
                                        channelCount);
                peakValue = 1.00003;
                for(int i = 0; i < values.size(); i++)
                    values[i] /= peakValue;
            }
            break;
        case QAudioFormat::SignedInt:
            switch(format.sampleSize())
            {
                case 8:
                    values = getAudioLevels(buffer.constData<qint8>(),
                                            frameCount,
                                            channelCount);
                    peakValue = CHAR_MAX;
                    break;
                case 16:
                    values = getAudioLevels(buffer.constData<qint16>(),
                                            frameCount,
                                            channelCount);
                    peakValue = SHRT_MAX;
                    break;
                case 32:
                    values = getAudioLevels(buffer.constData<qint32>(),
                                            frameCount,
                                            channelCount);
                    peakValue = INT_MAX;
                    break;
                default:
                    return values;
            }
            for(int i = 0; i < values.size(); i++)
                values[i] /= peakValue;
            break;

        default:
            return values;
    }
    return values;
}

void MainWindow::btRecordClicked()
{
    if(QMediaPlayer::StoppedState != audioPlayer->state())
        audioPlayer->stop();
    if(audioRecorder->state() != QMediaRecorder::RecordingState)
    {
        audioRecorder->setAudioInput(devVars.at(0).toString());
        QAudioEncoderSettings settings;
        settings.setCodec(codecVars.at(0).toString());
        settings.setBitRate(bitRateVars.at(0).toInt());
        settings.setSampleRate(sampleRateVars.at(0).toInt());
        settings.setQuality(QMultimedia::EncodingQuality(qualityVars.at(0).toInt()));
        settings.setChannelCount(channelCountVars.at(0).toInt());
        settings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
        audioRecorder->setAudioSettings(settings);
        audioRecorder->setOutputLocation(QUrl::fromLocalFile(QString("./Sounds/%1.mp3").
                                         arg(QDateTime::currentDateTime().toString())));
        vWidget[1]->show();
        audioRecorder->record();
    }
    else
    {
        audioRecorder->stop();
        clearRecordWidget();
        vWidget[1]->hide();
        scanAudioFile();
    }
}

void MainWindow::listWidgetCurrentItemChanged(QListWidgetItem *current,
                                              QListWidgetItem *previous)
{
    if(-1 != listWidget->row(previous))
        previous->setText(audioFile.at(listWidget->row(previous)).fileName);

    if(audioPlayer->state() == QMediaPlayer::PlayingState)
        audioPlayer->stop();

    if(-1 != listWidget->row(current))
        audioPlaylist->setCurrentIndex(listWidget->row(current));
}

void MainWindow::listWidgetItemClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    if(audioPlayer->state() != QMediaPlayer::PlayingState)
        audioPlayer->play();
    else
        audioPlayer->stop();
}

void MainWindow::audioPlayerStateChanged(QMediaPlayer::State state)
{
    for(int i = 0; i < listWidget->count(); i++)
        listWidget->item(i)->setIcon(QIcon(":/icons/play.png"));
    if(QMediaPlayer::PlayingState == state)
        listWidget->currentItem()->setIcon(QIcon(":/icons/pause.png"));
    else
        listWidget->currentItem()->setIcon(QIcon(":/icons/play.png"));
}

void MainWindow::btPreviousClicked()
{
    if(0 == listWidget->count())
        return;
    audioPlayer->stop();
    if(-1 == listWidget->currentRow())
        listWidget->setCurrentRow(0);
    if(0 == listWidget->currentRow())
        listWidget->setCurrentRow(listWidget->count() - 1);
    else
        listWidget->setCurrentRow(listWidget->currentRow() - 1);
    audioPlaylist->setCurrentIndex(listWidget->currentRow());
    audioPlayer->play();
}

void MainWindow::btNextClicked()
{
    if(0 == listWidget->count())
        return;
    audioPlayer->stop();
    if(-1 == listWidget->currentRow())
        listWidget->setCurrentRow(0);
    if(listWidget->count() - 1 == listWidget->currentRow())
        listWidget->setCurrentRow(0);
    else
        listWidget->setCurrentRow(listWidget->currentRow() + 1);
    audioPlaylist->setCurrentIndex(listWidget->currentRow());
    audioPlayer->play();
}

void MainWindow::btRemoveClicked()
{
    if(0 == listWidget->count())
        return;
    int index = listWidget->currentRow();
    if(-1 == index)
        return;

    QFile file(audioFile.at(index).fileNameWithPath);
    file.remove();

    audioFile.removeAt(index);

    audioPlaylist->removeMedia(index);

    listWidget->takeItem(index);

    if(0 != index)
        listWidget->setCurrentRow(index - 1);
    else
        audioPlaylist->setCurrentIndex(0);
}

void MainWindow::audioRecorderDurationChanged(qint64 duration)
{
    vWidget[1]->show();
    levelLabel->setText(QString("已录制%1S").arg(duration / 1000));
}

void MainWindow::audioPlayerPositionChanged(qint64 position)
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
    str += "/";

    int duration = audioPlayer->duration();
    min = duration / 1000 / 60;
    sec = duration / 1000 % 60;

    if(min > 9)
        str += QString::number(min);
    else
        str += "0" + QString::number(min);
    str += ":";
    if(sec > 9)
        str += QString::number(sec);
    else
        str += "0" + QString::number(sec);

    listWidget->currentItem()->setText(audioFile.at(listWidget->currentRow()).
                                       fileName + "\t" + str);
}

void MainWindow::processBuffer(const QAudioBuffer &buffer)
{
    int channelCount = buffer.format().channelCount();
    for(int i = 0; i < 4; i++)
    {
        if(i < channelCount)
            progressBar[i]->setVisible(true);
        else
            progressBar[i]->setVisible(false);
    }

    QVector<qreal> levels = getAudioLevels(buffer);
    for(int i = 0; i < levels.count(); i++)
        progressBar[i]->setValue(levels[i] * 100);
}

template<typename T>
QVector<qreal> MainWindow::getAudioLevels(const T *buffer, int frames, int channels)
{
    qreal value;
    QVector<qreal> values;
    values.fill(0, channels);

    for(int i = 0; i < frames; i++)
    {
        for(int j = 0; j < channels; j++)
        {
            value = qAbs(qreal(buffer[i * channels + j]));
            if(value > values[j])
                values.replace(j, value);
        }
    }
    return values;
}
