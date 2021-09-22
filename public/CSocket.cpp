#include "CSocket.h"
#include <QDateTime>

bool CSocket::Write(char* buf, int len)
{
    if(this == NULL || socket == NULL)
        return false;

    int writeed = 0;

    while(writeed < len)
    {
        int write = socket->write(buf + writeed, len - writeed);
        if(write < 0)
        {
            socket->close();
            return false;
        }
        if(write > 0) {
            if(!socket->waitForBytesWritten(CONNECT_TIME_OUT)) return false;
        }
        writeed += write;
    }
    return true;
}

void CSocket::operator=(QTcpSocket* s)
{
    qDebug() << "CSocket::operator=";
    if(socket) {
        if(socket->bytesToWrite() > 0 && socket->isWritable())
            socket->waitForBytesWritten(CONNECT_TIME_OUT);
        qDebug() << "断开连接";
        socket->disconnectFromHost();
        socket->disconnect();
        socket->close();
        socket->deleteLater();
    }
    socket = s;
}

bool CSocket::Connect(const char* ip, int port)
{
    if(socket == NULL)
        socket = new QTcpSocket;
    socket->connectToHost(ip, port);
    return socket->waitForConnected(CONNECT_TIME_OUT);
}

int CSocket::ReadSome(char* buf, int len)
{
    if(socket == NULL || !socket->isValid())
        return -1;
    if(socket->bytesAvailable() <= 0 && !socket->waitForReadyRead())
        return 0;
    qint64 read = socket->read(buf, len);
    return read;
}

bool CSocket::Read(char* buf, int len)
{
    if(socket == NULL)
        return false;

    int reTry = 0;
    int readed = 0;
    while(readed < len)
    {
        if(!socket->isValid())
            return false;

        if(socket->bytesAvailable() <= 0 && !socket->waitForReadyRead(CONNECT_TIME_OUT)) {
            if(reTry++ > 10)
                return false;
            else
                continue;
        }

        int read = socket->read(buf + readed, len - readed);
        if(read < 0)
        {
            socket->close();
            return false;
        }
        readed += read;
    }
    return true;
}

bool CSocket::Read(char* buf, int len, qint64 timeout)
{
    if(socket == NULL)
        return false;

    int readed = 0;
    while(readed < len)
    {
        if(!socket->isValid() || !socket->isReadable())
            return false;

        //没有数据的话,等待
        if(socket->bytesAvailable() <= 0 && !socket->waitForReadyRead(timeout))
            return false;

        int read = socket->read(buf + readed, len - readed);
        if(read < 0)
        {
            socket->close();
            return false;
        }
        readed += read;
    }
    return true;
}

CSocket::CSocket(QTcpSocket* s) : socket(s) {}

CSocket::~CSocket() { *this = (QTcpSocket*)NULL; }

