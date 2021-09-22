#ifndef CSOCKET_H
#define CSOCKET_H

#include <QTcpSocket>

class CSocket
{
public:
    CSocket(QTcpSocket* s = NULL);
    virtual ~CSocket();

    virtual void    operator=(QTcpSocket* s);

    virtual bool    Connect(const char* ip, int port);

    virtual bool    Write(char* buf, int len);

    virtual int     ReadSome(char* buf, int len);

    virtual bool    Read(char* buf, int len);
    virtual bool    Read(char* buf, int len, qint64 timeout /*msecs*/);

protected:
    QTcpSocket*     socket;

private:
    CSocket(const CSocket&);
    void operator=(const CSocket&);

    friend class CProxy;
};

#endif // CSOCKET_H
