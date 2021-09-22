#ifndef FRAMEPAGE_H
#define FRAMEPAGE_H

#include "ScrollMessage.h"

class FramePage : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE void guideClick();
    Q_INVOKABLE void guideClickByCode(QString,QString);
    Q_INVOKABLE void guideDeptClick(QString);
    Q_INVOKABLE void guideGetByUrlClick();
    Q_INVOKABLE void guideOtherClick();
    Q_INVOKABLE void guideXMClick();
    Q_INVOKABLE void guideOtherXMClick();
    Q_INVOKABLE void mediaClick();
    Q_INVOKABLE void signClick();
    Q_INVOKABLE void settClick();
    Q_INVOKABLE void questionClick();
    Q_INVOKABLE void announcementClick();
    Q_INVOKABLE void telUpdateClick();
    Q_INVOKABLE void honestClick();
    Q_INVOKABLE void dutyClick();
    Q_INVOKABLE void returnClick();
    Q_INVOKABLE QString getUserInfo(QString);
    Q_INVOKABLE void setUserInfo(QString, QString);
    Q_INVOKABLE qint64 getTimeDeviation();

public:
    void Show(Record& vdata);
    const char* UIObjectName() { return "FramePage"; }

    //操作用户信息
    static Record& GetUserInfo();
    static QString GetUserImageUrl(const QString& userID);

    FramePage();

private:
    void HideSubPage();

protected:
    QString                 project;

    class ServiceInfo*      serviceInfo;
    class AllConfigs*       allConfigs;
    class Question*         questionPage;
    class Announcement*     announcementPage;
    class AnnouncementDetail* announcementDetail;
    class TelWindow*        telWindow;
    class ServiceGuide*     serviceGuide;
    class ServiceGuideDept*     serviceGuideDept;
    class ServiceGuideGetByUrl*     serviceGuideGetByUrl;
    class ServiceGuideOther*        serviceGuideOther;
    class ServiceGuideXM*   serviceGuideXM;
    class ServiceGuideOtherXM*serviceGuideOtherXM;
    class HonestPage*       honestPage;
    class DutyPage*         dutyPage;
    ScrollMessage           scrollMsg;
};

#endif // FRAMEPAGE_H
