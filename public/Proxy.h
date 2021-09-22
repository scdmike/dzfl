#ifndef PROXY_H
#define PROXY_H

#include <QTcpServer>
#include "CSocket.h"

#ifndef ANDROID
class CProxy : public CSocket
{
public:
    bool            useProxy() { return false; }
    void            SetProxySocket(CSocket&) {}
public:
    static CProxy*  Instance() { static CProxy proxy; return &proxy; }
};
#else
class CProxy : public CSocket
{
public:
    bool            useProxy();
    void            SetProxySocket(CSocket&);

    virtual void    operator=(QTcpSocket* s);
    virtual bool    Write(char* buf, int len);
    virtual int     ReadSome(char* buf, int len);
    virtual bool    Read(char* buf, int len);
    virtual bool    Read(char* buf, int len, qint64 timeout /*msecs*/);

public:
    static CProxy*  Instance();

protected:
    void            CloseOldSocket(QTcpSocket* s);
private:
    CProxy();
    bool            bProxy;
};
#endif

#endif // PROXY_H
