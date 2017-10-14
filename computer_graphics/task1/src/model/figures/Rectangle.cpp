#include "Rectangle.h"

Rectangle::Rectangle() :
    Figure(), QRect()
{
    type = FigureType::rectangle;
}

Rectangle::Rectangle(const QPoint &topLeft, 
        const QPoint &bottomRight) :
    Figure(), QRect(topLeft, bottomRight)
{
    type = FigureType::rectangle;
}


Rectangle::Rectangle(const QPoint &topLeft, const QSize &size) :
    Figure(), QRect(topLeft, size)
{
    type = FigureType::rectangle;
}

Rectangle::Rectangle(int x, int y, int width, int height) :
    Figure(), QRect(x, y, width, height)
{
    type = FigureType::rectangle;
}

Rectangle::~Rectangle() {

}

void Rectangle::drawWith(QPainter *painter) const {
    painter->drawRect(*this);
}
