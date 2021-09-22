#ifndef AUDIORECORD_H
#define AUDIORECORD_H

#include <QUrl>
#include <QObject>
#include <QAudioRecorder>
#include <QAudioEncoderSettings>
#include <QtNetwork>

class AudioRecord : public QObject {
Q_OBJECT
public:
    ~AudioRecord();
    void StopCapture();
    static AudioRecord& Instance();
    void Capture(const QString& serviceID);

protected:
    explicit AudioRecord(QObject *parent = 0);

private:
    QAudioRecorder      audioRecorder;
};

#define IAudioRecord AudioRecord::Instance()

#endif // AUDIORECORD_H
