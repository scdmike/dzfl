#ifndef AUTOUPDATE_H
#define AUTOUPDATE_H

#include <QObject>
#include <QTimer>
#include <QtNetwork>
#include "../public/Record.h"
#include "../public/identify.h"

#define main(a, b) __main(QGuiApplication *app)

class AutoUpdate: public QObject
{
Q_OBJECT
public:
    AutoUpdate();
    void GetFiles();
    void ReplaceNewFile();


public slots:
    void GetFileInfo();
    void UpdateFileResult(QNetworkReply *reply);

private:
    Record                  fileList;
    QNetworkAccessManager   manager;
    QString                 currentFile;
    QString                 updatepath;
};

class UpdateBackWorker : public QObject {
Q_OBJECT
public:
    UpdateBackWorker();

public slots:
    void                OnTimer();

private:
    QTimer              timer;
};

#endif // AUTOUPDATE_H
