#ifndef DUTYPAGE_H
#define DUTYPAGE_H

#include "ScrollMessage.h"
#include "DisableButton.h"
#include "../public/Cache.h"

//
class DutyPage : public UILogic
{
    Q_OBJECT
public:
    Q_INVOKABLE void dragMove(int x, int y) {
        QQuickItem* grid = UIItem("tbGrid");
        QQuickItem* content = UIItem("tbContent");

        qreal newX = content->x() + x;
        qreal newY = content->y() + y;

        newX = qMax(grid->width() - content->width(), newX);
        newY = qMax(grid->height() - content->height(), newY);
        newX = qMin(newX, qreal(0.0));
        newY = qMin(newY, qreal(0.0));
        content->setPosition(QPointF(newX, newY));
    }

    void Show(Record& vdata) {
        QString userID = (const char*)vdata;

        Record cmd;
        cmd["cmd"]      = "GetDuty";
        cmd["userID"]   = userID;
        Record info = CacheInstance.ServiceDoCommand(cmd.ToString());
        if(info.Size() == 0) return;
        qDebug() << info["Duty"].ToString();
        QString str = QString((const char*)info["Duty"]);
        str.replace("\r\n", "\n");
        str.replace(";", ";\n");
        str.replace("；", "；\n");
        UIItem("t1")->setProperty("text", str);
        UIPage()->setVisible(true);
    }

    const char* UIObjectName() { return "DutyPage"; }
};

#endif // DUTYPAGE_H
