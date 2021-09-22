#ifndef PIXMAPLOADER_H
#define PIXMAPLOADER_H

#include <QQuickImageProvider>

class PixmapLoader : public QQuickImageProvider
{
public:
    PixmapLoader();
    QPixmap requestPixmap(const QString& streamInfo, QSize *size, const QSize &reqSize);
};

QString MyLoadImage(const QString& base64);
QString LoadTifImage(const QString& base64);

#endif // PIXMAPLOADER_H
