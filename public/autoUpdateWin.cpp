#include <QDir>
#include <QProcess>
#include <QQuickView>
#include <QQuickItem>
#include <QQuickWindow>
#include <QCryptographicHash>
#include "autoUpdateWin.h"
#include "QDebug"
#include "../public/Cache.h"
////
AutoUpdateWin::AutoUpdateWin() {
    QObject::connect(&manager, &QNetworkAccessManager::finished, this, &AutoUpdateWin::UpdateFileResult);
    GetFileInfo();
}

void AutoUpdateWin::GetFileInfo()
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

void AutoUpdateWin::UpdateFileResult(QNetworkReply *reply){
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

void AutoUpdateWin::GetFiles()
{
    bool allDown = true;

    Q_FOREACH(const QByteArray& curFileName, fileList.keys()){
        if((int)fileList[curFileName]["down"] == 1) continue;

        QString newdir = "tmpPj/";
        if(curFileName.indexOf("/") != -1)
        newdir = QString("tmpPj/") + curFileName.mid(0, curFileName.lastIndexOf('/'));
        QDir().mkpath(newdir);       

        currentFile = curFileName;
        QString url = QString("http://%1:%2/%3/%4").arg(CsGetConfig("评价服务器IP")).arg(CsGetConfig("评价服务器Port")).arg(updatepath).arg((QString)curFileName);
        manager.get(QNetworkRequest(QUrl(url)));
        allDown = false;
        break;
    }

    if(allDown) ReplaceNewFile();
}

void AutoUpdateWin::ReplaceNewFile()
{
    QFile bat("replaceFilePj.bat");
    if(bat.open(QFile::WriteOnly)) {
        bat.write(QString("@echo off \r\n").toLocal8Bit());
        bat.write(QString("echo 正在准备更新文件... \r\n").toLocal8Bit());
        bat.write(QString("ping -n 3 127.0.0.1 > nul \r\n").toLocal8Bit());
        bat.write(QString("echo 开始文件替换 \r\n").toLocal8Bit());

        bat.write(QString("xcopy /S /E /Y tmpPj .\\ > nul \r\n").toLocal8Bit());

        bat.write(QString("echo 更新完成 \r\n").toLocal8Bit());
        bat.write(QString("rd /s /q tmpPj > nul \r\n").toLocal8Bit());
        bat.write(QString("start dzfl.exe > nul \r\n").toLocal8Bit());
        bat.write(QString("del replaceFilePj.bat \r\n").toLocal8Bit());
        bat.close();
        qDebug()<<"启动cmd："<<QProcess::startDetached("cmd.exe", QStringList() << "/c" << "replaceFilePj.bat");
        #ifdef _MSC_VER
        //此处为MSVC编译器环境下的代码
            ::quick_exit(0);
        #elif __GNUC__
        //此处为MinGW编译器环境下的代码
            ::exit(0);
        #endif
    }
}
