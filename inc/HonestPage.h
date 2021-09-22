#ifndef HONESTPAGE_H
#define HONESTPAGE_H

#include "ScrollMessage.h"
#include "DisableButton.h"
#include "../public/Cache.h"

class HonestPage : public UILogic
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
        if(UIItem("t1")->property("text").toString().isEmpty()) {
            QString userID = (const char*)vdata;

            Record cmd;
            cmd["cmd"]      = "GetHonest";
            cmd["userID"]   = userID;
            Record info = CacheInstance.ServiceDoCommand(cmd.ToString());
            if(info.Size() == 0) return;
            qDebug() << info["Honest"].ToString();
            char buf[0xff];
            for(unsigned i = 0; i < info["Honest"].Size(); i++) {
                sprintf(buf, "t%d", i);
                QString str = QString((const char*)info["Honest"][i]["title"]);
                str.replace("\r\n", "\n");
                UIItem(buf)->setProperty("text", str);

                sprintf(buf, "c%d", i);
                str = QString((const char*)info["Honest"][i]["content"]);
                str.replace("\r\n", "\n");
                UIItem(buf)->setProperty("text", str);
            }
        }
        UIPage()->setVisible(true);
    }

    const char* UIObjectName() { return "HonestPage"; }
};

#endif // HONESTPAGE_H
