#ifndef SERVICEGUIDEDETAIL_H
#define SERVICEGUIDEDETAIL_H

#include "UILogic.h"

class ServiceGuideDetail : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE void btnClick(int index);
    Q_INVOKABLE void dragMove(int x, int y);
    Q_INVOKABLE void sendMessage();
    Q_INVOKABLE void showMobileInput();

signals:
    void loaded();

public:
    void Show(Record& vdata);
    virtual bool Init();
    const char* UIObjectName() { return "ServiceGuideDetail"; }

protected:
    Record          guideContent;
    QString         guideID;
    QQuickItem*     grid;
    QQuickItem*     gridSG;
    QString         selectButton;
};

class ServiceGuideDetailOther : public ServiceGuideDetail {
Q_OBJECT
public:
    const char* UIObjectName() { return "ServiceGuideDetailOther"; }
};

class ServiceGuideDetailWH : public ServiceGuideDetail {
Q_OBJECT
public:
    const char* UIObjectName() { return "ServiceGuideDetailWH"; }
};

#endif // SERVICEGUIDEDETAIL_H
