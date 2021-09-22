#include "../inc/UILogic.h"
#include <QQmlApplicationEngine>
#include <QQuickItem>

void UILogic::Show(Record&)
{
    QObjectList items = pViewer->rootObject()->children();
    for(QObjectList::Iterator i = items.begin(); i != items.end(); i++)
    {
        QQuickItem* tmp = ((QQuickItem*)*i);
        tmp->setVisible(false);
    }

    if(page)
        page->setVisible(true);
}

void UILogic::Hide()
{
    if(page)
        page->setVisible(false);
}
UILogic::UILogic(QObject* p) : QObject(p) {}
bool UILogic::Init()
{
    static QQuickItem null;
    page = pViewer->rootObject()->findChild<QQuickItem*>(UIObjectName());
    bool ret = page != NULL;

    //页不存在，使用默认页
    if(!ret) page = &null;

    return ret;
}

QQuickItem* SubItem(QQuickItem* page, const char* objectName)
{
    static QQuickItem null;
    QQuickItem* find = page->findChild<QQuickItem*>(objectName);
    if(find)
        return find;

    qDebug("SubItem() could not Find %s\n", objectName);

    return &null;
}

QQuickItem* UILogic::UIItem(const char* objectName)
{
    return SubItem(page, objectName);
}

QList<InstanceFun>& UILogic::RegInstance()
{
    static QList<InstanceFun>  regInstance;
    return regInstance;
}

QList<UILogic*>& UILogic::AllInstance()
{
    static QList<UILogic*> allInstance;
    return allInstance;
}
