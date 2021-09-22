#ifndef IMAGESTREAMLOADER_H
#define IMAGESTREAMLOADER_H

#include <QQuickImageProvider>

class ImageStreamLoader : public QQuickImageProvider
{
public:
    ImageStreamLoader()
        : QQuickImageProvider(QQmlImageProviderBase::Pixmap)
    {
    }

    QPixmap requestPixmap(const QString& streamInfo, QSize *size, const QSize &reqSize)
    {
        int width = 100;
        int height = 50;

        if (size)
            *size = QSize(width, height);

        QPixmap pixmap(width, height);
        pixmap.fill();

        QStringList szStr = streamInfo.split('#', QString::SkipEmptyParts);
        if(szStr.size() < 2)
            return pixmap;

        const unsigned char* ptr = (const unsigned char*)szStr[0].toULongLong();
        unsigned int len = szStr[1].toUInt();
        if(len == 0) return pixmap;
        if(pixmap.loadFromData(ptr, len))
        {
            if (reqSize.isValid())
            {
                pixmap = pixmap.scaled(reqSize.width(), reqSize.height());
            } else {
                size->setWidth(pixmap.width());
                size->setHeight(pixmap.height());
            }
        }

        return pixmap;
    }
};

#endif // IMAGESTREAMLOADER_H
