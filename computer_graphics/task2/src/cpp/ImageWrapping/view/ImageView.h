#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QtWidgets/QDialog>
#include <QtGui/QImage>
#include <QtGui/QPaintEvent>
#include <QtGui/QMouseEvent>

class ImageView : public QDialog {
    Q_OBJECT
    public:
        explicit ImageView(QWidget *parent = nullptr);
        ~ImageView();
        void setImage(QImage *image);
        QImage * getImage() const;
        std::vector<std::pair<QPoint, QPoint>> getControlPoints() const;
        void clearControlPoints();

    signals:

    protected:
        void paintEvent(QPaintEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    public slots:

    private:
        void resetStartAndEndPoints();
        void addControlPointPair(const std::pair<QPoint, QPoint> &pair);
        void drawControlPoints(QPainter *painter);
        QPoint getCenterPoint() const;

    private:
        QImage *image;
        std::vector<std::pair<QPoint, QPoint>> controlPoints;
        bool isDrawing;
        QPoint startPoint;
        QPoint endPoint;

};

#endif // IMAGEVIEW_H
