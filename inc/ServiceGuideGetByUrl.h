#ifndef ServiceGuideGetByUrlGETBYURL
#define ServiceGuideGetByUrlGETBYURL
#include "UILogic.h"

class ServiceGuideGetByUrl : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE void nextPageClick();
    Q_INVOKABLE void prevPageClick();
public:
    void Show(Record& vdata);
    QByteArray HttpPost(const QString& host, int port, const QString& url,const QByteArray& postDat, const QString& contentType);
    int GetHttpContentLength(const QByteArray& httpData, int httpHeadLen);
    const char* UIObjectName() { return "ServiceGuideGetByUrl"; }
    bool Init();
    void Hide();
    bool SplitUrl(const QString& urlForSp, QString& host, int& port, QString& url);
    //UILogic* GetDetailPage() { return detailPage; }
    ServiceGuideGetByUrl();

protected:
    void ShowPage(int page);
    void SelectGuideList(int index);
    void SetGuideGridValue(int index, Record value);

protected:
    Record                      guideList;
    int                         totalPage;
    int                         currentPage;
    QList<QQuickItem*>          uiGuideList;
    //UILogic*                    detailPage;
    QString         rootHost;
    int             rootPort;
    QString         rootUrl;
};


#endif // ServiceGuideGetByUrlGETBYURL

