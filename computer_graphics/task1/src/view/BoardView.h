#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QtWidgets/QWidget>
#include "../model/Board.h"

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
    QVector<QPoint> traces;
};

#endif // BOARDVIEW_H
