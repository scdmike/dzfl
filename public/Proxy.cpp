#include "Proxy.h"
#include <QGuiApplication>
#include <QMutex>
#include <QThread>

static QMutex mutex;
CProxy::CProxy() : CSocket(NULL), bProxy(false) {
}

CProxy* CProxy::Instance() {
    QMutexLocker lock(&mutex);
    static CProxy proxy;
    return &proxy;
}

bool CProxy::useProxy() {
    return bProxy;
}

void CProxy::SetProxySocket(CSocket& s) {
    bProxy = true;

    qDebug() << "usb proxy shake hands";
    QMutexLocker lock(&mutex);
    if(socket == NULL) {
        int r = 1;
        s.Write((char*)&r, sizeof(r));

        socket = s.socket;
        s.socket = NULL;

        qDebug() << "usb proxy connected";
    } else {
        int r = 0;
        s.Write((char*)&r, sizeof(r));
        qDebug() << "usb proxy close";
    }
}

void CProxy::operator=(QTcpSocket* s) {

}

void CProxy::CloseOldSocket(QTcpSocket* s) {
    if(socket) {
        socket->disconnectFromHost();
        socket->close();
        socket->deleteLater();
    }
    socket = s;
    qDebug() << "关闭代理连接" << socket;
}

bool CProxy::Write(char* buf, int len) {
    for(int i = 0; i < 8; i++) {
        {
            QMutexLocker lock(&mutex);
            if(socket) {
                bool r = CSocket::Write(buf, len);
                qDebug() << "代理写入数据" << len << r;
                if(!r) CloseOldSocket(NULL);
                return r;
            }
        }
        QThread::msleep(1000);
    }
    CloseOldSocket(NULL);
    return false;
}

int CProxy::ReadSome(char* buf, int len) {
    for(int i = 0; i < 5; i++) {
        {
            QMutexLocker lock(&mutex);
            if(socket) {
                int r = CSocket::ReadSome(buf, len);
                if(r <= 0)
                    CloseOldSocket(NULL);
                else
                    return r;
            }
        }
        QThread::msleep(1000);
    }
    CloseOldSocket(NULL);
    return 0;
}

bool CProxy::Read(char* buf, int len) {
    for(int i = 0; i < 5; i++) {
        {
            QMutexLocker lock(&mutex);
            if(socket) {
                bool r = CSocket::Read(buf, len);
                if(!r)
                    CloseOldSocket(NULL);
                else
                    return r;
            }
        }
        QThread::msleep(1000);
    }
    CloseOldSocket(NULL);
    return false;
}

bool CProxy::Read(char* buf, int len, qint64 timeout /*msecs*/) {
    for(int i = 0; i < 5; i++) {
        {
            QMutexLocker lock(&mutex);
            if(socket) {
                bool r = CSocket::Read(buf, len, timeout);
                if(r) return r;
            }
        }
        QThread::msleep(1000);
    }
    CloseOldSocket(NULL);
    return false;
}


