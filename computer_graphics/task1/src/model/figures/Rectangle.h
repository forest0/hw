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
        ~Rectangle();
        void drawWith(QPainter *painter) const override;
    private:
};

#endif
