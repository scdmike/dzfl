#include "../inc/IntroPage.h"
#include "../public/Cache.h"
#include "../inc/CommandBuffer.h"


//
void IntroPage::Show(Record& vdata)
{
    UIItem("CenterName")->setProperty("text", QString(CsGetConfig("中心名字")));
    UILogic::Show(vdata);
    disableButton.Start(this, "disableButton");
}

QString IntroPage::getWindowProject(QString window)
{
    if(windowProject.isEmpty()) {
        Record cmd;
        cmd["cmd"] = "GetWindowProject";
        QByteArray ba = window.toUtf8();
        cmd["window"] = ba.data();
        Record value = CacheInstance.ServiceDoCommand(cmd.ToString());
        windowProject = QString(value["Project"]).replace("<R><N>", "\n");
    }
    return windowProject;
}

void  IntroPageSq::setUserID(QString userID) {
    CsSetRuntimeConfig("窗口工号", userID);
    char vdata[100] = {0};
    CmdBufInstance->ShowPage("FramePage", vdata);
}

void  IntroPageSq::setWindowID(QString windowID) {
    CsSetRuntimeConfig("WindowID", windowID);
}

void  IntroPageSq::loginOut() {
    CsSetRuntimeConfig("窗口工号", "");
    GetUserID("未登录");
    CmdBufInstance->ShowPage("IntroPageSq", "");
}


static QString selectDept;
static QString selectUserID;
void IntroPageLb::showpage() {
    CsSetRuntimeConfig("窗口工号", "");
    GetUserID("未登录");
    CmdBufInstance->ShowPage("IntroPageLb", "");
    Record cmd;
    cmd["cmd"] = "Queue.GetBizDepts";
    cmd["CmdToQueue"] = 1;
    Record result = CacheInstance.ServiceDoCommand(cmd.ToString());
    Record resultdepts = result["depts"];
    deptsList.clear();
    selectDept.clear();
    for(uint i = 0; i < resultdepts.Size(); i++) {
        if((int)resultdepts[i]["Enable"] == 1) {
            deptsList.append((const char*)resultdepts[i]["DeptName"]);
        }
    }
    qDebug() << deptsList;
    currentPageIndex = 1;

    int start = (currentPageIndex - 1) * PAGE_MAX_SIZE;
    if(start < 0) return;

    int end = qMin(currentPageIndex * PAGE_MAX_SIZE, deptsList.size());
    QStringList pageList;
    for(int i = start; i < end; ++i)
    {
        pageList.append(deptsList[i]);
    }

    UIItem("dept_grid_Repeater")->setProperty("model", QVariant::fromValue(pageList));
    UIItem("usertxt")->setProperty("visible", false);
    UIItem("depttxt")->setProperty("visible", true);
}

void IntroPageLb::onSelect(const QString &dept) {
    if(selectDept.isEmpty()) {
        selectDept = dept;
        Record cmd;
        cmd["cmd"]        = "Queue.ListPerson";
        cmd["DeptName"]   = selectDept;
        cmd["CmdToQueue"] = 1;
        Record result = CacheInstance.ServiceDoCommand(cmd.ToString());
        Record resultUsers = result["Users"];
        usersList.clear();
        for(uint i = 0; i < resultUsers.Size(); i++) {
            QString users = QString("%1|%2").arg((const char*)resultUsers[i]["UserName"]).arg((const char*)resultUsers[i]["UserID"]);
            usersList.append(users);
        }
        qDebug() << usersList;

        currentPageIndex = 1;
        int start = (currentPageIndex - 1) * PAGE_MAX_SIZE;
        if(start < 0) return;

        int end = qMin(currentPageIndex * PAGE_MAX_SIZE, usersList.size());
        QStringList pageList;
        for(int i = start; i < end; ++i)
        {
            pageList.append(usersList[i]);
        }

        UIItem("dept_grid_Repeater")->setProperty("model", QVariant::fromValue(pageList));
        UIItem("usertxt")->setProperty("visible", true);
        UIItem("depttxt")->setProperty("visible", false);
        UIItem("returnDept")->setProperty("visible", true);

        deptsList.swap(usersList);
    } else {
        selectUserID = dept.split("|")[1];
        CsSetRuntimeConfig("窗口工号", selectUserID);
        char vdata[100] = {0};
        CmdBufInstance->ShowPage("FramePage", vdata);
    }
}

void IntroPageLb::nextPage() {
    if (currentPageIndex + 1 <= GetTotalPage())
    {
        qDebug() << "currentPageIndex:" << currentPageIndex;
        ++currentPageIndex;
        SetPageData();
    }
}

void IntroPageLb::prePage() {
    if (currentPageIndex - 1 > 0)
    {
        --currentPageIndex;
        qDebug() << "currentPageIndex:" << currentPageIndex;
        SetPageData();
    }
}

int IntroPageLb::GetTotalPage() {
    return (deptsList.size() % PAGE_MAX_SIZE > 0) ? (deptsList.size() / PAGE_MAX_SIZE + 1) : (deptsList.size() / PAGE_MAX_SIZE);
}

void IntroPageLb::SetPageData() {
    int start = (currentPageIndex - 1) * PAGE_MAX_SIZE;
    if(start < 0) return;

    int end = qMin(currentPageIndex * PAGE_MAX_SIZE, deptsList.size());
    QStringList pageList;
    for(int i = start; i < end; ++i)
    {
        pageList.append(deptsList[i]);
    }
    UIItem("dept_grid_Repeater")->setProperty("model", QVariant::fromValue(pageList));
}

QString& IntroPageLb::SelectDept() {
    return selectDept;
}

class IntroPageRegist
{
public:
    IntroPageRegist()
    {
        UILogic::RegInstance().append(GetInstance);
    }
    static UILogic* GetInstance()
    {
        static UILogic* instance = NULL;
        if(instance == NULL) {
            instance = new IntroPage;
        }
        return instance;
    }
} registIntroPage;

