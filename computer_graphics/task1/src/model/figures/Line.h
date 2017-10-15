#ifndef LINE_H
#define LINE_H

#include "Figure.h"
#include <QtCore/QPoint>
#include <QtCore/QLine>

class Line : public Figure,  public QLine {
    public:
        Line();
        Line(const QPoint &point1, const QPoint &point2);
        ~Line();
        void drawWith(QPainter *painter) const override;

    private:
};

#endif
