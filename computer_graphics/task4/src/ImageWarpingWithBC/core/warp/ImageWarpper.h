#ifndef IMAGEWARPPER_H
#define IMAGEWARPPER_H

#include <QtGui/QImage>
#include <QtCore/QPoint>
#include <vector>

class ImageWarpper {

public:
    ImageWarpper();
    ImageWarpper(QImage *image, std::vector<QPoint>vertices);
    virtual ~ImageWarpper();
    void warp(int index, const QPoint &delta);
    void setImage(QImage *image);
    void setVertices(std::vector<QPoint>vertices);

private:
    void init();

private:
    QImage *image;
    std::vector<QPoint> vertices;
};

#endif /* IMAGEWARPPER_H */
