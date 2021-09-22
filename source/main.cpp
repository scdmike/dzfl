#include <QTextCodec>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QSharedMemory>
#include <QGuiApplication>
#include <QScreen>
#include<QFontDatabase>
#include "../inc/CommandBuffer.h"
#include "../inc/HttpServer.h"
#include "../inc/UILogic.h"
#include "../public/ImageStreamLoader.h"
#include "../public/PixmapLoader.h"
#include "../inc/TcpReadCommand.h"
#include "../inc/AllConfigs.h"
//安卓自动更新由进程自已负责
#ifdef ANDROID
    #include "../public/autoUpdate.h"
    #include "../public/Logger.h"
#endif

QQuickView*     pViewer = NULL;
QList<UILogic*> logicList;

void RegLogicToScript(QQuickView* viewer)
{
    for(QList<InstanceFun>::Iterator it = UILogic::RegInstance().begin();
        it != UILogic::RegInstance().end(); ++it) {
        UILogic* tmp = (*it)();

        if(tmp && tmp->Init())
            viewer->rootContext()->setContextProperty(tmp->UIObjectName(), (QObject*)tmp);
    }

    for(QList<UILogic*>::Iterator it = UILogic::AllInstance().begin();
        it != UILogic::AllInstance().end(); ++it) {
        UILogic* tmp = *it;
        if(tmp->Init() && viewer->rootContext()->contextProperty(tmp->UIObjectName()).isNull())
            viewer->rootContext()->setContextProperty(tmp->UIObjectName(), (QObject*)tmp);
    }

    for(int i = UILogic::RegInstance().size() - 1; i >= 0; i--) {
        UILogic* tmp = (UILogic::RegInstance()[i])();

        if(tmp) UILogic::AllInstance().insert(UILogic::AllInstance().begin(), tmp);
    }
    UILogic::RegInstance().clear();
}

#ifdef ANDROID
extern "C"
#else
#include "../public/autoUpdateWin.h"
#include "../public/identify.h"
#include <QLibrary>
/* 加载异常打印DLL */
static struct LoadTracStack {
    LoadTracStack() {
        QLibrary("tracstack.dll").load();
    }
} loadTracStack;
#endif
int main(int argc, char *argv[])
{

    //从大厅管理系统获取配置项并保存
    //AllConfigs allConfigs ;
    
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#ifndef ANDROID
    QGuiApplication *app = new QGuiApplication(argc, argv);
    //保证只启动一个实例
    QSharedMemory mem("DzflApp");
    if (!mem.create(1)) { // 如果全局对象以存在则退出
        return 0;
    }
    AutoUpdateWin autoUpdateWin;
    static Identify identify;
#else
    //InstallLogcatMessageHandler("InspurPJDebug");
    int fontId = QFontDatabase::addApplicationFont("assets:/msyh.ttf");
    QString msyh = QFontDatabase::applicationFontFamilies ( fontId ).at(0);
    QFont font(msyh);
    QGuiApplication::setFont(font);
    qDebug() << qApp->font().family();
    UpdateBackWorker backUpdate;      //不使用定时更新文件
#endif

    QQuickView myView;
    pViewer = &myView;

    myView.engine()->addImageProvider("ImageStreamLoader", new ImageStreamLoader);
    myView.engine()->addImageProvider("PixmapLoader", new PixmapLoader);

    QString startPage = CsGetConfig("启动页");   
    myView.setSource(QUrl(startPage));
    if(CsGetConfig("自适应")[0] == '1') {
        QScreen* screen = QGuiApplication::primaryScreen();
        int screenWidth = screen->size().width();
        int screenHeight = screen->size().height();
        int main_width = myView.rootObject()->property("width").toInt();
        int main_height = myView.rootObject()->property("height").toInt();
        float sx = myView.rootObject()->property("sx").toFloat();
        float sy = myView.rootObject()->property("sy").toFloat();
        float ori_width = main_width/sx;
        float ori_height = main_height/sy;
        sx = screenWidth/ori_width;
        sy = screenHeight/ori_height;
        myView.rootObject()->setProperty("width", screenWidth);
        myView.rootObject()->setProperty("height", screenHeight);
        myView.rootObject()->setProperty("sx", sx);
        myView.rootObject()->setProperty("sy", sy);
    }

    //标题不能让QML文件中改变了
    myView.setTitle("Dzfl");
    //自适应屏幕


    #ifndef ANDROID
        if(CsGetConfig("调试")[0] != '1') {
            pViewer->setFlags(Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint);
            }
        myView.show();
    #else
        if(CsGetConfig("调试")[0] != '1') {
            myView.showFullScreen();
         }else{
            myView.show();
        }

    #endif

    QObject::connect(myView.engine(), SIGNAL(quit()), app, SLOT(quit())); //这句代码作用是在qml中可以使用Qt.quit()方法

    //注册UI逻辑
    RegLogicToScript(pViewer);
    //评价定时处理命令
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), CmdBufInstance, SLOT(DoCommand()));
    timer.start(50);

    //开始命令接收
    HttpServer http;
    TcpServer tcp; tcp.Run();

    if(startPage.isEmpty() || !QFile::exists(startPage)){
            AllConfigs* pUi = new AllConfigs();
            pUi->Init();
            myView.engine()->rootContext()->setContextProperty("AllConfigs",  pUi);

    }else if(CsGetConfig("窗口工号")[0] != '\0') {
        char vdata[100] = {0};
        CmdBufInstance->ShowPage("FramePage", vdata);
    }else {
        CmdBufInstance->ShowPage("IntroPage", NULL);
    }
    return app->exec();
}

void CppCommand(int id, const char* vdata)
{
    CmdBufInstance->AddCommand(id, vdata);
}
