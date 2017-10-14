#ifndef FREEDRAW_H
#define FREEDRAW_H

#include "Figure.h"
#include <QtCore/QPoint>
#include <QtCore/QVector>

class FreeDraw : public Figure {
    public:
        FreeDraw(const QVector<QPoint> &points);
        ~FreeDraw();
        void drawWith(QPainter *painter) const override;
    private:
        QVector<QPoint> points;
};

#endif
