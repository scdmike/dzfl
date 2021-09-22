#ifndef CONSOLEMESSAGEBOX_H
#define CONSOLEMESSAGEBOX_H

#include <QString>
#include <QMutex>
#include <QList>
#include "../public/CSocket.h"

class ConsoleMessageBox {
public:
    static ConsoleMessageBox& Instance() {
        static ConsoleMessageBox consoleMsg;
        return consoleMsg;
    }

    void AddMessage(const QString& msg) {
        QMutexLocker lock(&mutex);
        msgQueue.push_back(msg);
    }

    void Send(CSocket& socket) {
        QString msg;
        {
            QMutexLocker lock(&mutex);
            if(!msgQueue.isEmpty()) {
                msg = msgQueue.first();
                msgQueue.removeFirst();
            }
        }
        if(!msg.isEmpty()) {
            QByteArray array = msg.toUtf8();
            int bufLen = array.length() + sizeof(int) * 2;
            if(bufLen < 0x400) {
                int mType = 'M';
                char buf[0x400];
                *(int*)buf = mType;
                *(int*)(buf + sizeof(int)) = array.length();
                memcpy(buf + sizeof(int) * 2, array.constData(), array.length());
                socket.Write(buf, bufLen);
            }
        }
    }

private:
    ConsoleMessageBox() {}

private:
    QMutex          mutex;
    QList<QString>  msgQueue;
};

#endif // CONSOLEMESSAGEBOX_H
