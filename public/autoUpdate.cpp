#include <QDir>
#include <QProcess>
#include <QQuickView>
#include <QQuickItem>
#include <QQuickWindow>
#include <QCryptographicHash>
#include "autoUpdate.h"
#include "QDebug"
#include "../public/Cache.h"

AutoUpdate::AutoUpdate() {
    QObject::connect(&manager, &QNetworkAccessManager::finished, this, &AutoUpdate::UpdateFileResult);
    GetFileInfo();
}

void AutoUpdate::GetFileInfo()
{
    Record cmd;
    cmd["cmd"]  = "GetFilesHash";
    cmd["Path"] = CsGetConfig("更新目录");
    cmd["Type"] = "PJ";
    Record result = CacheInstance.ServiceDoCommand(cmd.ToString());
    qDebug() << "result: " << result.ToString();

    Record files = result["files"];
    updatepath = (const char*)result["Path"];

    Record needUpdate;
    fileList.Clear();
    currentFile = "";

    Q_FOREACH(const QByteArray& cFile, files.keys())
    {
        QFile fFile(cFile);

        if(fFile.exists()) {
            fFile.open(QIODevice::ReadOnly);
            QByteArray localHash = QCryptographicHash::hash(fFile.readAll(),QCryptographicHash::Md5).toHex().constData();
            QByteArray getHash = (const char*)files[cFile]["hash"];
            if(localHash != getHash) {
                needUpdate[cFile] = files[cFile];
            }
        } else{
            needUpdate[cFile] = files[cFile];
        }
    }
    fileList = needUpdate;

    //看看有没有需要更新的文件，如果更新文件数为0，不需要更新
    if(fileList.Size() > 0)
        GetFiles();
}

void AutoUpdate::UpdateFileResult(QNetworkReply *reply){
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << currentFile << "下载文件失败";
    } else {
        QFile f("tmpPj/" + currentFile);
        if(f.open(QIODevice::WriteOnly)) {
            f.write(reply->readAll());
            f.close();
            //下载剩下的文件
            fileList[currentFile.toUtf8().constData()]["down"] = 1;
            GetFiles();
        }
    }
    reply->deleteLater();
}

void AutoUpdate::GetFiles()
{
    bool allDown = true;

    Q_FOREACH(const QByteArray& curFileName, fileList.keys()){
        if((int)fileList[curFileName]["down"] == 1) continue;

        QString newdir = "tmpPj/";
        if(curFileName.indexOf("/") != -1)
        newdir = QString("tmpPj/") + curFileName.mid(0, curFileName.lastIndexOf('/'));
        QDir().mkpath(newdir);       

        currentFile = curFileName;
        QString url = QString("http://%1:%2/%3/%4").arg(CsGetConfig("服务器IP")).arg(CsGetConfig("服务器Port")).arg(updatepath).arg((QString)curFileName);
        manager.get(QNetworkRequest(QUrl(url)));
        allDown = false;
        break;
    }

    if(allDown) ReplaceNewFile();
}

void AutoUpdate::ReplaceNewFile()
{
    qDebug() << QDir::currentPath();

    Q_FOREACH(const QString& fileT, fileList.keys())
    {
        QByteArray file = fileT.toLatin1();
        file.replace("\\", "/");
        QByteArray tmpF = QByteArray("tmpPj/") + file;
        int find = file.indexOf('/');
//        if(find < 0) return Error("文件名非法");
        QByteArray curfile = file;
        QByteArray cdir = curfile;
        find = 0;
        while((find = cdir.indexOf('/', find)) >= 0) {
            QDir().mkdir(QByteArray("./") + cdir.mid(0, find).constData());
            find++;
        }
        QFile::remove("../" + curfile);
        bool renameFile = false;
        {
            QFile file(tmpF);
            renameFile = file.size() > 0;
            qDebug() << "rename" << tmpF << "./" + curfile << "file size" << file.size();
        }
        QFile::remove("./" + curfile);
        renameFile = renameFile && QFile::rename(tmpF, "./" + curfile) && QFile::setPermissions("./" + curfile, (QFile::Permission)0xffffffff);

        if(renameFile) {
            //更新数据记录
            file = (const char*)fileT.toLatin1();
            if(!CacheInstance.SaveConfig( (QByteArray("atup__") + file).constData(), (const char*)fileList[file.constData()]["hash"])) {
                qDebug() <<  "自动更新写入数据库出错";
                exit(9);
            }
        }
    }
    qDebug() << "完成重命名" << fileList.keys().size();
    QDir tmp("tmpPj");
    tmp.removeRecursively();
    ::exit(0);
}
#undef main
#include <QGuiApplication>
#include <QLibrary>
extern void SetStringCode(const char* code);
extern "C" int __main(QGuiApplication *app);

UpdateBackWorker::UpdateBackWorker() {
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
    //每分钟检查一次文件更新
    timer.start(60000);
}

void UpdateBackWorker::OnTimer() {
    timer.stop();
    AutoUpdate();
    timer.start();
}
int main(int argc, char *argv[]) {
    QGuiApplication *app = new QGuiApplication(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));

    static Identify identify;
    AutoUpdate autoUpdate;

    qDebug() << "启动程序";
    QDir dir("./libDzflUpdate.so");
    QString path = dir.absolutePath();
    qDebug() << path;
    //如果有新的版本文件，使用新版程序入口
    if(QFile::exists("./libDzflUpdate.so")) {
        QLibrary *m_li = NULL;
        m_li = new QLibrary(path);
        m_li->load();
        if (!m_li->isLoaded())
        {
            qDebug() << "libDzflUpdate.so加载失败";
        }
        typedef int (*Fun)(QGuiApplication*);
        Fun fun = (Fun)m_li->resolve("__main");
        qDebug() << "更新程序入口" << fun;
        if(fun) fun(app);
    } else {
        qDebug() << "libDzflUpdate.so文件不存在";
    }
    __main(app);
}
