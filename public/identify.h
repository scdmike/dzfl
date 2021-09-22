#ifndef IDENTIFY_H
#define IDENTIFY_H

#include "../public/Record.h"
#include <QObject>
#include <QTimer>
#include <QQuickItem>

class Identify : public QObject
{
Q_OBJECT
public:
    explicit Identify();

public slots:
    void OnTimer();

private:
    QTimer          timer;
    Record          infoAll;
    Record          infoShort;
};

#endif // IDENTIFY_H
