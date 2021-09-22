#include <QByteArray>
#include <QTcpSocket>
#include "ServiceConnect.h"
#include "Setting.h"

void IRpc::SendCommand(const Record &cmd) {
    szData = cmd.ToString();

    ServiceConnect::IConnect().Send(this);
}

void IRpc::RecvResult(Record& json) {
    emit result(json.ToString());
}

ServiceConnect& ServiceConnect::IConnect() {
    static ServiceConnect connect;
    return connect;
}

ServiceConnect::ServiceConnect() {
    //启动回调定时器
    connect(&timer, &QTimer::timeout, this, &ServiceConnect::OnTimer);
    timer.start(100);

    //启动线程
    start();
}

void ServiceConnect::Send(IRpc *task) {
    QMutexLocker lock(&sendMutex);
    sendQueue.append(task);
}

int GetHttpContentLength(const QByteArray& httpData, int httpHeadLen) {
    QByteArray head = httpData.left(httpHeadLen).toUpper();
    int lenOff = head.indexOf("CONTENT-LENGTH:");
    if(lenOff < 0) return 0;
    lenOff += strlen("CONTENT-LENGTH:");
    QByteArray lenByte = head.mid(lenOff, head.indexOf('\n', lenOff) - lenOff);
    if(lenByte[lenByte.length() - 1] == '\r') lenByte.remove(lenByte.length() - 1, 1);
    return lenByte.toInt();
}

QByteArray HttpPost(const QString& host, int port, const QString& url, const QByteArray& postData) {
    QByteArray result;
    do {
        //空数据不发请求了
        if(postData.isEmpty()) break;

        QTcpSocket socket;
        socket.connectToHost(host, port);
        if(!socket.waitForConnected(10000)) break;

        QString req =   "POST " + url + " HTTP/1.0\r\n"
                        "Content-Type: text/plain;charset=UTF-8\r\n"
                        "Content-Length: %1\r\n"
                        "Accept: */*\r\n\r\n";
        QByteArray send = req.arg(postData.size()).toUtf8() + postData;

        //发送命令
        if(socket.write(send) <= 0) break;
        if(!socket.waitForBytesWritten(3000)) break;

        //重试三次读回返头
        int index = 0;
        for(int i = 0; i < 3; i++) {
            if(socket.bytesAvailable() <= 0)
                socket.waitForReadyRead(3000);
            result += socket.readAll();
            index = result.indexOf("\n\n");
            if(index > 0) { index += 2; break; }
            index = result.indexOf("\r\n\r\n");
            if(index > 0) { index += 4; break; }
        }
        if(index <= 0 || index > 0x40000) break;

        int size = GetHttpContentLength(result, index);
        int reTryCount = 0;
        while(result.length() < size + index) {
            if(socket.bytesAvailable() <= 0)
                socket.waitForReadyRead(3000);

            result += socket.readAll();
            if(reTryCount++ > 10) break;
        }
        result = result.mid(index);

        //断开连接
        socket.waitForDisconnected(1000);
        socket.disconnectFromHost();

    } while(0);

    return result;
}

void ServiceConnect::run() {
    while(true)
    {
        DataQueue tmp;
        {
            QMutexLocker lock(&sendMutex);
            if(sendQueue.size() > 0)
                tmp.swap(sendQueue);
        }

        if(tmp.size() == 0)
            QThread::msleep(200);

        for(DataQueue::iterator it = tmp.begin(); it != tmp.end(); ++it)
        {
            IRpc* p = *it;
            QByteArray json;
            json.swap(p->szData);

            qDebug() << "请求：" << json << endl;
            if(!json.contains("Service")) {
                qDebug() << "异常请求：" << json << endl;
                continue;
            }
            QByteArray result = HttpPost(Setting.serviceIPValue(),
                Setting.servicePortValue(), "/ServiceEntry.aspx", json);

            if(!result.isEmpty()) p->szData.swap(result);

            qDebug() << "返回：" << p->szData << endl;

            {
                QMutexLocker rLock(&recvMutex);
                recvQueue.append(p);
            }
        }
    }
}

void ServiceConnect::OnTimer() {
    DataQueue tmp;
    {
        QMutexLocker lock(&recvMutex);
        if(recvQueue.size() > 0)
            tmp.swap(recvQueue);
    }

    for(DataQueue::iterator it = tmp.begin(); it != tmp.end(); ++it) {
        IRpc* p = *it;
        if(p) {
            Record result;
            result.FromString(p->szData.data(), p->szData.size());
            p->RecvResult(result);
        }
    }
}
