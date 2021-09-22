#include "../inc/ServiceGuideDetailXM.h"
#include <QQmlApplicationEngine>
#include "../public/Cache.h"
#include "../public/PixmapLoader.h"
#include "../inc/FramePage.h"
//
void ServiceGuideDetailXM::Show(Record& vdata)
{
    guideID = (const char*)vdata;

    Record cmd;
    cmd["cmd"] = "GetInfoContentByTypeCode";
    cmd["typeCode"] = "tzgg";
    cmd["id"] = guideID;
    guideContent = CacheInstance.ServiceDoCommand(cmd.ToString());

    page->setProperty("itemID", guideID);
    btnClick(0);

    UIPage()->setVisible(true);
    emit loaded();
}

void ServiceGuideDetailOtherXM::Show(Record& vdata)
{
    guideID = (const char*)vdata;

    Record cmd;
    cmd["cmd"] = "GetInfoContentByTypeCode";
    cmd["typeCode"] = "zcfg";
    cmd["id"] = guideID;
    guideContent = CacheInstance.ServiceDoCommand(cmd.ToString());

    page->setProperty("itemID", guideID);
    btnClick(0);

    UIPage()->setVisible(true);
    emit loaded();
}

void ServiceGuideDetailXM::showMobileInput() {
    QString serviceid = (const char*)FramePage::GetUserInfo()["currentQueueNum"];
    if(serviceid.isEmpty() || serviceid == "0") {
        UIItem("tbOutput")->setProperty("text", "");
    } else {
        Record cmd;
        cmd["cmd"] = "GetServicePID";
        cmd["ServiceID"] = serviceid;
        Record serviceInfo = CacheInstance.ServiceDoCommand(cmd.ToString());
        UIItem("tbOutput")->setProperty("text", QString(serviceInfo["Phone"]));
    }

    UIItem("sendMessage")->setVisible(true);
}

void ServiceGuideDetailXM::sendMessage() {
    QString mobile = UIItem("tbOutput")->property("text").toString();
    QString msg = UIItem("tbContent")->property("text").toString();

    Record cmd;
    cmd["cmd"] = "SendMessage";
    cmd["mobile"] = mobile;
    cmd["msg"] = selectButton + msg;

    Record result = CacheInstance.ServiceDoCommand(cmd.ToString());
    if((int)result["Succ"] == 1) {
        UIItem("sendMessage")->setVisible(false);
        UIItem("msgResult")->setProperty("text", "短信发送完成");
    } else {
        UIItem("msgResult")->setProperty("text", "短信发送失败");
    }
    UIItem("msgResult")->setVisible(true);
}

void ServiceGuideDetailXM::dragMove(int x, int y)
{
    QQuickItem* grid = UIItem("tbGrid");
    QQuickItem* content = NULL;
    if(UIItem("tbContent")->isVisible())
        content = UIItem("tbContent");
    else
        content = UIItem("imgContent");
    qreal newX = content->x() + x;
    qreal newY = content->y() + y;

    newX = qMax(grid->width() - content->width(), newX);
    newY = qMax(grid->height() - content->height(), newY);
    newX = qMin(newX, qreal(0.0));
    newY = qMin(newY, qreal(0.0));
    content->setPosition(QPointF(newX, newY));
}

bool ServiceGuideDetailXM::Init() {
    bool ret = UILogic::Init();
    grid = UIPage();
    QString SG = UIObjectName();
    SG += "SG";
    gridSG = UIItem(SG.toUtf8());
    return ret;
}

void ServiceGuideDetailXM::btnClick(int index)
{
    UIItem("sendMessage")->setVisible(false);
    UIItem("msgResult")->setVisible(false);
    if (guideID.isEmpty() || guideContent.Size() == 0) return;

    QString text;
    switch(index)
    {
    case 0:
    {
        text = (const char*)guideContent["Infocontent"];
        QByteArray t = QByteArray::fromBase64(text.toUtf8());
        text = t.data();
//        text.replace(QRegExp("<STYLE>.*</STYLE>"),"");
        selectButton = "【法律依据】";
        if(text.startsWith("Base64://")) {
            grid->setVisible(false);
            gridSG->setVisible(true);
            UIPage() = gridSG;
        } else {
            grid->setVisible(true);
            gridSG->setVisible(false);
            UIPage() = grid;
        }
        break;
    }
    case 1:
        text = (const char*)guideContent["DeptName"];
        selectButton = "【办理条件】";
        break;
    case 2:
        text = (const char*)guideContent["Infocontent"];
        selectButton = "【申报材料】";
        break;
    case 3:
        text = (const char*)guideContent["approvalProcess"];
        selectButton = "【办理程序】";
        break;
    case 4:
        text = (const char*)guideContent["chargeNorm"];
        selectButton = "【收费标准】";
        break;
    case 5:
        text = (const char*)guideContent["commitForTime"];
        selectButton = "【办理时限】";
        break;
    }
    char buf[16];
    for (int i = 0; i < 6; i++) {
        sprintf(buf, "btn%d", i);
        UIItem(buf)->setVisible(i == index ? true : false);
    }
    QString name = QString(guideContent["Title"]).replace("<BR>", "\n");
    if (name.length() > 46)
        name = name.left(43) + "...";
    UIItem("tbName")->setProperty("text", name);

    if(text.startsWith("Base64://")) {
        text = text.remove('\r');
        text = text.remove('\n');

        QString imgSource = LoadTifImage(text);
        if(imgSource.isEmpty())
            imgSource = MyLoadImage(text);
        if(!imgSource.isEmpty()) {
            QQuickItem* imgContent = UIItem("imgContent");
            imgContent->setProperty("source", imgSource);
            imgContent->setY(0);
            imgContent->setX(0);
            imgContent->setVisible(true);
            UIItem("tbContent")->setProperty("text", "");
            UIItem("tbContent")->setVisible(false);
            return;
        }
    }

    text.replace("<BR>", "\n");
    UIItem("tbContent")->setProperty("text", text);
    UIItem("tbContent")->setY(0);
    UIItem("tbContent")->setX(0);

    UIItem("imgContent")->setVisible(false);
    UIItem("tbContent")->setVisible(true);
}
