#ifndef SERVICECONNECT_H
#define SERVICECONNECT_H

#include <QTimer>
#include <QThread>
#include <QMutex>

#include "public/General.h"

typedef QList<IRpc*> DataQueue;

class ServiceConnect : public QThread
{
Q_OBJECT
public:
    static ServiceConnect&      IConnect();
    void                        Send(IRpc* task);

public Q_SLOTS:
    void                        OnTimer();

protected:
    ServiceConnect();
    void                        run();

private:
    QTimer                      timer;

    QMutex                      sendMutex;
    DataQueue                   sendQueue;

    QMutex                      recvMutex;
    DataQueue                   recvQueue;
};

#endif // SERVICECONNECT_H
