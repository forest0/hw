#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include "BoardView.h"
#include "../model/figures/Line.h"
#include "../model/figures/FreeDraw.h"
#include "../model/figures/Rectangle.h"
#include "../model/figures/Ellipse.h"
#include "../model/figures/Polygon.h"

BoardView::BoardView(QWidget *parent) :
    QWidget(parent),
    startPoint(), endPoint(),
    board(new Board()),
    traces()
{
    isDrawing = false;

    connect(board, &Board::shownFiguresAmountChange,
            this, &BoardView::onShownFiguresAmountChange);
    connect(board, &Board::deletedFiguresAmountChange,
            this, &BoardView::onDeletedFiguresAmountChange);
}

BoardView::~BoardView() {
    delete board;
}

void BoardView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    for (const auto &item : *(board->getShownFigures())) {
        item->drawWith(&painter);
    }
    switch (board->getCurrentDrawingType()) {
        case FigureType::line:
            painter.drawLine(QLine(startPoint, endPoint));
            break;
        case FigureType::ellipse:
            painter.drawEllipse(QRect(startPoint, endPoint));
            break;
        case FigureType::rectangle:
            painter.drawRect(QRect(startPoint, endPoint));
            break;
        case FigureType::polygon:
            for (int i=0; i < traces.size()-1; ++i) {
                painter.drawLine(traces[i], traces[i+1]);
            }
            painter.drawLine(startPoint, endPoint);
            break;
        case FigureType::freeDraw:
            painter.drawLines(traces);
            break;
    }
}

void BoardView::mousePressEvent(QMouseEvent *event) {
    if (!isDrawing) {
        switch (board->getCurrentDrawingType()) {
            case FigureType::line:
            case FigureType::rectangle:
            case FigureType::ellipse:
                if (Qt::LeftButton == event->button()) {
                    isDrawing = true;
                    startPoint = event->pos();
                }
                break;
            case FigureType::polygon:
                if (Qt::LeftButton == event->button()) {
                    this->setMouseTracking(true);
                    isDrawing = true;
                    startPoint = endPoint = event->pos();
                }
                break;
            case FigureType::freeDraw:
                if (Qt::LeftButton == event->button()) {
                    isDrawing = true;
                    traces.push_back(event->pos());
                }
                break;
        }
    }
}

void BoardView::mouseReleaseEvent(QMouseEvent *event) {
    if (isDrawing) {
        switch (board->getCurrentDrawingType()) {
            case FigureType::line:
                if (Qt::LeftButton == event->button()) {
                    isDrawing = false;
                    endPoint = event->pos();
                    board->addFigure(new Line(startPoint, endPoint));
                    resetStartAndEndPoints();
                }
                break;
            case FigureType::ellipse:
                if (Qt::LeftButton == event->button()) {
                    isDrawing = false;
                    endPoint = event->pos();
                    board->addFigure(new Ellipse(startPoint, endPoint));
                    resetStartAndEndPoints();
                }
                break;
            case FigureType::rectangle:
                if (Qt::LeftButton == event->button()) {
                    isDrawing = false;
                    endPoint = event->pos();
                    board->addFigure(new Rectangle(startPoint, endPoint));
                    resetStartAndEndPoints();
                }
                break;
            case FigureType::polygon:
                if (Qt::LeftButton == event->button()) {
                    startPoint = endPoint;
                    endPoint = event->pos();
                    traces.push_back(endPoint);
                } else if (Qt::RightButton == event->button()) {
                    isDrawing = false;
                    board->addFigure(new Polygon(traces));
                    resetStartAndEndPoints();
                    this->setMouseTracking(false);
                    traces.clear();
                }
                break;
            case FigureType::freeDraw:
                if (Qt::LeftButton == event->button()) {
                    isDrawing = false;
                    board->addFigure(new FreeDraw(traces));
                    traces.clear();
                    resetStartAndEndPoints();
                }
                break;
        }
        // update();
    }

}

void BoardView::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing) {
        switch (board->getCurrentDrawingType()) {
            case FigureType::line:
            case FigureType::rectangle:
            case FigureType::ellipse:
            case FigureType::polygon:
                endPoint = event->pos();
                update();
                break;
            case FigureType::freeDraw:
                traces.push_back(event->pos());
                update();
                break;
        }
    }
}

Board * BoardView::getBoard() const {
    return this->board;
}

void BoardView::onShownFiguresAmountChange(
        unsigned int currentAmount) {

    update();
}

void BoardView::onDeletedFiguresAmountChange(
        unsigned int currentAmount) {
    update();

}

void BoardView::resetStartAndEndPoints() {
    startPoint.setX(0);
    startPoint.setY(0);
    endPoint.setX(0);
    endPoint.setY(0);
}
