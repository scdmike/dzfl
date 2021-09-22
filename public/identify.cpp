#include "../public/Cache.h"
#include <QFile>
#include <QDebug>
#include <QCryptographicHash>
#include <QNetworkInterface>
#include <QHostInfo>
#include "identify.h"
//
Identify::Identify() : QObject(NULL) {
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(OnTimer()));

    CacheInstance;

    infoAll["hierarchy"] = CsGetConfig("所属层级");

#ifdef ANDROID
    infoAll["IdeSN"] = "PAD HD";
    infoAll["CpuInfo"][0] = "ARMv7";
    infoAll["Net0Mac"] = "WIFI";
    infoAll["BiosSN"] = "null";
    infoAll["name"] = "android";

    QFile cpu("/proc/cpuinfo");
    if(cpu.open(QIODevice::ReadOnly)) {
        QByteArray md5souce = cpu.readAll();
        infoAll["SSID"] = QString(QCryptographicHash::hash(md5souce, QCryptographicHash::Md5).toBase64());
        cpu.close();
    }
#else
    infoAll["name"] = "window";
    QString localhostName = QHostInfo::localHostName();
    QNetworkInterface* netinterface = new QNetworkInterface;
    QString mac = netinterface->hardwareAddress();
    QByteArray md5souce =QString("%1+%2").arg(localhostName).arg(mac).toLatin1();
    infoAll["SSID"] = QString(QCryptographicHash::hash(md5souce, QCryptographicHash::Md5).toBase64());
#endif
    QString timeStep = QString::fromLocal8Bit(CsGetConfig("监控数据上传间隔"));
    qDebug() << "Identify Timer Start" << timeStep;
    if(timeStep.isEmpty())
        timer.start(10000);
    else
        timer.start(timeStep.toLong() * 1000);
}

void Identify::OnTimer() {
#ifdef ANDROID
    infoShort["cpuUse"] = "0";
    infoShort["hostName"] = "android";
    infoAll["infoShort"] = infoShort;

    Record send = infoShort;
    send["cmd"] = "PushPjMonitorC2S";
    send["SSID"] = infoAll["SSID"];
    send["IPAddr"] = CsGetConfig("监控配置IP");
    Record resutl = CacheInstance.ServiceDoCommand(send.ToString());
    if((int)resutl["ReqHardware"] == 1) {
        send = infoAll;
        send["cmd"] = "PushPjMonitorC2S";
        CacheInstance.ServiceDoCommand(send.ToString());
    }
#else
    Record send = infoAll;
    send["cmd"] = "PushPjMonitorC2S";
    send["IPAddr"] = CsGetConfig("监控配置IP");
    CacheInstance.ServiceDoCommand(send.ToString());
#endif
}
