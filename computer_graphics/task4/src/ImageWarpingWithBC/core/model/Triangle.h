#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <opencv2/core.hpp>
#include <vector>
#include <QtCore/QPoint>
#include <QtCore/QPointF>

class Triangle {

public:
    Triangle(const cv::Point2f &point1, const cv::Point2f &point2,
            const cv::Point2f &point3);
    Triangle(const QPointF &point1, const QPointF &point2,
            const QPointF &point3);
    std::vector<QPoint> getInternalIntegerPoints() const;
    double getArea() const;
    std::vector<cv::Point2f> getVerticesByXAscent() const;
    bool hasEdgePass(const QPointF &point) const;
    virtual ~Triangle();

private:
    cv::Point2f point1;
    cv::Point2f point2;
    cv::Point2f point3;

    /* calculate the integer points within a triangle which 
     * has a edge with undefined slope
     * 
     * param: idx is the point index, from 0 to 2
     * represent the point on which slope exists. 
     * 
     * return: the coverd integer points
     */
    std::vector<QPoint> getInternalIntegerPoints(int idx) const;
};

#endif /* TRIANGLE_H */
