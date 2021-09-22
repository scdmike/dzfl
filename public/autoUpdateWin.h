#ifndef AUTOUPDATEWIN_H
#define AUTOUPDATEWIN_H

#include <QObject>
#include <QTimer>
#include <QtNetwork>
#include "../public/Record.h"

class AutoUpdateWin: public QObject
{
Q_OBJECT
public:
    AutoUpdateWin();
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

#endif // AUTOUPDATEWIN_H
