#ifndef AllConfigs_H
#define AllConfigs_H
#include "UILogic.h"

class AllConfigs : public UILogic
{
Q_OBJECT
public:
    Q_INVOKABLE QString allSettings;
    Q_INVOKABLE QString getAllSetting(QString array);
    Q_INVOKABLE QString dmGetSett(QString updatekey);
    Q_INVOKABLE void dmSaveSett(QString updatekey,QString updateValue);
    Q_INVOKABLE QString getTeamSetting(QString array);
    Q_INVOKABLE QString checkingValue();
    Q_INVOKABLE QString getOtherSetting(QString array);
    Q_INVOKABLE QString updateConfigs();
    Q_INVOKABLE QString getSetCompare();
    Q_INVOKABLE QString appReStart();
public:
    void            Show(Record& vdata);
    const char*     UIObjectName() { return "AllConfigs"; }
    bool            Init();
    QString         getAllConfigs();   
    void            getConfigs();
    void            dtglState();
    QMap<QString, QString>  SettingKeyValue;
    bool            QtPing(const QString ip);
    int  GetHttpContentLength(const QByteArray& httpData, int httpHeadLen);
    Record sendGetUrl(QString urlForSp, Record cmdBiz);
    QString token;
};

#endif // AllConfigs_H
