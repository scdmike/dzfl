#include <QImage>
#include <QGuiApplication>
#include "../public/Proxy.h"
#include "../public/CopyData.h"
#include "../inc/CommandBuffer.h"
#include "../inc/TcpReadCommand.h"
#include "../inc/ConsoleMessageBox.h"

extern void CppCommand(int id, const char* vdata);

TcpReadCommand::TcpReadCommand(qintptr handle) : socketID(handle) {
    QObject::connect(this, &QThread::finished, this, &QThread::deleteLater);
}

int TcpReadCommand::CheckPageVisible(const QString& pages) {
    if(!CmdBufInstance->IsEmpay())
        return 1;
    QStringList pageList = pages.split('|', QString::SkipEmptyParts);
    for(int i = 0; i < pageList.size(); i++) {
        if(!pageList[i].isEmpty() && CmdBufInstance->IsPageVisible(pageList[i]))
            return 2;
    }

    return 0;
}

int SCREEN_CAPTURE_RESULT = 1;
void TcpReadCommand::run() {
    //当前线程上连接
    QTcpSocket* tmp = new QTcpSocket;
    tmp->setSocketDescriptor(socketID);
    CSocket socket(tmp);
    bool onceCommand = true;
    qDebug() << "tcp command socket begin";

    while(!QGuiApplication::closingDown()) {
        int len;
        char data[0x100];
        char vdata[100] = {0};
        CopyData_Generic* Generic = (CopyData_Generic*)data;

        if(!socket.Read((char*)&len, 4)) goto SOCKET_ERROR;
        if(!socket.Read(data, len)) goto SOCKET_ERROR;

        int result = 1;
        switch(Generic->cmd) {
        case CommandID::USER_INFO: {
                CopyData_UserInfo* UserInfo = (CopyData_UserInfo*)Generic;
                memcpy(vdata, UserInfo->data, sizeof(vdata));
            }
            break;

        }
        CppCommand(Generic->cmd, vdata);

    SKIP_COMMAND:
        //加上返回数据,保证运行到这一步时发送端可以知道
        if(!socket.Write((char*)&result, sizeof(result))) goto SOCKET_ERROR;
        if(onceCommand) break;
    }

SOCKET_ERROR:
    qDebug() << "tcp command socket end";

    this->exit();
}

void TcpServer::incomingConnection(qintptr handle) {
    TcpReadCommand* read = new TcpReadCommand(handle);
    read->start();
}

void TcpServer::Run() {
    listen(QHostAddress::Any, 9901);
}


