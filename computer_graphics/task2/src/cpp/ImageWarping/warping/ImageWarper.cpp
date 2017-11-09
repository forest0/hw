#include "ImageWarper.h"
#include <QtGui/QRgb>
#include <QtGui/QColor>
#include <QtCore/QPoint>
#include <QtGui/QImage>
#include "../tools/Log.h"
#include <iostream>
#include <cstring>

ImageWarper::ImageWarper(Mapper *mapper, QObject *parent) 
    : QObject(parent),
    mapper(mapper)
{

}

ImageWarper::~ImageWarper() {
    if (mapper) {
        delete mapper;
    }
}

QImage * ImageWarper::warp(QImage *image) const {
        std::vector<std::pair<QPoint, QRgb>> pixels;
    int maxX = 0;
    int minX = 0;
    int maxY = 0;
    int minY = 0;

    for (int i = 0; i < image->height(); ++i) {
        for (int j = 0; j < image->width(); ++j) {
            QRgb rgb = image->pixel(j,i);
            QPoint point = mapper->map(QPoint(j,i));
            pixels.push_back(std::make_pair(point, rgb));
            if (maxX < point.x()) {
                maxX = point.x();
            }
            if (minX > point.x()) {
                minX = point.x();
            }
            if (maxY < point.y()) {
                maxY = point.y();
            }
            if (minY > point.y()) {
                minY = point.y();
            }
        }
    }

    if (minX < 0) {
        maxX -= minX;
        minX = -minX;
    }
    if (minY < 0) {
        maxY -= minY;
        minY = -minY;
    }

    QImage *warpedImage = new QImage(maxX+1, maxY+1, 
            QImage::Format_RGB888);
    // clear memory, or there are massive noises
    std::memset(warpedImage->bits(), 255, warpedImage->byteCount());

    QPoint offset(minX, minY);
    for (const auto &pair : pixels) {
        warpedImage->setPixel(pair.first+offset, pair.second);
    }

    QImage *resampledImage = resample(warpedImage);

    delete warpedImage;
    warpedImage = nullptr;
    
    return resampledImage;

}

QImage * ImageWarper::resample(QImage *image) const {
    QRgb blank = QColor(255,255,255).rgb();
    QImage *resampledImage = new QImage(*image);
    for (int i = 0; i < image->height(); ++i) {
        for (int j = 0; j < image->width(); ++j) {
            if (image->pixel(j,i) == blank) {
                QRgb rgb = findNearColor(image, QPoint(j,i));
                resampledImage->setPixel(j,i, rgb);
            }
        }
    }
    return resampledImage;
}

QRgb ImageWarper::findNearColor(QImage *image, const QPoint &point) const {
    const int searchLength = 3;
    QRgb blank = QColor(255,255,255).rgb();
    static std::vector<QPoint> directions{QPoint(-1,0), QPoint(0,-1),
        QPoint(1,0), QPoint(0,1), QPoint(-1,1), QPoint(-1,-1),
        QPoint(1,-1), QPoint(1,1)};
    for (int i = 1; i < searchLength; ++i) {
        for (const auto &direction : directions) {
            QPoint sampingPoint = point+(direction*i);
            if (image->valid(sampingPoint) && 
                    (image->pixel(sampingPoint) != blank)) {
                return image->pixel(sampingPoint);
            }
        }
    }
    return blank;
}
