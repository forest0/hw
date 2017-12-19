#ifndef IMAGEWARPPER_H
#define IMAGEWARPPER_H

#include <QtGui/QImage>
#include <QtCore/QPoint>
#include <vector>
#include "../model/Triangle.h"

class ImageWarpper {

public:
    // ImageWarpper();
    ImageWarpper(QImage **image, 
            const std::vector<QPoint> &afterVertices);
    virtual ~ImageWarpper();
    void warp(int index, const QPoint &delta);
    void setImage(QImage *image);
    // void setVertices(const std::vector<QPoint> &vertices);

    void debug();

private:
    void init();
    void initGeneratedInternalPoints();
    void calculateValidTriangles();
    bool isValidTrianglePoints(const cv::Vec6f &vector) const;

private:
    QImage **image;
    /* TODO:  <18-12-17, duplicate here> */
    std::vector<QPoint> beforeVertices;
    std::vector<QPoint> afterVertices;
    const int generatedInternalPointsAmount = 30;

    std::vector<QPoint> generatedInternalPoints;
    std::vector<Triangle> validTriangles;

    std::vector<std::vector<double>> generatedInternalPointsBC;

};

#endif /* IMAGEWARPPER_H */
