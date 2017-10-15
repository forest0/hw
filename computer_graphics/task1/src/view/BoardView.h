#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QtWidgets/QWidget>
#include "../model/Board.h"

/* core view of GraffitiBoard
 * 
 *      responsible for draw figures provided by Board
 *          and interact with user
 */
class BoardView : public QWidget
{
    Q_OBJECT

public:
    explicit BoardView(QWidget *parent = 0);
    ~BoardView();
    Board * getBoard() const;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void onShownFiguresAmountChange(unsigned int currentAmount);
    void onDeletedFiguresAmountChange(unsigned int currentAmount);


private:
    bool isDrawing;
    QPoint startPoint;
    QPoint endPoint;
    Board *board;
    void resetStartAndEndPoints();
    QVector<QPoint> traces;         // helper for record user's action
};

#endif // BOARDVIEW_H
