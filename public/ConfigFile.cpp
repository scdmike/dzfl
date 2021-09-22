#include <QFile>
#include <QDebug>
#include <QMutex>
#include "Cache.h"

static Record clientConfig;
static Record serverConfig;
static bool   serverRecv = false;
void LocationConfigPath();
//utf-8
const char* CsGetConfig(const char* key) {
    if(key == NULL || key[0] == 0) return "";
    LocationConfigPath();

    if(clientConfig.Size() == 0)
    {
        QFile file(CONFIG_FILE);
        if(file.open(QIODevice::ReadOnly)) {
            QByteArray data = file.readAll();
            file.close();
            int sindex = data.indexOf('{');
            if(sindex > 0) {
                data = data.mid(sindex);
            } else if(sindex < 0) {
                data = "{}";
            }
            qDebug() << data;
            clientConfig.FromString(data, data.length());
            qDebug() << clientConfig.ToString();
        } else {
            qDebug() << QString("打开配置文件%1失败").arg(CONFIG_FILE);
            exit(100);
        }
    }
    if(clientConfig.Exists(key)) {
        const char* value = clientConfig[key];
        qDebug() << "CsGetConfig" << key << value;
        return value;
    }

    if(!serverRecv || serverConfig.Size() == 0) {
        FlashConfig();
    }

    if(serverConfig.Exists(key)) {
        return serverConfig[key];
    } else {
        qDebug() << key << serverConfig.ToString();
    }

    return "";
}

#include <QMutex>
void FlashConfig() {

}

void CsSetRuntimeConfig(const QString& key, const QString& value) {
    clientConfig[key.toUtf8().constData()] = value.toUtf8().constData();
}

const char* GetUserID(const char* userid)
{
    static QByteArray userID;

    if(userid && strlen(userid) > 0) {
        userID = userid;
    }

    if(userID == "未登录")
        userID = "";

    if(userID.isEmpty() && CsGetConfig("窗口工号")[0] != '\0') {
        userID = CsGetConfig("窗口工号");
    }

    //如果没有传用户ID，则从登录窗口取得用户ID
    return userID;
}
