#ifndef QUESTION_H
#define QUESTION_H

#include "UILogic.h"

class Question : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE void nextPageClick();
    Q_INVOKABLE void prevPageClick();
    Q_INVOKABLE void dragMove(int x, int y);
    Q_INVOKABLE void questionListClick(int index);

public:
    void Show(Record& vdata);
    const char* UIObjectName() { return "QuestionPage"; }
    bool Init();

private:
    void ShowPage(int page);
    void SelectQuestionList(int index);
    void SetQuestionListValue(int index, Record value);

private:
    Record                      questionList;
    int                         totalPage;
    int                         currentPage;
    int                         selectIndex;
    QList<QQuickItem*>    uiQuestionList;
};

#endif // QUESTION_H
