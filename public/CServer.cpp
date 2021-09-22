#include "../public/CServer.h"
#include "QDebug"

CClient::CClient(QTcpSocket* s, QObject *parent) : QObject(parent), socket(s), read_bytes(0) {
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(OnDateCanRead()));
    QObject::connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                     this, SLOT(OnSocketStateChange(QAbstractSocket::SocketState)));

    socket->setParent(this);

    qDebug() << "new socket" << socket;
}

void CClient::OnSocketStateChange(QAbstractSocket::SocketState s) {
    if(s == QAbstractSocket::ClosingState) {
        qDebug() << "delete socket" << socket;
        this->deleteLater();
    }
}

void CClient::Close() {
    socket->disconnectFromHost();
}

void CClient::OnDateCanRead() {
    int rb = socket->bytesAvailable();

    if((size_t)rb + read_bytes + 1 >= sizeof buf) {
        Close();
        return;
    }

    socket->read(buf + read_bytes, rb);
    read_bytes += rb;

    buf[read_bytes] = 0;

    Logic();
}
