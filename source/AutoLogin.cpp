#include "../inc/UILogic.h"
class UserAutoLoginRegist
{
public:
    UserAutoLoginRegist() {
        UILogic::RegInstance().append(GetInstance);
    }

    static UILogic* GetInstance()
    {
        static bool init = false;
        if(!init) {
            if(CsGetConfig("自动登录")[0] == '1') {
                QString UserID = Cache::Instance().LastLoginUserID();
                qDebug() << "Cache::Instance().LastLoginUserID()" << UserID;
                if(!UserID.isEmpty())
                    CsSetRuntimeConfig("窗口工号", UserID);
            }
            init = true;
        }
        return NULL;
    }
} userAutoLoginRegist;
