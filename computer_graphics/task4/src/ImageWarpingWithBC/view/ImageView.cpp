#include "ImageView.h"
#include <QtGui/QPainter>
#include <QtCore/QPointF>
#include <QtGui/QMouseEvent>
#include <QtCore/QDebug>

ImageView::ImageView(QWidget *parent) : QWidget(parent),
    image(nullptr), imageBak(nullptr),
    startPoint(), endPoint(),
    drawingState(ImageView::DrawingState::DRAW),
    vertices(), traces(), isDrawing(false), cageIsDrawn(false),
    chosenPointIndex(-1)
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
        painter.drawImage(getCenterPoint(), *(this->image));
    }
    switch (getCurrentDrawingState()) {
        case ImageView::DrawingState::DRAW:
            if (!traces.empty()) {
                for (unsigned int i = 0; 
                        i < (traces.size()-1); ++i) {

                    painter.drawLine(traces[i], traces[i+1]);
                }
                if (cageIsDrawn) {
                    painter.drawLine(traces.back(), 
                            traces.front());
                }

            }
            if (!cageIsDrawn) {
                painter.drawLine(startPoint, endPoint);
            }
            break;
        case ImageView::DrawingState::DRAG:
            if (cageIsDrawn) {
                 for (unsigned int i = 0; 
                        i < (traces.size()-1); ++i) {
                    painter.drawLine(traces[i], traces[i+1]);
                    painter.drawEllipse(traces[i], VERTEX_RADIUS, 
                            VERTEX_RADIUS);
                }
                painter.drawLine(traces.back(), 
                        traces.front());
                painter.drawEllipse(traces.back(), VERTEX_RADIUS, 
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
                        traces.push_back(endPoint);
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
                    traces[chosenPointIndex] = event->pos();
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
                    traces[chosenPointIndex] = event->pos();
                }
                update();
                break;
        }
    }
}

void ImageView::setImage(QImage * image) {
    this->image = image;
    imageBak = new QImage();
    *imageBak = image->copy(0,0,image->width(), image->height());
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
    for (unsigned int i = 0; i < traces.size(); ++i) {
        int squaredDistance = 
            (point.x()-traces[i].x())*(point.x()-traces[i].x()) 
            + (point.y()-traces[i].y())*(point.y()-traces[i].y());
        if (squaredDistance < VERTEX_RADIUS*VERTEX_RADIUS) {
            return i;
        }
    }
    return INVALID_INDEX;
}

