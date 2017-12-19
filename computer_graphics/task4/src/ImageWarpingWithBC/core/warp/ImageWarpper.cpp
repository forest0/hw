#include "ImageWarpper.h"
#include <opencv2/imgproc.hpp>
#include <cassert>
#include "../../utils/Utils.h"
#include "../coordinates/BarycentricCoordinate.h"
#include "../coordinates/WachspressCoordinate.h"
#include <QtCore/QDebug>
#include <QtGui/QPainter>

#include "../../view/ImageView.h"

// ImageWarpper::ImageWarpper() 
//     :image(nullptr), beforeVertices(), 
//     generatedInternalPoints(generatedInternalPointsAmount)
// {
// 
// }

ImageWarpper::ImageWarpper(QImage ** image, 
        const std::vector<QPoint > &afterVertices)
    :image(image), afterVertices(afterVertices),
    generatedInternalPoints(generatedInternalPointsAmount),
    generatedInternalPointsBC()
{

}

void ImageWarpper::warp(int index, const QPoint & delta) {
    assert((0 <= index) && (index <= afterVertices.size()));
    beforeVertices = afterVertices;
    beforeVertices[index] -= delta;
    init();

    QImage *warppedImage = new QImage((*image)->width(),
            (*image)->height(), (*image)->format());
    warppedImage->fill(Qt::white);

    BarycentricCoordinate *beforeBC = new WachspressCoordinate(
            beforeVertices);
    BarycentricCoordinate *afterBC = new WachspressCoordinate(
        afterVertices);
    std::vector<double> bc1;
    std::vector<double> bc2;
    std::vector<double> bc3;
    std::vector<double> currentPointBC;
    for (const auto &triangle : validTriangles) {
        bc1 = beforeBC->getCoordinateOf(triangle.point1);
        bc2 = beforeBC->getCoordinateOf(triangle.point2);
        bc3 = beforeBC->getCoordinateOf(triangle.point3);

        QPoint point1 = afterBC->getRealCoordinateOf(bc1);
        QPoint point2 = afterBC->getRealCoordinateOf(bc2);
        QPoint point3 = afterBC->getRealCoordinateOf(bc3);

        Triangle afterTriangle(point1, point2, point3);
        std::vector<QPoint> internalIntegerPoints = 
            afterTriangle.getInternalIntegerPoints();

        for (const auto &point : internalIntegerPoints) {
            if ((point.x() > warppedImage->width()) ||
                    (point.x() < 0) || (point.y() < 0) ||
                    (point.y() > warppedImage->height())) {
                continue;
            }
            currentPointBC = afterBC->getCoordinateOf(point);
            QPoint originPoint = beforeBC->getRealCoordinateOf(
                    currentPointBC);
            if ((originPoint.x() > warppedImage->width()) ||
                    (originPoint.x() < 0) || (point.y() < 0) ||
                    (originPoint.y() > warppedImage->height())) {
                continue;
            }
            warppedImage->setPixel(point, 
                    (*image)->pixel(originPoint));
        }


    }

    delete *image;
    *image = warppedImage;
}

ImageWarpper::~ImageWarpper() {

}

// void ImageWarpper::setImage(QImage * image) {
//     this->image = image;
// }

// void ImageWarpper::setbeforeVertices(const std::vector<QPoint> &beforeVertices) {
//     this->beforeVertices = beforeVertices;
// }

void ImageWarpper::init() {
    initGeneratedInternalPoints();
    calculateValidTriangles();
}

void ImageWarpper::calculateValidTriangles() {
    assert(this->image);
    assert(generatedInternalPoints.size());
    cv::Rect rect(0,0, (*image)->width(), (*image)->height());
    cv::Subdiv2D subdiv(rect);

    for (const auto &point : beforeVertices) {
        subdiv.insert(Utils::qPointF2cvPoint2f(point));
    }
    for (const auto &point : generatedInternalPoints) {
        subdiv.insert(Utils::qPointF2cvPoint2f(point));
    }

    std::vector<cv::Vec6f> triangles;
    subdiv.getTriangleList(triangles);

    for (const auto &vec : triangles) {
        if (isValidTrianglePoints(vec)) {
            validTriangles.push_back(Triangle(
                QPointF(vec[0],vec[1]),QPointF(vec[2],vec[3]),
                QPointF(vec[4],vec[5])));
        }
    }
}

bool ImageWarpper::isValidTrianglePoints(const cv::Vec6f &vector) const {
    assert(this->image);
    int validMaxValue = (*image)->width() > (*image)->height() ?
        (*image)->width() : (*image)->height();

    for (int i = 0; i < 6; ++i) {
        if (vector[i] > validMaxValue || vector[i] < -validMaxValue) {
            return false;
        }
    }

    return true;
}

void ImageWarpper::initGeneratedInternalPoints() {
    const int beforeVerticesAmount = beforeVertices.size();
    assert(beforeVerticesAmount);
    std::vector<double> weights(beforeVerticesAmount);
    double x = 0.0;
    double y = 0.0;
    for (int i = 0; i < generatedInternalPointsAmount; ++i) {
        x = y = 0.0;
        weights = Utils::getRandomBC(beforeVerticesAmount);
        generatedInternalPointsBC.push_back(weights);

        for (int j = 0; j < beforeVerticesAmount; ++j) {
            x += weights[j]*beforeVertices[j].x();
            y += weights[j]*beforeVertices[j].y();
            generatedInternalPoints[i] = QPoint(x, y);
        }
    }
}

#include <QtGui/QPainter>
void ImageWarpper::debug() {
    assert(image);
    QPainter painter(*image);
    for (const auto &triangle : validTriangles) {
        QPointF point1 = Utils::cvPoint2f2QPointF(triangle.point1);
        QPointF point2 = Utils::cvPoint2f2QPointF(triangle.point2);
        QPointF point3 = Utils::cvPoint2f2QPointF(triangle.point3);
        painter.drawLine(point1, point2);
        painter.drawLine(point1, point3);
        painter.drawLine(point2, point3);
    }
}

