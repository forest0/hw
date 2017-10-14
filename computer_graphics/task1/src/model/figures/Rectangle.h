#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Figure.h"
#include <QtCore/QPoint>
#include <QtCore/QRect>

class Rectangle : public Figure, public QRect {
    public:
        Rectangle();
        Rectangle(const QPoint &topLeft, 
                const QPoint &bottomRight);
        Rectangle(const QPoint & topLeft, const QSize & size);
        Rectangle(int x, int y, int width, int height);
        ~Rectangle();
        void drawWith(QPainter *painter) const override;
    private:
};

#endif
