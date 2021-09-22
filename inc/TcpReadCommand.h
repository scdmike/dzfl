#ifndef TCPREADCOMMAND_H
#define TCPREADCOMMAND_H

#include <QThread>
#include <QTcpServer>
#include "../public/CSocket.h"

class TcpReadCommand : public QThread {
Q_OBJECT
public:
    TcpReadCommand(qintptr handle);

protected:
    void        run();
private:
    int         CheckPageVisible(const QString& page);
private:
    qintptr     socketID;
};

class TcpServer : public QTcpServer {
Q_OBJECT
public:
    void        Run();

protected:
    void        incomingConnection(qintptr handle);
};

#endif // TCPREADCOMMAND_H
