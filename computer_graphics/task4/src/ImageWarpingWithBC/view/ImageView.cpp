#include "ImageView.h"
#include <QtGui/QPainter>
#include <QtCore/QPointF>
#include <QtGui/QMouseEvent>
#include <QtCore/QDebug>
#include "../core/warp/ImageWarpper.h"

ImageView::ImageView(QWidget *parent) : QWidget(parent),
    image(nullptr), imageBak(nullptr),
    startPoint(), endPoint(),
    drawingState(ImageView::DrawingState::DRAW),
    vertices(), isDrawing(false), cageIsDrawn(false),
    chosenPointIndex(-1), 
    dragStart(0,0), dragEnd(0,0)
{

}

ImageView::~ImageView() {
    if (this->image) {
        delete image;
        image = nullptr;
    }
    if (this->imageBak) {
        delete imageBak;
        imageBak = nullptr;
    }
}

void ImageView::paintEvent(QPaintEvent * event) {
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(255,0,0));
    pen.setWidth(4);
    if (this->image) {
        painter.drawImage(0, 0, *(this->image));
    }
    switch (getCurrentDrawingState()) {
        case ImageView::DrawingState::DRAW:
            if (!vertices.empty()) {
                for (unsigned int i = 0; 
                        i < (vertices.size()-1); ++i) {

                    painter.drawLine(vertices[i], vertices[i+1]);
                }
                if (cageIsDrawn) {
                    painter.drawLine(vertices.back(), 
                            vertices.front());
                }

            }
            if (!cageIsDrawn) {
                painter.drawLine(startPoint, endPoint);
            }
            break;
        case ImageView::DrawingState::DRAG:
            if (cageIsDrawn) {
                 for (unsigned int i = 0; 
                        i < (vertices.size()-1); ++i) {
                    painter.drawLine(vertices[i], vertices[i+1]);
                    painter.drawEllipse(vertices[i], VERTEX_RADIUS, 
                            VERTEX_RADIUS);
                }
                painter.drawLine(vertices.back(), 
                        vertices.front());
                painter.drawEllipse(vertices.back(), VERTEX_RADIUS, 
                        VERTEX_RADIUS);

            }
            break;
    }
}

void ImageView::mousePressEvent(QMouseEvent * event) {
    if (!isDrawing) {
        switch (getCurrentDrawingState()) {
            case ImageView::DrawingState::DRAW:
                if (!cageIsDrawn) {
                    if (Qt::LeftButton == event->button()) {
                        this->setMouseTracking(true);
                        isDrawing = true;
                        startPoint = endPoint = event->pos();
                    }
                }
                break;
            case ImageView::DrawingState::DRAG:
                if (Qt::LeftButton == event->button()) {
                    this->setMouseTracking(true);
                    isDrawing = true;
                    startPoint = endPoint = event->pos();
                    dragStart = startPoint;
                    chosenPointIndex = 
                        getChosenPointIndex(endPoint);
                }
                break;

        }
    }
}

void ImageView::mouseReleaseEvent(QMouseEvent * event) {
    if (isDrawing) {
        switch (getCurrentDrawingState()) {
            case ImageView::DrawingState::DRAW:
                if (!cageIsDrawn) {
                    if (Qt::LeftButton == event->button()) {
                        startPoint = endPoint;
                        endPoint = event->pos();
                        vertices.push_back(endPoint);
                    } else if (Qt::RightButton == event->button()) {
                        isDrawing = false;
                        cageIsDrawn = true;
                        drawingState = 
                            ImageView::DrawingState::DRAG;
                        this->setMouseTracking(false);
                        resetStartAndEndPoints();
                        update();
                    }

                }
                break;
            case ImageView::DrawingState::DRAG:
                if (chosenPointIndex != INVALID_INDEX) {
                    vertices[chosenPointIndex] = event->pos();
                    dragEnd = event->pos();
                    ImageWarpper warpper(&image, vertices);
                    warpper.warp(chosenPointIndex, 
                            dragEnd-dragStart);
                }
                isDrawing = false;
                this->setMouseTracking(false);
                resetStartAndEndPoints();
                update();
                
                break;
        }
    }

}

void ImageView::mouseMoveEvent(QMouseEvent * event) {
    if (isDrawing) {
        switch (getCurrentDrawingState()) {
            case ImageView::DrawingState::DRAW:
                endPoint = event->pos();
                update();
                break;
            case ImageView::DrawingState::DRAG:
                endPoint = event->pos();
                chosenPointIndex = getChosenPointIndex(
                        event->pos());
                if (chosenPointIndex != INVALID_INDEX) {
                    vertices[chosenPointIndex] = event->pos();
                }
                update();
                break;
        }
    }
}

void ImageView::setImage(QImage * image) {
    if (this->image != image) {
        if (this->image) {
            delete this->image;
            this->image = nullptr;
        }
        this->image = image;

        if (this->imageBak) {
            delete this->imageBak;
            this->imageBak = nullptr;
        }
        imageBak = new QImage();
        *imageBak = image->copy(0, 0, image->width(), 
                image->height());

    }
}

QPoint ImageView::getCenterPoint() const {
    return QPoint((this->width()-image->width())/2,
            (this->height()-image->height())/2);
}

ImageView::DrawingState ImageView::getCurrentDrawingState() const {
    return drawingState;
}

void ImageView::resetStartAndEndPoints() {
    startPoint.setX(-1);
    startPoint.setY(-1);
    endPoint.setX(-1);
    endPoint.setY(-1);
}

int ImageView::getChosenPointIndex(const QPoint &point) const {
    for (unsigned int i = 0; i < vertices.size(); ++i) {
        int squaredDistance = 
            (point.x()-vertices[i].x())*(point.x()-vertices[i].x()) 
            + (point.y()-vertices[i].y())*(point.y()-vertices[i].y());
        if (squaredDistance < VERTEX_RADIUS*VERTEX_RADIUS) {
            return i;
        }
    }
    return INVALID_INDEX;
}

std::vector<QPoint> ImageView::getVertices() {
    return this->vertices;
}

QImage * ImageView::getImage() {
    return this->image;
}

