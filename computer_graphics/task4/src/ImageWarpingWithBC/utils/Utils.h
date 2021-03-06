#ifndef UTILS_H
#define UTILS_H

#include <QtCore/QPointF>
#include <opencv2/core.hpp>
#include <vector>

class Utils {

public:
    Utils();
    virtual ~Utils();

    static QPointF cvPoint2f2QPointF(const cv::Point2f &point);
    static cv::Point2f qPointF2cvPoint2f(const QPointF &point);

    static bool isOnSameLine(const QPointF &point1, 
            const QPointF &point2, const QPointF &point3);

    static std::vector<double> getRandomBC(int dimension);


private:
    static void initSeed();
};

#endif /* UTILS_H */
