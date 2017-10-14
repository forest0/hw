#ifndef BOARD_H
#define BOARD_H

#include "Constants.h"

class Board {

    public:
        Board();
        void setFigureType(const FigureType &type);
        FigureType getFigureType() const;

    private:
        FigureType figureType;
};

#endif
