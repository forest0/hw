#include "Board.h"

Board::Board() 
    : figureType(FigureType::freeDraw)
{

}

void Board::setFigureType(const FigureType &type) {
    this->figureType = type;
}

FigureType Board::getFigureType() const {
    return this->figureType;
} 
