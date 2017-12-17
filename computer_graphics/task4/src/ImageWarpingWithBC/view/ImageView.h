#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QtWidgets/QWidget>
#include <QtGui/QImage>
#include <vector>


class ImageView : public QWidget {
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = nullptr);
    virtual ~ImageView();
    void setImage(QImage *image);

    enum class DrawingState {
        DRAW,
        DRAG
    };

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:

private:
    QPoint getCenterPoint() const;
    DrawingState getCurrentDrawingState() const;
    void resetStartAndEndPoints();
    int getChosenPointIndex(const QPoint &point) const;

private:
    QImage *image;
    QImage *imageBak;

    QPoint startPoint;
    QPoint endPoint;

    DrawingState drawingState;

    std::vector<QPoint> vertices;
    std::vector<QPoint> traces;

    bool isDrawing;
    bool cageIsDrawn;

    const int VERTEX_RADIUS = 5;
    const int INVALID_INDEX = -1;

    int chosenPointIndex;
};

#endif // IMAGEVIEW_H
