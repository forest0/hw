#ifndef IMAGEWARPER_H
#define IMAGEWARPER_H

#include <QtCore/QObject>
#include "Mapper.h"
#include <QtGui/QRgb>

class ImageWarper : public QObject {
    Q_OBJECT
    public:
        explicit ImageWarper(Mapper *mapper, QObject *parent = nullptr);
        ~ImageWarper();
        QImage * warp(QImage *image) const;

    signals:

    public slots:

    private:
        QImage * resample(QImage *image) const;
        QRgb findNearColor(QImage *image, const QPoint &point) const;

    private:
        Mapper *mapper;
};

#endif // IMAGEWARPER_H
