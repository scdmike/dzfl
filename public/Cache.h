#pragma once

#include "public/Record.h"
#include "CSocket.h"
#include <QSqlDatabase>


class Cache {
public:
    Record              ServiceDoCommand(const char* json, bool onErrClose = true);
    Record              GetServiceUserInfo(const QByteArray& uid);
    void                SetScore(const char* json);
    void				UploadCacheScore();
    void                insertSignName(QString imgbase64);
    QString             getSignName();
    QString             getIfHaveSignName();
    bool                SaveConfig(const char* configName, const char* json);
    const char*         LoadConfig(const char* configName);
    char*               GetImage(const QString& userid);
    char*               GetFileStream(const char* filename, int* len);
    QString             LastLoginUserID();
    Record              GetWindowPhone(const QString& UserID);
    static Cache&       Instance();
private:
    QSqlDatabase&       DB();
    CSocket*            GetSocket();
    void                CloseSocket();
    int                 GetInfoCache(const QString& uid, Record& record, bool delay = false);
private:
    Cache();
    QSqlDatabase        cache_db;
    CSocket*            socket;
};

#define CacheInstance Cache::Instance()
#define CacheDB CacheInstance.DB()

//取配置内容，先本地后服务端
void   FlashConfig();
extern const char* CONFIG_FILE;
const  char* CsGetConfig(const char* key);
const  char* GetUserID(const char* userid);
void   CsSetRuntimeConfig(const QString& key, const QString& value) ;

#ifdef ANDROID
#include <unistd.h>
#define mySleep(n) usleep(n*1000)
#else
#include <Windows.h>
#define mySleep(n) Sleep(n)
#endif

