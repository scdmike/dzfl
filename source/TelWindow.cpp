#include <QQuickItem>
#include "../public/Cache.h"
#include "../inc/TelWindow.h"
#include "../inc/FramePage.h"

void TelWindow::Show(Record& vdata)
{
    serviceid = (const char*)vdata;

    Record cmd;
    cmd["cmd"] = "GetServicePID";
    cmd["ServiceID"] = serviceid;
    Record serviceInfo = CacheInstance.ServiceDoCommand(cmd.ToString());

    UIItem("tbName")->setProperty("text", QString(serviceInfo["Name"]));
    UIItem("tbTel")->setProperty("text", QString(serviceInfo["Phone"]));

    input.clear();

    UIPage()->setVisible(true);
}

void TelWindow::num(QString n)
{
    if(input.length() >= 11)
        return;
    input += n;
    UIItem("tbOutput")->setProperty("text", input);
}

void TelWindow::crClick()
{
    input.clear();
    UIItem("tbOutput")->setProperty("text", input);
}

void TelWindow::savePhone(QString input, QString serviceid)
{
    //保存手机号
    Record cmd;
    cmd["cmd"] = "SavePhone";

    if(serviceid.isEmpty())
        cmd["ServiceID"] = (const char*)FramePage::GetUserInfo()["serviceID"];
    else
        cmd["ServiceID"] = serviceid;

    cmd["Phone"] = input;
    CacheInstance.ServiceDoCommand(cmd.ToString());
}

void TelWindow::okClick()
{
    UIItem("tbTel")->setProperty("text", input);
    savePhone(input, serviceid);
}
