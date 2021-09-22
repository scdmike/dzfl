#ifndef STRINGCOMMOND
#define STRINGCOMMOND

#include "General.h"

class StringCommand : public IRpc {
Q_OBJECT
    PROPERTY(QString, cmd)

public:
    void getData();
};

#endif // STRINGCOMMOND

