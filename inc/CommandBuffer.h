#ifndef COMMANDBUFFER_H
#define COMMANDBUFFER_H

#include <QtCore>
#include <QMutex>
#include "../public/CopyData.h"
struct Command {
    int     id;
    char    vdata[10000];
};

class CommandBuffer : public QObject {
Q_OBJECT
public:
    void AddCommand(int id, const char* vdata);
    bool IsPageVisible(const QString& page);
    bool ClosePage(const QString& page);
    bool IsEmpay();
    void ShowPage(const QString& pageName, const char* vdata);
    static CommandBuffer* Instance();


public slots:
    void DoCommand();

private:
    CommandBuffer() {}

private:
    QList<Command>  buffer;
    QMutex          mutex;

};

#define CmdBufInstance CommandBuffer::Instance()

#endif // COMMANDBUFFER_H
