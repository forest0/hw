#ifndef POLYGON_H
#define POLYGON_H

#include "Figure.h"
#include <vector>
#include <QtCore/QPoint>
#include <QtCore/QVector>
#include <QtGui/QPolygon>

class Polygon : public Figure {
    public:
        Polygon(const QVector<QPoint> &points);
        ~Polygon();
        void drawWith(QPainter *painter) const override;
    private:
        QVector<QPoint> points;
};

#endif
