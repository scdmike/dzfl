#ifndef IRPC
#define IRPC
#include <QQuickItem>
#include <QQmlExtensionPlugin>
#include "Record.h"

#define PROPERTY(type, name) \
    private:\
    type name; \
    Q_SIGNALS: \
    void notify##name(); \
    public:\
    Q_PROPERTY(type name READ name##Value WRITE set##name NOTIFY notify##name ); \
    type name##Value() const { return name; } \
    void set##name(const type& value) { name = value; emit notify##name(); }

//全局设置属性，QML与C++共用互通
#define SETTING_PROPERTY(type, name) \
    Q_SIGNALS: \
    void notify##name(); \
    public:\
    Q_PROPERTY(type name READ name##Value WRITE set##name NOTIFY notify##name ); \
    type& name##Value() const { static type name; return name; } \
    void set##name(const type& value) { name##Value() = value; emit notify##name(); }

class MyItem : public QQuickItem {
Q_OBJECT
};

class IRpc : public MyItem {
Q_OBJECT
public:
    /* QML向服务端请求数据 */
    Q_INVOKABLE virtual void    getData()                       = 0;

Q_SIGNALS:
    /* 给QML系统的信号，触发界面更新 */
    void                        result(QString list);

protected:
    /* 处理服务端返回的数据，默认直接把服务端返回的Json直接给到QML */
    virtual void                RecvResult(Record& result);
    void                        SendCommand(const Record& cmd);
    QByteArray                  szData;
    friend class                ServiceConnect;
};

//用于在没有代码时，项目上编辑QML文件时，设计器的加载
class Q_DECL_EXPORT MyPlugin : public QQmlExtensionPlugin {
Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
public:
    void                registerTypes(const char *uri);

public:
    struct              RegObject {
        virtual int     Reg(const char *uri) = 0;
        virtual         ~RegObject()  { }
    };
    static void         AddRegObject(const char* uri, RegObject* obj);
};

QByteArray HttpPost(const QString& host, int port, const QString& url, const QByteArray& postData);

#endif // IRPC

