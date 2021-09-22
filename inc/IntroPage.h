#ifndef INTROPAGE_H
#define INTROPAGE_H

#include "ScrollMessage.h"
#include "DisableButton.h"
#include <QString>

class IntroPage : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE QString getWindowProject(QString window);

public:
    const char* UIObjectName() { return "IntroPage"; }
    void Show(Record& vdata);

private:
    ScrollMessage   scrollMsg;
    DisableButton   disableButton;
    QString         windowProject;
};

class IntroPageSq : public IntroPage {
Q_OBJECT
public:
    Q_INVOKABLE void setUserID(QString userID);
    Q_INVOKABLE void setWindowID(QString windowID);
    Q_INVOKABLE void loginOut();
    const char* UIObjectName() { return "IntroPageSq"; }
};

class IntroPageLb : public IntroPage {
Q_OBJECT
public:
    Q_INVOKABLE void showpage();
    Q_INVOKABLE void onSelect(const QString &dept);
    Q_INVOKABLE void nextPage();
    Q_INVOKABLE void prePage();
    const char* UIObjectName() { return "IntroPageLb"; }
    int GetDeptCount() { return deptsList.size(); }
    void ClearDepts() { deptsList.clear();}
    static QString& SelectDept();

private:
    int GetTotalPage();
    void SetPageData();

private:
    const static int PAGE_MAX_SIZE = 12;
    QList<QString> deptsList;
    QList<QString> usersList;
    int currentPageIndex;
};

#endif // INTROPAGE_H
