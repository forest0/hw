#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <QtCore/QObject>
#include "Constants.h"
#include "model/figures/Figure.h"

class Board : public QObject {

    Q_OBJECT

public:
    Board();
    ~Board();
    void setCurrentDrawingType(FigureType type);
    FigureType getCurrentDrawingType() const;
    std::vector<Figure *>* getShownFigures() const;
    std::vector<Figure *>* getDeletedFigures() const;
    void addFigure(Figure *figure);

public slots:
    void popBackFromShownFigures();
    void popBackFromDeletedFigures();

signals:
    void shownFiguresAmountChange(unsigned int cuttentAmount);
    void deletedFiguresAmountChange(unsigned int cuttentAmount);

private:
    FigureType currentDrawingType;
    std::vector<Figure *>* shownFigures;  // for undo
    std::vector<Figure *>* deletedFigures; // for redo
    void moveFigureToShownFigures(Figure *figure);
    void moveFigureToDeletedFigures(Figure *figure);
};

#endif
