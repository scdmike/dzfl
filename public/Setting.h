#ifndef SETTING
#define SETTING

#include <QQuickItem>
#include "General.h"

class CSetting : public MyItem {
Q_OBJECT
    SETTING_PROPERTY(QString,   serviceIP)
    SETTING_PROPERTY(int,       servicePort)
    SETTING_PROPERTY(QString,   startQmlPage)
    SETTING_PROPERTY(QString,   updateDirectory)
    SETTING_PROPERTY(bool,      multipleStart) 
public:
    static CSetting&            Instance();
};

#define Setting                 CSetting::Instance()

#endif // SETTING

