TEMPLATE = app

QT +=  quick qml quickcontrols2 sql network multimedia gui xml

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += CONNECT_TIME_OUT=5000


SOURCES += \
    public/Logger.cpp \
    source/CommandBuffer.cpp \
    source/DisableButton.cpp \
    source/FramePage.cpp \
    source/IntroPage.cpp \
    source/ScrollMessage.cpp \
    source/ServiceGuide.cpp \
    source/ServiceGuideDept.cpp \
    source/ServiceGuideDetail.cpp \
    source/ServiceGuideGetByUrl.cpp \
    source/main.cpp \
    source/AllConfigs.cpp \
    source/ServiceInfo.cpp \
    source/TcpReadCommand.cpp \
    source/TelWindow.cpp \
    source/UILogic.cpp \
    public/Cache.cpp \
    public/ConfigFile.cpp \
    public/CServer.cpp \
    public/CSocket.cpp \
    public/PixmapLoader.cpp \
    private/Reader.cpp \
    private/Record.cpp \
    public/audioRecord.cpp \
    public/HttpServer.cpp \
    public/identify.cpp


RESOURCES += \
    dzfl.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    inc/ScrollMessage.h \
    inc/ServiceGuide.h \
    inc/ServiceGuideDept.h \
    inc/ServiceGuideDetail.h \
    inc/ServiceGuideGetByUrl.h \
    public/Cache.h \
    public/CopyData.h \
    public/CServer.h \
    public/CSocket.h \
    public/ImageStreamLoader.h \
    public/Logger.h \
    public/PixmapLoader.h \
    private/Reader.h \
    public/Record.h \
    inc/CommandBuffer.h \
    inc/ConsoleMessageBox.h \
    inc/DisableButton.h \
    inc/FramePage.h \
    inc/HonestPage.h \
    inc/IntroPage.h \
    inc/AllConfigs.h \
    inc/ServiceInfo.h \
    inc/TcpReadCommand.h \
    inc/TelWindow.h \
    inc/UILogic.h \
    public/audioRecord.h \
    inc/HttpServer.h \
    public/identify.h \
    inc/DutyPage.h \


android {
    QT += androidextras



    HEADERS += \
        public/Proxy.h \
        public/autoUpdate.h \

    SOURCES += \
        public/Proxy.cpp \
        public/autoUpdate.cpp

    DISTFILES += \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradlew.bat \
        android/build.gradle \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew \
        android/src/org/qtproject/qt5/android/bindings/StartService.java \
        android/assets/config.txt\
        android/AndroidManifest.xml

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

win32 {

    RC_FILE = app.rc
    HEADERS +=  public/autoUpdateWin.h

    SOURCES += \
                public/autoUpdateWin.cpp

     LIBS += -luser32
}

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS =
}



INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include





