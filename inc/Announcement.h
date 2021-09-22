#ifndef ANNOUNCEMENT_H
#define ANNOUNCEMENT_H

#include "UILogic.h"

class Announcement : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE void nextPageClick();
    Q_INVOKABLE void prevPageClick();
    Q_INVOKABLE void announcementListClick(int index);

public:
    void Show();
    QByteArray HttpPost(const QString& host, int port, const QString& url,const QByteArray& postDat, const QString& contentType);
    int GetHttpContentLength(const QByteArray& httpData, int httpHeadLen);
    const char* UIObjectName() { return "AnnouncementPage"; }
    bool Init();
    bool Login();
    bool SplitUrl(const QString& urlForSp, QString& host, int& port, QString& url);
    Announcement();


private:
    void ShowPage(int page);
    void SetAnnouncementValue(int index, Record value);

private:
    Record                      announcementList;
    int                         totalPage;
    int                         currentPage;
    int                         selectIndex;
    QList<QQuickItem*>          uiAnnouncementList;
    QString         token;
    QString         rootHost;
    int             rootPort;
    QString         rootUrl;
    UILogic*                    detailPage;
};

#endif //ANNOUNCEMENT_H
