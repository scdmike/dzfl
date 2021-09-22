#ifndef SCROLLMESSAGE_H
#define SCROLLMESSAGE_H

#include "UILogic.h"
#include <QTimer>

class ScrollMessage : public UILogic
{
Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText)
public:
    const char* UIObjectName();
    ScrollMessage(QObject* parent = NULL);
    void Start(UILogic* page, const char* gridName);

    QString getText() const;
    void setText(const QString &text);

public Q_SLOTS:
    void        OnTimer();

private:
    UILogic*            parent;
    QQuickItem*   msg;
    QQuickItem*   msgBak;
    QQuickItem*   msgRoll;
    QTimer              timer;
};

#endif // SCROLLMESSAGE_H
