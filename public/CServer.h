#ifndef CSERVER_H
#define CSERVER_H

#include <QTcpSocket>
#include <QTcpServer>

class CClient : public QObject {
Q_OBJECT

public:
    explicit CClient(QTcpSocket* s, QObject *parent = 0);
    virtual void        Logic() = 0;

    void Close();

public Q_SLOTS:
    void OnDateCanRead();
    void OnSocketStateChange(QAbstractSocket::SocketState);

protected:
    QTcpSocket*         socket;
    int                 read_bytes;
    char                buf[0x2000];
};

#endif // CSERVER_H
