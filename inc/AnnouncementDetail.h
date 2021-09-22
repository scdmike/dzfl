#ifndef ANNOUNCEMENTDETAIL_H
#define ANNOUNCEMENTDETAIL_H


#include "UILogic.h"

class AnnouncementDetail : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE void btnClick();
    Q_INVOKABLE void dragMove(int x, int y);

public:
    void Show(Record& vdata);
    virtual bool Init();
    const char* UIObjectName() { return "AnnouncementDetail"; }
    bool Login();
    bool SplitUrl(const QString& urlForSp, QString& host, int& port, QString& url);
    int GetHttpContentLength(const QByteArray& httpData, int httpHeadLen);
    QByteArray HttpPost(const QString& host, int port, const QString& url,const QByteArray& postDat, const QString& contentType);


protected:
    Record          guideContent;
    QString         guideID;
    QQuickItem*     grid;
    QString         selectButton;
    QString         token;
    QString         rootHost;
    int             rootPort;
    QString         rootUrl;
};

#endif // ANNOUNCEMENTDETAIL_H
