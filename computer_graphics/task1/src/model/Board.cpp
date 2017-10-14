#include "Board.h"
#include "../tools/Log.h"
#include "../tools/Utils.h"

Board::Board() : 
    QObject(),
    currentDrawingType(FigureType::freeDraw),
      shownFigures(new std::vector<Figure *>()),
      deletedFigures(new std::vector<Figure *>())
{
}

Board::~Board() {
    for (const auto &item : *deletedFigures) {
        delete item;
    }
    for (const auto &item : *shownFigures) {
        delete item;
    }
    delete deletedFigures;
    delete shownFigures;
}

void Board::setCurrentDrawingType(FigureType type) {
    this->currentDrawingType = type;
}

FigureType Board::getCurrentDrawingType() const {
    return this->currentDrawingType;
}
std::vector<Figure *>* Board::getShownFigures() const {
    return this->shownFigures;
}

std::vector<Figure *>* Board::getDeletedFigures() const {
    return this->deletedFigures;
}

void Board::addFigure(Figure *figure) {
    moveFigureToShownFigures(figure);
}

void Board::popBackFromShownFigures() {
    if (!shownFigures->empty()) {
        Figure *figure = shownFigures->back();
        shownFigures->pop_back();
        moveFigureToDeletedFigures(figure);
        emit shownFiguresAmountChange(shownFigures->size());
    } else {
        Log::e("shownFigures is empty, can not pop");
    }
}
void Board::popBackFromDeletedFigures() {
    if (!deletedFigures->empty()) {
        Figure *figure = deletedFigures->back();
        deletedFigures->pop_back();
        moveFigureToShownFigures(figure);
        emit deletedFiguresAmountChange(deletedFigures->size());
    } else {
        Log::e("deletedFigures is empty, can not pop");
    }
}

void Board::moveFigureToShownFigures(Figure *figure) {
    shownFigures->push_back(figure);
    emit shownFiguresAmountChange(shownFigures->size());
}

void Board::moveFigureToDeletedFigures(Figure *figure) {
    deletedFigures->push_back(figure);
    emit deletedFiguresAmountChange(deletedFigures->size());
}
