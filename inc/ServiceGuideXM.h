#ifndef SERVICEGUIDEXM_H
#define SERVICEGUIDEXM_H

#include "UILogic.h"

class ServiceGuideXM : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE void nextPageClick();
    Q_INVOKABLE void prevPageClick();
    Q_INVOKABLE void guideListClick(int index);

public:
    void Show(Record& vdata);
    const char* UIObjectName() { return "ServiceGuideXM"; }
    bool Init();
    void Hide();
    UILogic* GetDetailPage() { return detailPage; }
    ServiceGuideXM();

protected:
    void ShowPage(int page);
    void SelectGuideList(int index);
    void SetGuideGridValue(int index, Record value);

protected:
    Record                      guideList;
    int                         totalPage;
    int                         currentPage;
    QList<QQuickItem*>          uiGuideList;
    UILogic*                    detailPage;
};

class ServiceGuideOtherXM : public ServiceGuideXM {
public:
    ServiceGuideOtherXM();
    void Show(Record& vdata);
    const char* UIObjectName() { return "ServiceGuideOtherXM"; }
};


#endif // SERVICEGUIDEXM_H
