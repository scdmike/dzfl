#include <QQuickView>
#include "../inc/CommandBuffer.h"
#include "../inc/UILogic.h"
#include <QSound>
#include "../inc/AllConfigs.h"


void CommandBuffer::AddCommand(int id, const char* vdata)
{
    Command cmd;
    cmd.id = id;
    int sendSize=1000;//从100改成1000，
    memcpy(cmd.vdata, vdata, sendSize);
    QMutexLocker lock(&mutex);
    buffer.push_back(cmd);
}
CommandBuffer* CommandBuffer::Instance()
{
    static CommandBuffer instance;
    return &instance;
}

void CommandBuffer::ShowPage(const QString& pageName, const char* vdata)
{
    QMutexLocker lock(&mutex);

    for(QList<UILogic*>::Iterator it = UILogic::AllInstance().begin();
        it != UILogic::AllInstance().end(); ++it)
    {
        UILogic* tmp = *it;
        if(pageName == tmp->UIObjectName())
        {
            qDebug()<<"pageName"<<pageName;
            Record r = (int64_t)vdata;
            tmp->Show(r);
        }
    }
}

bool CommandBuffer::IsPageVisible(const QString& page)
{
    QMutexLocker lock(&mutex);
    for(QList<UILogic*>::Iterator it = UILogic::AllInstance().begin();
        it != UILogic::AllInstance().end(); ++it)
    {
        UILogic* tmp = *it;
        const char* name = tmp->UIObjectName();
        if(tmp && tmp->UIPage() && tmp->UIPage()->isVisible() && page == name)
            return true;
    }
    return false;
}

bool CommandBuffer::IsEmpay()
{
    QMutexLocker lock(&mutex);
    return buffer.size() == 0;
}

bool CommandBuffer::ClosePage(const QString& page)
{
    for(QList<UILogic*>::Iterator it = UILogic::AllInstance().begin();
        it != UILogic::AllInstance().end(); ++it)
    {
        UILogic* tmp = *it;
        const char* name = tmp->UIObjectName();
        if(page == name) {
            tmp->Hide();
            return true;
        }
    }
    return false;
}

void ConvertGBKToUTF8(char* str) {
    bool isGBK = false;
    for(int i = 0; i < 1000 && str[i] != '\0'; i++) {
        if(((uint8_t*)str)[i] >= 128) { isGBK = true; break; }
    }
    if(isGBK) {
        QString convStr = QString::fromLocal8Bit(str);
        strcpy(str, convStr.toUtf8().constData());
    }
}
void CommandBuffer::DoCommand()
{

    Command  cmd;

    {
        QMutexLocker lock(&mutex);
        if(buffer.size() == 0) return;
        cmd = buffer[0];
    }

    switch (cmd.id)
    {
    case CommandID::USER_INFO:
        ConvertGBKToUTF8(cmd.vdata);
        ConvertGBKToUTF8(cmd.vdata + 16);
        ConvertGBKToUTF8(cmd.vdata + 32);
        ShowPage("FramePage", cmd.vdata);
        break;
    case CommandID::INTRODUCE:
        ShowPage("IntroPage", cmd.vdata);
        break;
    }

    { QMutexLocker lock(&mutex); buffer.removeAt(0); }
}
