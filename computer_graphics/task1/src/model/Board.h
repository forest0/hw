#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <QtCore/QObject>
#include "Constants.h"
#include "figures/Figure.h"

/* core model of GraffitiBoard
 * 
 *     mainly to store the figures created by user
 *     
 *     inherit from QObject to use its signal-slots mechanism
 */
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
    std::vector<Figure *>* shownFigures;   // figures shown on the boardView
    std::vector<Figure *>* deletedFigures; // figures delete by click undo
    void moveFigureToShownFigures(Figure *figure);
    void moveFigureToDeletedFigures(Figure *figure);
};

#endif
