#ifndef SERVICEGUIDEDETAILXM_H
#define SERVICEGUIDEDETAILXM_H

#include "UILogic.h"

class ServiceGuideDetailXM : public UILogic
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
    const char* UIObjectName() { return "ServiceGuideDetailXM"; }

protected:
    Record          guideContent;
    QString         guideID;
    QQuickItem*     grid;
    QQuickItem*     gridSG;
    QString         selectButton;
};

class ServiceGuideDetailOtherXM : public ServiceGuideDetailXM {
Q_OBJECT
public:
    void Show(Record& vdata);
    const char* UIObjectName() { return "ServiceGuideDetailOtherXM"; }
};

#endif // SERVICEGUIDEDETAILXM_H
