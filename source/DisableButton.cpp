#include "../inc/DisableButton.h"
#include <QDateTime>

const char* DisableButton::UIObjectName()
{
    if(parent)
        return parent->UIObjectName();
    return "";
}

DisableButton::DisableButton()
    : parent(NULL), tbTime(NULL)
{
    page = NULL;
}

void DisableButton::Start(UILogic* page, const char* gridName)
{
    if(parent == NULL)
    {
        this->page = page->UIItem(gridName);
        tbTime = UIItem("tbDisableButtonTime");
        parent = page;
        QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
    }

    timer.start(1000);
}

void DisableButton::OnTimer()
{
    if(!parent->UIPage()->isVisible())
    {
        timer.stop();
        return;
    }
    QDateTime qDateTime = QDateTime::currentDateTime();
    QString str = qDateTime.toString("yyyy-MM-dd hh:mm:ss");
    tbTime->setProperty("text", str);
}

