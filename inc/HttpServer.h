#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QTimer>
#include "../public/CServer.h"
#include "../public/CopyData.h"
#include "../inc/UILogic.h"

//评价用的数据
extern bool AppraiseLock;
extern char AppraiseResult[0x1000];
extern void CppCommand(int id, const char* vdata);

//HTTP数据处理
class HttpClient : public CClient {
Q_OBJECT
public:
    HttpClient(QTcpSocket* s) : CClient(s) {
        QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
    }
    void Logic();

public Q_SLOTS:
    void OnTimer();

private:
    char* GetParam(const char* str, const char* key);

private:
    QTimer      timer;
};

//HTTP连接服务
class HttpServer : public QObject {
    Q_OBJECT
public:
    explicit HttpServer(QObject *parent = 0) : QObject(parent) {
        server.listen(QHostAddress::Any, 9900);
        QObject::connect(&server, SIGNAL(newConnection()), this, SLOT(OnConnect()));
     }

public Q_SLOTS:
    void OnConnect() {
        QTcpSocket* s = server.nextPendingConnection();
        if(s == NULL) return;
        if(!s->isValid()) {
            delete s;
            qDebug() << "httpserver: socket not valid" << s;
            return;
        }
        new HttpClient(s);
    }

private:
    QTcpServer          server;
};


#endif // HTTPSERVER_H
