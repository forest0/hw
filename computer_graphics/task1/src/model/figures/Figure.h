#ifndef FIGURE_H
#define FIGURE_H

#include "Constants.h"
#include <QtGui/QPainter>

/* figure base type 
 */
class Figure {
    public:
        Figure();
        virtual ~Figure() = 0;
        virtual void drawWith(QPainter *) const = 0;
    protected: 
        // this field's type may add a limit for inheritance
        FigureType type;
};

#endif
