#ifndef TEST_H
#define TEST_H

#include <QQuickItem>
#include <QQuickView>
#include "../public/Cache.h"


typedef class UILogic* (*InstanceFun)();

class UILogic : public QObject
{
Q_OBJECT
public:
    virtual void Hide();
    virtual bool Init();
    UILogic(QObject* parent = NULL);
    virtual void Show(Record& vdata);
    virtual const char* UIObjectName() = 0;
    QQuickItem*& UIPage() { return page; }
    QQuickItem*  UIItem(const char* objectName);

    static QList<UILogic*>&     AllInstance();

    //初始化时的接口要用这个函数注册
    static QList<InstanceFun>&  RegInstance();

protected:
    QQuickItem*   page;
};

extern class QQuickView* pViewer;
QQuickItem* SubItem(QQuickItem* page, const char* objectName);

#endif // TEST_H
