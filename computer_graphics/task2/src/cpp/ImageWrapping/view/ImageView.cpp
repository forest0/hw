#include "ImageView.h"
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtGui/QColor>

ImageView::ImageView(QWidget *parent) 
    : QDialog(parent),
    image(nullptr)
{
    isDrawing = false;
}

ImageView::~ImageView() {
    if (image) {
        delete image;
    }
}

void ImageView::setImage(QImage *image) {
    this->image = image;
}

QImage * ImageView::getImage() const {
    return this->image;
}

void ImageView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(255,0,0));
    pen.setWidth(4);
    painter.setPen(pen);
    if (this->image) {
        painter.drawImage(getCenterPoint(), *(this->image));
    }
    painter.drawLine(startPoint, endPoint); // draw current controlPoints
    drawControlPoints(&painter); // draw previous controlPoints
}

void ImageView::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing) {
        endPoint = event->pos();
        this->update();
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (isDrawing) {
            isDrawing = false;
            endPoint = event->pos();
            update();
            addControlPointPair(
                std::make_pair(startPoint-getCenterPoint(),
                    endPoint-getCenterPoint()));
            resetStartAndEndPoints();
        }
    }
}

void ImageView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (!isDrawing) {
            isDrawing = true;
            startPoint = event->pos();
        }
    }
}

void ImageView::resetStartAndEndPoints() {
    startPoint.setX(-1);
    startPoint.setY(-1);
    endPoint.setX(-1);
    endPoint.setY(-1);
}

void ImageView::addControlPointPair(const std::pair<QPoint, QPoint> &pair) {
    controlPoints.push_back(pair);
}

std::vector<std::pair<QPoint, QPoint>> ImageView::getControlPoints() const {
    return this->controlPoints;
}

void ImageView::drawControlPoints(QPainter *painter) {
    for (const auto &pair : controlPoints) {
        painter->drawLine(pair.first+getCenterPoint(),
                pair.second+getCenterPoint());
    }
}

QPoint ImageView::getCenterPoint() const {
    return QPoint((this->width()-image->width())/2,
            (this->height()-image->height())/2);
}

void ImageView::clearControlPoints() {
    controlPoints.clear();
}
