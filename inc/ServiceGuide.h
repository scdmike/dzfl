#ifndef SERVICEGUIDE_H
#define SERVICEGUIDE_H

#include "UILogic.h"

class ServiceGuide : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE void nextPageClick();
    Q_INVOKABLE void prevPageClick();
    Q_INVOKABLE void guideListClick(int index);

public:
    void Show(Record& vdata);
    const char* UIObjectName() { return "ServiceGuide"; }
    bool Init();
    void Hide();
    UILogic* GetDetailPage() { return detailPage; }
    ServiceGuide();

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

class ServiceGuideOther : public ServiceGuide {
public:
    ServiceGuideOther();
    void Show(Record& vdata);
    const char* UIObjectName() { return "ServiceGuideOther"; }
};

#endif // SERVICEGUIDE_H
