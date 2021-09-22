#include "Cache.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QMutex>
#include <QThread>
#include <QDebug>
#include <QUrl>
#include <QDir>
#include <QByteArray>
#include <QDate>
#include <QFile>
#include <QString>
#include <QGuiApplication>
#include "Proxy.h"
#include "../inc/FramePage.h"

const int   BufferSize  = 640*1024;
const char* DB_NAME     = NULL;
const char* CONFIG_FILE = NULL;

//    配置文件目录
static const char* szConfig[] = {
    "/mnt/sdcard/dzfl/config.txt",
    "/mnt/storage/sdcard/dzfl/config.txt",
    "config.txt"
};
static const char* szDBFile[] = {
    "/mnt/sdcard/dzfl/cache.s3db",
    "/mnt/storage/sdcard/dzfl/cache.s3db",
    "cache.s3db"
};

void LocationConfigPath() {
    if(CONFIG_FILE != NULL) return;
    unsigned i = 0;
    for(; i < sizeof(szConfig) / sizeof(char*); i++) {
        if(QFile::exists(szConfig[i])) {
            DB_NAME = szDBFile[i];
            CONFIG_FILE = szConfig[i];
            break;
        }
    }

    if(CONFIG_FILE == NULL) {
        qDebug() << QDir::currentPath();
#ifdef ANDROID
        QFile config("assets:/config.txt");
#else
        QFile config("config.txt");
#endif
        if(!config.open(QFile::ReadOnly)) { qDebug() << "open file config.txt for read error"; return; }
        QFile write(szConfig[i - 1]);
        if(!write.open(QFile::WriteOnly)) { qDebug() << "open file config.txt for write error";  return; }
        QByteArray ba = config.readAll();
        write.write(ba);

        QFile db_read(":/cache.s3db");
        if(!db_read.open(QFile::ReadOnly)) { qDebug() << "open file :/cache.s3db for read error" ;   return; }
        QFile db_write(szDBFile[i - 1]);
        if(!db_write.open(QFile::WriteOnly)) return;
        ba = db_read.readAll();
        db_write.write(ba);

        DB_NAME = szDBFile[i - 1];
        CONFIG_FILE = szConfig[i - 1];
    }
    qDebug() << "确定配置文件" << CONFIG_FILE;
}

struct CommandID { enum { ServiceUserInfo = 3, SetScore, GetAcceptServiceInfo, GetProjectName }; };

class PrintBuf : public QObjectUserData {
public:
    QByteArray buf;
};
QByteArray& GetThreadBuffer(int size, int bufID = 0xF123) {
    static QMutex mutex;
    QMutexLocker lock(&mutex);
    PrintBuf* buf = (PrintBuf*)QThread::currentThread()->userData(bufID);
    if(buf == NULL)
        QThread::currentThread()->setUserData(bufID, buf = new PrintBuf);
    if(size != 0) buf->buf.resize(size);
    return buf->buf;
}

QSqlDatabase& Cache::DB() {
    return cache_db;
}
CSocket* Cache::GetSocket() {
    qDebug() << "Cache::GetSocket()" << socket;

    //如果是平板的,可以启用USB代理连接功能,做USB通信
    if(CProxy::Instance()->useProxy()) {
        return socket = CProxy::Instance();
    }

    QByteArray ip = CsGetConfig("评价服务器IP");
    QString port = CsGetConfig("评价服务器Port");
    qDebug() << "Connet" << ip << port;
    if(socket == NULL)
        socket = new CSocket((QTcpSocket*)NULL);
    *socket = new QTcpSocket;
    socket->Connect(ip, port.toInt());

    return socket;
}

Cache::Cache() : socket(NULL) {
    LocationConfigPath();

    //打开本地数据库
    qApp->addLibraryPath("./plugins");
    //QCoreApplication::addLibraryPath("./plugins");
    if(qApp != NULL)
        cache_db = QSqlDatabase::addDatabase("QSQLITE", QString("sqlite_%1").arg(qApp->applicationPid()));
    else
        cache_db = QSqlDatabase::addDatabase("QSQLITE");
    cache_db.setDatabaseName(DB_NAME);
    if(!cache_db.open()) {
        qDebug() << QString("打开本地缓存文件%1出错").arg(DB_NAME);
        exit(99);
    }
}

Cache& Cache::Instance() {
    static Cache cache;
    return cache;
}

void Cache::CloseSocket() {
    if(socket)
        *socket = (QTcpSocket*)NULL;
}
Record Cache::ServiceDoCommand(const char* json, bool onErrClose) {
    qDebug() << "ServiceDoCommand send" << json;

    Record ret = Literal::Null;
    QByteArray byteArray(json);

    int slen = byteArray.length();
    char* szBuffer = GetThreadBuffer(BufferSize).data();
    *(int*)szBuffer = slen;
    memcpy(szBuffer + 4, byteArray.data(), byteArray.length());
    szBuffer[4 + byteArray.length()] = 0;

    CSocket* socket = GetSocket();
    //写出命令
    if(!socket->Write(szBuffer, slen + 4)) {
        goto RetPoint;
    }
    //读返回长度
    if(!socket->Read((char*)&slen, 4)) {
        goto RetPoint;
    }
    //有可能命令返回内容大于2M...
    if(slen >= BufferSize) {
        qDebug() << "不允许返回大于640K的JSON数据";
        goto RetPoint;
    }
    //读返回json
    if(!socket->Read(szBuffer, slen)) {
        goto RetPoint;
    }

    szBuffer[slen] = 0;
    //返回命令运行结果UTF8
    ret.FromString(szBuffer, slen);

    //判断命令运行情况
    if(onErrClose && (int)ret["Succ"] == 0) {
        ret = Literal::Null;
        goto RetPoint;
    }

	//每次运行命令完成看一下是否有未提交的评价记录
    if(QByteArray(json).indexOf("\"SetScore\"") < 0 )
        UploadCacheScore();

RetPoint:
    //用短连接，旧版服务端可能压力比较大
    CloseSocket();

    qDebug() << "ServiceDoCommand return Size=" << ret.Size() << "Json=" << QString::fromUtf8(ret.ToString());
    return ret;
}

//评价用的数据
bool AppraiseLock = false;
char AppraiseResult[0x1000] = {0};
void Cache::SetScore(const char* json) {
    strcpy(AppraiseResult, json);

    AppraiseLock = false;

    QString strDate = QDate::currentDate().toString("yyyy-MM-dd");

    Record tmp;
    tmp.FromString(json, strlen(json));
    QString sid = (const char*)tmp["ServiceID"];
    QSqlQuery query(CacheDB);

    //检查是否已经存在缓存
    query.exec(QString("select * from scoreCache where sid='%1'").arg(sid));
    if(!query.next()) { //没有缓存，新增缓存到数据库中
        QSqlQuery(CacheDB).exec(
            QString("insert into scoreCache(sid, score, CreateDate) values('%1', '%2', '%3')").arg(sid).arg(json).arg(strDate));
    }

    tmp = ServiceDoCommand(json, false);
    if(tmp.GetType() != DataType::Literal && (int)tmp["Succ"] == 1) {
        QSqlQuery(CacheDB).exec(QString("update scoreCache set Send=1 where sid='%1'").arg(sid));
    }
}

bool  Cache::SaveConfig(const char* configName, const char* json) {
    char* szBuffer = GetThreadBuffer(BufferSize).data();
    sprintf(szBuffer, "delete from Config where key='%s'", configName);
    QSqlQuery(CacheDB).exec(szBuffer);

    QSqlQuery query(CacheDB);
    query.prepare("insert into Config(key, value) values(?, ?)");
    query.addBindValue(QString(configName));
    query.addBindValue(QByteArray(json));
    return query.exec();
}
const char* Cache::LoadConfig(const char* configName) {
    char* szBuffer = GetThreadBuffer(BufferSize).data();
    sprintf(szBuffer, "select value from Config where key='%s'", configName);
    QSqlQuery query(CacheDB);
    query.exec(szBuffer);
    if(!query.next()) return "";

    QByteArray bArray = query.value(0).toByteArray();
    memcpy(szBuffer, bArray.data(), bArray.size());
    szBuffer[bArray.size()] = 0;
    return szBuffer;
}

void Cache::UploadCacheScore() {
    QString strDate = QDate::currentDate().toString("yyyy-MM-dd");
    QSqlQuery query(CacheDB);
    query.exec(QString("select score from scoreCache where CreateDate='%1' and Send=0 limit 1").arg(strDate));
    if(!query.next()) return;

    SetScore(query.value(0).toByteArray());
}

char* Cache::GetImage(const QString& userid) {
    QSqlQuery query(CacheDB);
    query.exec(QString("select ImageData from InfoCache where ServiceUserID='%1'").arg(userid));
    if(!query.next())  return NULL;

    QByteArray bArray = query.value(0).toByteArray();
    char* szBuffer = GetThreadBuffer(qMax(BufferSize, bArray.size() + 8)).data();

    *(int*)szBuffer = bArray.size();
    memcpy(szBuffer + 4, bArray.data(), bArray.size());
    return szBuffer;
}
int Cache::GetInfoCache(const QString& uid, Record& record, bool delay) {
    //需要读配置的部分尽量推后
    static int cacheUpdate = QString(CsGetConfig("用户缓存更新间隔")).toInt();

    QSqlQuery query(CacheDB);
    query.exec(QString("select UpdateTime,Info from InfoCache where ServiceUserID='%1'").arg(uid));
    if(!query.next()) {
        return 1;
    } else if(delay) {
    } else if(QDateTime::currentMSecsSinceEpoch() / 1000 - query.value(0).toInt() > cacheUpdate){
        return 2;
    }

    QByteArray bArray = query.value(1).toByteArray();
    record.FromString(bArray.data(), bArray.size());
    return 0;
}

QString Cache::LastLoginUserID() {
    QSqlQuery query(CacheDB);
    query.exec("select ServiceUserID from InfoCache ORDER BY UpdateTime desc LIMIT 0,1");
    if(query.next()) {
        return query.value(0).toString();
    }
    return "";
}

Record Cache::GetServiceUserInfo(const QByteArray& uid) {
    Record ret;
    int cache_ret = GetInfoCache(uid, ret);
    if(cache_ret == 0) {
        return ret;
    }

    //读新数据
    Record reqCmd;
    reqCmd["cmd"] = "UserInfo";
    reqCmd["idUser"] = uid.data();
    ret = ServiceDoCommand(reqCmd.ToString());
    if(ret.GetType() == DataType::Literal) {
        GetInfoCache(uid, ret, true);
        return ret;
    }
    {
        char sql[0x1000];
        if(cache_ret == 1) {
            sprintf(sql, "insert into InfoCache(ServiceUserID, UpdateTime, Info) "
                "Values('%s', %d, ?)", uid.data(), (int)(QDateTime::currentMSecsSinceEpoch() /1000));
        }
        if(cache_ret == 2) {
            sprintf(sql, "update InfoCache set UpdateTime=%d, Info=? where ServiceUserID='%s'",
                    (int)(QDateTime::currentMSecsSinceEpoch() /1000), uid.data());
        }
        QSqlQuery query(CacheDB);
        query.prepare(sql);
        query.addBindValue(QByteArray(ret.ToString()));
        query.exec();
    }

    int   image_len = 0;
    do {
        Record record;
        record["cmd"] = "UserImage";
        record["UserID"] = uid.data();
        QByteArray cmd = record.ToString();
        int cmdlen = cmd.length();
        cmd = QByteArray(4, '\0') + cmd;
        *(int*)cmd.data() = cmdlen;
        CSocket* socket = GetSocket();

        if(!socket->Write(cmd.data(), cmd.length())) {
            CloseSocket();
            break;
        }
        if(!socket->Read((char*)&image_len, 4)) {
            CloseSocket();
            break;
        }
        if(image_len <= 0) {
            qDebug() << QString("服务器返回出错");
            break;
        }
        if(image_len > 1024*1024) {
            qDebug() << QString("相片文件大于1M,影响性能");
        }
        //不限制相片大小了
        char* image_dat = GetThreadBuffer(image_len + 8).data();
        socket->Read(image_dat, image_len);
        qDebug() << "请相片成功";

        //保存到数据库
        char sql[0x100];
        sprintf(sql, "update InfoCache set ImageData=? where ServiceUserID='%s'", uid.data());
        QSqlQuery query(CacheDB);
        query.prepare(sql);
        query.addBindValue(QByteArray(image_dat, image_len));
        query.exec();
    } while(0);

    return ret;
}
//保存签名
void Cache::insertSignName(QString imgbase64) {

    QString strDate = QDate::currentDate().toString("yyyy-MM-dd ");
    QString strTime = QTime::currentTime().toString("HH:mm:ss");

    QSqlQuery(CacheDB).exec(QString("insert into SIGNNAME(imgbase64, CREATTIME,ifsend) values('%1', '%2','0')").arg(imgbase64).arg(strDate+strTime));
    //保存签名到pddb

//    Record cmd;
//    cmd["cmd"] = "InsertSignName";
//    cmd["imgbase64"] = imgbase64;
//    QString winid =  FramePage::GetUserInfo()["WinID"].ToString();
//    cmd["WinID"]   = "G02";
//    CacheInstance.ServiceDoCommand(cmd.ToString());

}
//获取签名
QString Cache::getSignName() {
    QSqlQuery query(CacheDB);
    query.exec("select imgbase64,CREATTIME from SIGNNAME where ifsend = '0' ORDER BY CREATTIME desc LIMIT 0,1");
    if(query.next()) {
        QSqlQuery(CacheDB).exec(QString("update SIGNNAME set ifsend=1"));
        return query.value(0).toString();
    }
    return "";
}
//判断是否有签名
QString Cache::getIfHaveSignName() {
    QSqlQuery query(CacheDB);
    query.exec("select ifsend from SIGNNAME  where ifsend = '0' ORDER BY CREATTIME desc LIMIT 0,1");
    if(query.next()) {
        return "1";
    }
    return "0";
}
char* Cache::GetFileStream(const char* filename, int* len) {
    Record cmd;
    cmd["cmd"] = "GetFileStream";
    cmd["filename"] = filename;
    QByteArray ba(cmd.ToString());

    QByteArray& buffer = GetThreadBuffer(BufferSize);
    char* szBuffer = buffer.data();
    *(int*)szBuffer =  ba.size();
    memcpy(szBuffer + 4, ba.data(), ba.size());
    szBuffer[4 + ba.size()] = 0;

    CSocket* socket = GetSocket();
    socket->Write(szBuffer, ba.size() + 4);
    int recvFileSize = 0;
    socket->Read((char*)&recvFileSize, 4);

    if(recvFileSize > 200*1024*1024) {
        qDebug() << "文件大于200M，不能下载";
        return NULL;
    }

    if(recvFileSize > BufferSize) {
        buffer.resize(recvFileSize + 8);
    }
    szBuffer = buffer.data();
    if(socket->Read(szBuffer, recvFileSize)) {
        *len = recvFileSize;
        return szBuffer;
    }
    return NULL;
}

//获取员工当前所在窗口的办公电话   付志闯于2019.03.20添加
Record Cache::GetWindowPhone(const QString& UserID) {
    Record cmd;
    cmd["cmd"] = "getWindowPhone";
    cmd["UserID"] = UserID;
    Record result = ServiceDoCommand(cmd.ToString());
    return result;
}
