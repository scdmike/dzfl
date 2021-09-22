#ifndef SERVICEINFO_H
#define SERVICEINFO_H

#include <QTimer>
#include "UILogic.h"
#include "ScrollMessage.h"

class ServiceInfo : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE void loadSecondUser();
    Q_INVOKABLE void projectPageUp();
    Q_INVOKABLE void projectPageDown();
    Q_INVOKABLE void projectPageAlwaysDown();
    Q_INVOKABLE void resumeScroll();
    Q_INVOKABLE void resumeScroll2(QString UserID,QString ServiceID);
    Q_INVOKABLE void stopTimer();
    Q_INVOKABLE void approvalClick(int index);
    Q_INVOKABLE void showAppraise();

public slots:
    void OnTimer();

public:
    ServiceInfo();
    void Show(Record& vdata);
    const char* UIObjectName() { return "ServiceInfo"; }
    const QString& GetPersonName() const { return personName; }
    UILogic* GetservicedetailPage() { return servicedetailPage; }

private:
    void LoadUserImage(const char* image, const char* userID);
    void UpdateGovFlag(const QString& gov, int umUserIndex/*联合窗口工作人员编号0,1*/ = 0);
    void UpdateWinFlag(const QString& winHonor);
    void UpdateServiceStar(const QString& userID, int umUserIndex/*联合窗口工作人员编号0,1*/ = 0);
    void UpdateUserProject(QString project);
    void UpdateServiceMessage();
    void LoadScrollText(ScrollMessage* box, const char* boxName, const char* field);
    void SetScrollProjectPage(int page);
    void CheckModifyPage();
    void GetProjectList(QString project);
    QString GetUserProjectGz(const QString& userid);

    void HideItem();

private:
    QString                 serviceID;
    QString                 personName;
    QStringList             projectNameList;
    QStringList             idList;
    int                     projectNameListPageCount;
    int                     projectNameListCurPage;
    QList<ScrollMessage*>   scProjectNameList;
    ScrollMessage           scWinProject[3];
    ScrollMessage           scUserProject[3];
    ScrollMessage           scProjectName;
    QTimer                  timer;
    UILogic*                servicedetailPage;
};

#endif // SERVICEINFO_H
