#include "ImageWrapper.h"
#include <QtGui/QRgb>
#include <QtCore/QPoint>
#include <QtGui/QImage>
#include "../tools/Log.h"
#include <iostream>
#include <cstring>

ImageWrapper::ImageWrapper(Mapper *mapper, QObject *parent) 
    : QObject(parent),
    mapper(mapper)
{

}

ImageWrapper::~ImageWrapper() {
    if (mapper) {
        delete mapper;
    }
}

QImage * ImageWrapper::wrap(QImage *image) const {
        std::vector<std::pair<QPoint, QRgb>> pixels;
        int maxX = 0;
        int minX = 0;
        int maxY = 0;
        int minY = 0;

        for (int i = 0; i < image->height(); ++i) {
            for (int j = 0; j < image->width(); ++j) {
                QRgb rgb = image->pixel(i,j);
                QPoint point = mapper->map(QPoint(i,j));
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

        QImage *wrappedImage = new QImage(maxX+1, maxY+1, 
                QImage::Format_RGB888);
        // clear memory, or there are massive noises
        std::memset(wrappedImage->bits(), 255, wrappedImage->byteCount());

        QPoint offset(minX, minY);
        for (const auto &pair : pixels) {
            wrappedImage->setPixel( pair.first+offset, pair.second);
        }
        
        return wrappedImage;

}
