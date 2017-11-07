#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <QtCore/QPoint>
#include <QtGui/QImage>

/* some utility functions
 */
class Utils {
    public:
        static std::string getCurrentTimeString();
        static std::vector<std::pair<QPoint, QPoint>> getControlPoints();
        static void showImage(QImage *image);
        static void printControlPoints(
            const std::vector<std::pair<QPoint, QPoint>> &controlPoints);
        static void printPoint(const QPoint &point);
};

#endif
