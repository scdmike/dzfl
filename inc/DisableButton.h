#ifndef DISABLEBUTTON_H
#define DISABLEBUTTON_H

#include "UILogic.h"
#include <QTimer>

class DisableButton : public UILogic
{
Q_OBJECT
public:
    const char* UIObjectName();
    DisableButton();
    void Start(UILogic* page, const char* gridName);

public Q_SLOTS:
    void        OnTimer();

private:
    UILogic*            parent;
    QQuickItem*         tbTime;
    QTimer              timer;
};

#endif // DISABLEBUTTON_H
