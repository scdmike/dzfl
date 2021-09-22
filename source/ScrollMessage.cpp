#include "../inc/ScrollMessage.h"
#include "../public/Cache.h"

const char* ScrollMessage::UIObjectName()
{
    if(parent)
        return parent->UIObjectName();
    return "";
}

ScrollMessage::ScrollMessage(QObject* p)
    : UILogic(p), parent(NULL), msg(NULL)
{
    page = NULL;
}

void ScrollMessage::Start(UILogic* page, const char* gridName)
{
    if(parent == NULL)
    {
        this->page = page->UIItem(gridName);
        msg = UIItem("msg");
        if(UIPage()->childItems().contains(UIItem("msgBak")))
            msgBak = UIItem("msgBak");
        else
            msgBak = NULL;
        if(UIPage()->childItems().contains(UIItem("msgRoll")))
            msgRoll = UIItem("msgRoll");
        else
            msgRoll = NULL;
        parent = page;

        QString text = UIPage()->property("text").toString();
        if(!text.isEmpty())
            setText(text);
        else if(CsGetConfig("滚动消息")[0] != '\0')
            setText(CsGetConfig("滚动消息"));

         qDebug() << ">>>滚动消息>>>" <<CsGetConfig("办事指南地址");

        QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
    }

    timer.start(100);
}

QString ScrollMessage::getText() const
{
    return msg->property("text").toString();
}
void ScrollMessage::setText(const QString &text)
{
    QString old = msg->property("text").toString();
    if(old == text)
        return;

    timer.stop();
    msg->setX(0);
    msg->setY(0);
    msg->setProperty("text", text);
    if(msgRoll&&msgRoll->property("text").toString() != "true") {
        if(msg->width() > UIPage()->width() + 2) {
            QString text1 = text.left(16) + "...";
            msg->setProperty("text", text1);
        }
    }

    if(msgBak) {
        if(msg->width() > UIPage()->width() + 2) {
            qreal w = msg->width();
            msgBak->setX(w);
            msgBak->setVisible(true);
        } else if(msg->height() > UIPage()->height() + 2) {
            qreal h = msg->height();
            msgBak->setY(h);
            msgBak->setVisible(true);
        }
    }
    timer.start(100);
}

void ScrollMessage::OnTimer()
{
    if(!parent->UIPage()->isVisible())
    {
        timer.stop();
        return;
    }

    if(msgRoll) {
        if(msgRoll->property("text").toString() != "true") {
            timer.stop();
            if(msgBak) {
                msgBak->setProperty("visible", false);
            }
            return;
        }
    }

    if(msg->width() > UIPage()->width() + 2)                //横向滚动
    {
        if(msgBak) {
            msg->setX(msg->x() - 2);
            msgBak->setX(msgBak->x() - 2);
            if(msg->x() + msg->width() < 0)
                msg->setX(msgBak->x() + msgBak->width());
            if(msgBak->x() + msgBak->width() < 0)
                msgBak->setX(msg->x() + msg->width());
        } else {
            msg->setX(msg->width() + msg->x() > UIPage()->width() ? msg->x() - 2 : 20);
        }
    } else if(msg->height() > UIPage()->height() + 2) {     //竖向滚动
        if(msgBak) {
            qreal y1 = msg->y();
            qreal y2 = msgBak->y();
            qreal h1 = msg->height();
            qreal h2 = msgBak->height();
            msg->setY(y1 - 2);
            msgBak->setY(y2 - 2);
            if(y1 + h1 < 0)
                msg->setY(y2 + h2);
            if(y2 + h2 < 0)
                msgBak->setY(y1 + h1);
        } else {
            msg->setY(msg->height() + msg->y() > UIPage()->height() ? msg->y() - 2 : 20);
        }
    }else {
        if(msgBak)
            msgBak->setVisible(false);
        timer.stop();
    }
}
