#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Figure.h"
#include <QtCore/QPoint>

class Ellipse : public Figure {
    public:
        Ellipse(const QPoint &topLeft, const QPoint &bottomRight);
        ~Ellipse();
        void drawWith(QPainter *painter) const override;
    private:
        QPoint topLeft;
        QPoint bottomRight;
};

#endif
