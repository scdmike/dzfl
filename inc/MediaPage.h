#ifndef MEDIAPAGE_H
#define MEDIAPAGE_H

#include "UILogic.h"

class MediaPage : public UILogic
{
Q_OBJECT
    Q_PROPERTY(int mIndex READ GetIndex)
public:
    Q_INVOKABLE void mediaListClick(int index);
    Q_INVOKABLE void nextPageClick();
    Q_INVOKABLE void prevPageClick();
    Q_INVOKABLE void playClick();

public:
    void            Show(Record& vdata);
    const char*     UIObjectName() { return "MediaPage"; }
    bool            Init();
    int             GetIndex();

private:
    void ShowPage(int page);
    void SelectMediaList(int index);
    void SetMediaListValue(int index, Record value);

private:
    Record                      mediaList;
    int                         totalPage;
    int                         currentPage;
    int                         selectIndex;
    QList<QQuickItem*>          uiMediaList;
};

#endif // MEDIAPAGE_H
