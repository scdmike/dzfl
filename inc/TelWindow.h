#ifndef TELWINDOW_H
#define TELWINDOW_H

#include "UILogic.h"

class TelWindow : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE void num(QString n);
    Q_INVOKABLE void crClick();
    Q_INVOKABLE void okClick();
    Q_INVOKABLE void savePhone(QString num, QString serviceid = "");

public:
    void Show(Record& vdata);
    const char* UIObjectName() { return "TelWindow"; }

private:
    QString             serviceid;
    QString             input;
};

#endif // TELWINDOW_H
