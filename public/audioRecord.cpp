#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "audiorecord.h"
#include "public/cache.h"
//
AudioRecord::AudioRecord(QObject *parent) : QObject(parent) {
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/amr");
    audioSettings.setQuality(QMultimedia::LowQuality);
    audioSettings.setChannelCount(1);

    audioRecorder.setEncodingSettings(audioSettings);
}

AudioRecord& AudioRecord::Instance() {
    static AudioRecord audioInstance;
    return audioInstance;
}

void AudioRecord::Capture(const QString& serviceID) {
    if(CsGetConfig("录音")[0] != '1') return;

    QString file = serviceID + QDateTime::currentDateTime().toString("_yyyyMMdd_hhmmss");
    qDebug() << "begin record:" << file;
    audioRecorder.setOutputLocation(QUrl::fromLocalFile(file));
    audioRecorder.record();
}

void AudioRecord::StopCapture() {
    if(CsGetConfig("录音")[0] != '1') return;

    qDebug() << "Recorder url：" << audioRecorder.outputLocation();
    audioRecorder.stop();
    QString url = CsGetConfig("音频上传地址");
    QUrl output = audioRecorder.outputLocation();
    QString putFile = output.toString().replace("file:///","");
    #ifdef ANDROID
    putFile = output.toString().replace("file:///","/");
    #endif
    QString fileName = putFile.split("/")[putFile.split("/").length() - 1];
    qDebug() << "putFile：" << putFile;
    QFile file(putFile);
    if(file.exists())
    {

        if(!file.open(QIODevice::ReadOnly))
        {
            return;
        }
        QByteArray fileContent = file.readAll();
        file.close();
        file.remove();


        QString sCrlf="\r\n";
        qsrand(QDateTime::currentDateTime().toTime_t());
        QString b=QVariant(qrand()).toString()+QVariant(qrand()).toString()+QVariant(qrand()).toString();
        QString sBoundary="---------------------------"+b;
        QString sEndBoundary=sCrlf+"--"+sBoundary+"--"+sCrlf;
        QString sContentType="multipart/form-data; boundary="+sBoundary;
        sBoundary="--"+sBoundary+sCrlf;
        QByteArray boundary=sBoundary.toLatin1();

        QByteArray sendData;

        sendData.append(boundary);
        sBoundary = sCrlf + sBoundary;
        boundary = sBoundary.toLatin1();
        sendData.append(QString("Content-Disposition: form-data; name=\"file\"; filename=\""+QString(fileName.toUtf8().constData())+"\""+sCrlf).toLatin1());
        sendData.append(QString("Content-Transfer-Encoding: 8bit"+sCrlf).toLatin1());
        sendData.append(sCrlf.toLatin1());
        sendData.append(fileContent);

        sendData.append(sEndBoundary.toLatin1());


        QNetworkRequest req;
        req.setUrl(url);
        req.setHeader(QNetworkRequest::ContentTypeHeader, sContentType.toLatin1());
        req.setHeader(QNetworkRequest::ContentLengthHeader, QVariant(sendData.size()).toString());
        QNetworkAccessManager *manager = new QNetworkAccessManager();
        manager->post(req, sendData);
    }
    else
    {
        qDebug() << "文件不存在";
    }
}

AudioRecord::~AudioRecord() {
}

