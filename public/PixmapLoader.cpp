#include <QBuffer>
#include <QPainter>
#include <QDebug>
#include <QTime>
#include "PixmapLoader.h"
//utf-8
PixmapLoader::PixmapLoader() : QQuickImageProvider(QQuickImageProvider::Pixmap) {
}

QPixmap PixmapLoader::requestPixmap(const QString& streamInfo, QSize *size, const QSize &reqSize) {
    int width = 100;
    int height = 50;

    if (size)
        *size = QSize(width, height);

    QPixmap pixmap;
    QPixmap* p = (QPixmap*)streamInfo.split('#', QString::SkipEmptyParts)[0].toULongLong();
    if(p == NULL) return pixmap;

    pixmap.swap(*p);
    delete p;
    qDebug() << "requestPixmap" << p;

    if (reqSize.isValid())
    {
        pixmap = pixmap.scaled(reqSize.width(), reqSize.height());
    } else {
        size->setWidth(pixmap.width());
        size->setHeight(pixmap.height());
    }

    return pixmap;
}

//TIF文件头结构
typedef struct tagIMAGEFILEHEADER {
  quint16 byteOrder;
  quint16 version;
  quint32 offsetToIFD;
} IFH;

QString LoadTifImage(const QString& text) {
    do {
        if(!text.startsWith("Base64://")) break;
        if(text.mid(9, 3) == "/9j") break;      //jpg格式

        size_t len = text.length() - 9;
        QByteArray image = QByteArray::fromBase64(text.toUtf8().mid(9, len));
        QBuffer buf;
        buf.setData(image);
        buf.open(QIODevice::ReadWrite);
        buf.seek(0);

        IFH ifh;
        //读取文件头
        if(sizeof(IFH) != buf.read((char*)&ifh, (qint64)sizeof(IFH))) break;
        //是否是tif格式
        if(ifh.version != 0x2a) break;

        //初始化ifhList链表
        QList<quint32> ifhList;
        quint16 deCount;
        while(ifh.offsetToIFD) {
            ifhList.append(ifh.offsetToIFD);       //第i幅图片的存储开始位置。
            buf.seek(ifh.offsetToIFD);             //文件读定位到第i幅文件的开始位置
            buf.read((char*)&deCount,2);
            buf.seek(ifh.offsetToIFD+deCount*12+2);//文件定位到offsetToNextIFD
            buf.read((char*)&ifh.offsetToIFD,4);
        }
        QList<QImage*> images;
        for(int i = 0; i < ifhList.size(); i ++) {
            buf.seek(4);
            buf.write((const char*)&(ifhList[i]), 4);
            QImage *img = new QImage();
            img->loadFromData((const uchar*)buf.data().data(), len);
            images.append(img);
        }
        buf.close();

        if(images.size() == 0) break;
        int w = images[0]->width();
        int h = 0;
        for(int i = 0; i < images.size(); i++) h += images[i]->height();
        QPixmap* pixmap = new QPixmap(w, h);
        h = 0;
        QPainter painter(pixmap);
        for(int i = 0; i < images.size(); i++) {
            painter.drawImage(0, h, *(images[i]));
            h += images[i]->height();
        }
        painter.end();
        for(int i = 0; i < images.size(); i++) { delete images[i]; images[i] = NULL; }

        QString imgSource = "image://PixmapLoader/";
        imgSource += QString::number((qulonglong)pixmap);
        imgSource += '#';
        imgSource += QTime::currentTime().toString();

        return imgSource;
    } while(0);

    return "";
}

QString MyLoadImage(const QString& text) {
    do {
        size_t len = text.length() - 9;

        QByteArray image = QByteArray::fromBase64(text.toUtf8().mid(9, len));
        QPixmap* pixmap = new QPixmap;
        if(!pixmap->loadFromData(image))
            break;

        QString imgSource = "image://PixmapLoader/";
        imgSource += QString::number((qulonglong)pixmap);
        imgSource += '#';
        imgSource += QTime::currentTime().toString();

        return imgSource;
    } while(0);

    return "";
}
