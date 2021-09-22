#include <QDebug>
#include <QQuickItem>
#include <QTimer>
#include "../public/Setting.h"
#include "../public/StringCommond.h"
#include "ServiceConnect.h"

CSetting& CSetting::Instance() {
    static CSetting setting;
    return setting;
}

static struct RegistType_CSetting : MyPlugin::RegObject {
    RegistType_CSetting() { MyPlugin::AddRegObject("SmartTerminal.Setting", this); }
    int Reg(const char *) {
        qDebug() << "qmlRegisterType" << "Timer" << "Setting";
        return  qmlRegisterType<QTimer>("SmartTerminal", 1, 0, "Timer"),
                qmlRegisterType<CSetting>("SmartTerminal", 1, 0, "Setting");
    }
} _RegistSettingType;

void StringCommand::getData() {
    szData = cmd.toUtf8();
    ServiceConnect::IConnect().Send(this);
}

static struct RegistType_StringCommand : MyPlugin::RegObject {
    RegistType_StringCommand() { MyPlugin::AddRegObject("SmartTerminal.StringCommand", this); }
    int Reg(const char *) {
        return  qmlRegisterType<StringCommand>("SmartTerminal", 1, 0, "StringCommand");
    }
} _RegistType_StringCommand;

