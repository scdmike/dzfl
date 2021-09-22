#ifndef _COPY_DATA_H_
#define _COPY_DATA_H_

struct CommandID { enum { INTRODUCE = 1,
                          USER_INFO
                        }; };
struct CopyData_Generic {
    int         cmd;
};

struct CopyData_PauseType : CopyData_Generic {
    CopyData_PauseType() { memset(data, 0, sizeof(data)); }
    char        data[100];
};

struct CopyData_UserInfo : CopyData_Generic {
    CopyData_UserInfo() { memset(data, 0, sizeof(data)); }
    char        data[100];
};

struct CopyData_Appraise : CopyData_Generic {
    CopyData_Appraise() { memset(data, 0, sizeof(data)); }
    char        data[100];
};

struct CopyData_ViewPersonID : CopyData_Generic {
    CopyData_ViewPersonID() { memset(data, 0, sizeof(data)); }
    char        data[100];
};

struct CopyData_CheckPageVisible : CopyData_Generic {
    CopyData_CheckPageVisible() { memset(data, 0, sizeof(data)); }
    char        data[100];
};

struct CopyData_ScreenCapture : CopyData_Generic {
    int         size;
};
typedef CopyData_ScreenCapture CopyData_Proxy;

#endif//_COPY_DATA_H_
