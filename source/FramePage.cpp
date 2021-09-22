#include "../inc/FramePage.h"
#include "../public/CopyData.h"
#include "../public/Cache.h"
#include "../inc/ServiceInfo.h"
#include "../inc/MediaPage.h"
#include "../inc/AllConfigs.h"
#include "../inc/Question.h"
#include "../inc/Announcement.h"
#include "../inc/AnnouncementDetail.h"
#include "../inc/TelWindow.h"
#include "../inc/ServiceGuide.h"
#include "../inc/ServiceGuideDept.h"
#include "../inc/ServiceGuideGetByUrl.h"
#include "../inc/HonestPage.h"
#include "../public/audioRecord.h"
#include "../inc/DutyPage.h"
#include <QDatetime>
//
FramePage::FramePage()
{
    serviceInfo = new ServiceInfo();
    UILogic::AllInstance().append(serviceInfo);


    allConfigs = new AllConfigs();
    UILogic::AllInstance().append(allConfigs);

    telWindow = new TelWindow();
    UILogic::AllInstance().append(telWindow);

    honestPage = new HonestPage();
    UILogic::AllInstance().append(honestPage);

    serviceGuideGetByUrl = new ServiceGuideGetByUrl();
    UILogic::AllInstance().append(serviceGuideGetByUrl);

    serviceGuide = new ServiceGuide();
    UILogic::AllInstance().append(serviceGuide);

    serviceGuideDept = new ServiceGuideDept();
    UILogic::AllInstance().append(serviceGuideDept);

    serviceGuideOther = new ServiceGuideOther();
    UILogic::AllInstance().append(serviceGuideOther);

    dutyPage = new DutyPage();
    UILogic::AllInstance().append(dutyPage);
}

void FramePage::HideSubPage()
{

    allConfigs->Hide();

    telWindow->Hide();
    serviceInfo->Hide();
    honestPage->Hide();
    dutyPage->Hide();

    UIItem("actMedia")->setVisible(false);
    UIItem("actSign")->setVisible(false);
    UIItem("actGuide")->setVisible(false);
    UIItem("actGuideDept")->setVisible(false);
    UIItem("actGuideGetByUrl")->setVisible(false);
    UIItem("actGuideXM")->setVisible(false);
    UIItem("actGuideOther")->setVisible(false);
    UIItem("actGuideOtherXM")->setVisible(false);
    UIItem("actQuestion")->setVisible(false);
    UIItem("actTelUpdate")->setVisible(false);
    UIItem("actHonest")->setVisible(false);
    UIItem("actDuty")->setVisible(false);
}

Record& FramePage::GetUserInfo()
{
    static Record userInfo;
    return userInfo;
}

void FramePage::returnClick()
{
    if(serviceGuide->GetDetailPage()->UIPage()->property("visible") == true) {
        serviceGuide->GetDetailPage()->Hide();
        serviceGuide->UIPage()->setVisible(true);
    } else if(serviceGuideOther->GetDetailPage()->UIPage()->property("visible") == true) {
        serviceGuideOther->GetDetailPage()->Hide();
        serviceGuideOther->UIPage()->setVisible(true);
    }  else {
        HideSubPage();
        serviceInfo->UIPage()->setVisible(true);
        if(CsGetConfig("显示办事指南事项")[0] == '1') {
            serviceInfo->GetservicedetailPage()->Hide();
        }
        if(CsGetConfig("按部门显示办事指南事项")[0] == '1') {
            serviceInfo->GetservicedetailPage()->Hide();
        }
    }
}

void FramePage::guideClick()
{
    HideSubPage();
    UIItem("actGuide")->setVisible(true);
    Record param;
    param["deptName"]   = (const char*)GetUserInfo()["deptName"];
    param["deptID"]     = (const char*)GetUserInfo()["deptID"];
    serviceGuide->Show(param);
}
void FramePage::guideClickByCode(QString deptName,QString deptID)
{
    HideSubPage();
    UIItem("actGuide")->setVisible(true);
    Record param;
    param["deptName"]   =  deptName;
    param["deptID"]     =  deptID;
    serviceGuide->Show(param);
}
void FramePage::guideDeptClick(QString baseUrl)
{
    HideSubPage();
    UIItem("actGuideDept")->setVisible(true);
    Record param;
    param["baseUrl"]   = baseUrl;
    serviceGuideDept->Show(param);
}
void FramePage::guideGetByUrlClick()
{
    HideSubPage();
    UIItem("actGuideGetByUrl")->setVisible(true);
    Record param;
    param["deptName"]   = (const char*)GetUserInfo()["deptName"];
    param["deptID"]     = (const char*)GetUserInfo()["deptID"];
    serviceGuideGetByUrl->Show(param);
}


void FramePage::guideOtherClick()
{
    HideSubPage();
    UIItem("actGuideOther")->setVisible(true);
    Record param;
    param["deptName"]   = (const char*)GetUserInfo()["deptName"];
    param["deptID"]     = (const char*)GetUserInfo()["deptID"];
    serviceGuideOther->Show(param);
}

void FramePage::guideXMClick()
{
    HideSubPage();
}

void FramePage::guideOtherXMClick()
{
    HideSubPage();
}

void FramePage::questionClick()
{
    HideSubPage();
    UIItem("actQuestion")->setVisible(true);
    questionPage->Show(GetUserInfo()["deptName"]);
}
void FramePage::announcementClick()
{
    HideSubPage();
}

void FramePage::telUpdateClick()
{
    HideSubPage();
    UIItem("actTelUpdate")->setVisible(true);
    telWindow->Show(GetUserInfo()["serviceID"]);
}

void FramePage::honestClick()
{
    HideSubPage();
    UIItem("actHonest")->setVisible(true);
    honestPage->Show(GetUserInfo()["userID"]);
}

void FramePage::dutyClick()
{
    HideSubPage();
    UIItem("actDuty")->setVisible(true);
    dutyPage->Show(GetUserInfo()["userID"]);
}

void FramePage::mediaClick()
{
    HideSubPage();
}

void FramePage::signClick()
{
    HideSubPage();
}

void FramePage::settClick()
{
    HideSubPage();
    Record tmp;
    allConfigs->Show(tmp);
    UIItem("actSett")->setVisible(true);
}

QString FramePage::getUserInfo(QString key)
{
    return QString(GetUserInfo()[(const char*)key.toUtf8()]);
}

void FramePage::setUserInfo(QString key, QString value) {
    GetUserInfo()[(const char*)key.toUtf8()] = (const char*)value.toUtf8().data();
}

void FramePage::Show(Record& data)
{
    const char* vdata = (const char*)(int64_t)data;
    UIItem("CenterName")->setProperty("text", QString(CsGetConfig("中心名字")));
    QString userID = GetUserID(vdata);
    if(userID.isEmpty()) return;
    QString serviceID = vdata+16;
    QString projectID = vdata+32;

    //去掉特呼标志
    serviceID.remove('T');

    GetUserInfo() = CacheInstance.GetServiceUserInfo(userID.toLocal8Bit());
    GetUserInfo()["serviceID"] = serviceID;
    GetUserInfo()["userID"] = userID;

    Record WindowPhone = CacheInstance.GetWindowPhone(userID);
    GetUserInfo()["WindowPhone"] = WindowPhone["WindowPhone"];

    if(!serviceID.isEmpty())
        IAudioRecord.Capture(serviceID);

    if(projectID.isEmpty() || projectID == "0") {
        project = "";
    } else {
        Record cmd;
        cmd["cmd"] = "ProjectName";
        cmd["idProject"] = projectID;
        Record info = CacheInstance.ServiceDoCommand(cmd.ToString());
        project = (const char*)info["ProjectName"];
    }

    GetUserInfo()["projectName"] = project.toUtf8().data();

    UIItem("updateTelGrid")->setVisible(false);
    HideSubPage();
    serviceInfo->Show(GetUserInfo());
    if(!serviceInfo->GetPersonName().isEmpty())
        UIItem("updateTelGrid")->setVisible(true);

    UILogic::Show(data);
    scrollMsg.Start(this, "scrollmsg");
}

QString FramePage::GetUserImageUrl(const QString& userID)
{
    static char* ImagePtr = NULL;
    const char* ptr = CacheInstance.GetImage(userID);
    if(ptr == NULL) return "";

    int size = *(int*)ptr;
    ptr += 4;

    delete[] ImagePtr;
    ImagePtr = new char[size];
    memcpy(ImagePtr, ptr, size);

    QString imgSource = "image://ImageStreamLoader/";
    imgSource += QString::number((qulonglong)ImagePtr);
    imgSource += '#';
    imgSource += QString::number((unsigned int)size);
    imgSource += "#";
    imgSource += userID.toUtf8();

    FramePage::GetUserInfo()["userImage"] = imgSource.toUtf8().data();

    return imgSource;
}

qint64 FramePage::getTimeDeviation()
{
    Record cmd;
    cmd["cmd"] = "TimeSync";
    Record timeS = CacheInstance.ServiceDoCommand(cmd.ToString());
    QString timeD = (const char*)timeS["NowTime"];
    QDateTime targetTime = QDateTime::fromString(timeD, "yyyy/M/dd hh:mm:ss");
    QDateTime originalTime =QDateTime::currentDateTime();
    qint64 timeDeviation = originalTime.secsTo(targetTime);
    return timeDeviation;
}

class FramePageRegist
{
public:
    FramePageRegist()
    {
        UILogic::RegInstance().append(GetInstance);
    }

    static UILogic* GetInstance()
    {
        static UILogic* instance = NULL;
        if(instance == NULL) {

          instance = new FramePage;
        }
        return instance;
    }
} registFramePage;
