#include "view/MainWindow.h"
#include <QtWidgets/QApplication>

void test();
void testBC(const QPoint &point);

#include "view/ImageView.h"

int main(int argc, char *argv[]) {
   QApplication a(argc, argv);
   MainWindow w;
   w.show();

   return a.exec();
}


#include "core/model/Triangle.h"
#include <QtCore/QDebug>
#include <iostream>
#include "core/coordinates/BarycentricCoordinate.h"
#include "core/coordinates/WachspressCoordinate.h"

void test() {
    // test interal integer point
    // 
    Triangle triangle(cv::Point2f(0,3), 
            cv::Point2f(-44,0), 
            cv::Point2f(4,0));
    std::vector<QPoint> integerPoints = 
        triangle.getInternalIntegerPoints();
    for (const auto &point : integerPoints) {
        // qDebug() << point;
        testBC(point);
    }

    // testBC(QPoint(0,1));
    
}

void testBC(const QPoint &point) {
    // test WP coordinates
    static std::vector<QPointF> basePoints = {
        QPointF(-4,-5), QPointF(9,2), QPointF(5,8), QPointF(-50,5)
        // QPointF(0,3), QPointF(0,0), QPointF(4,0)
        // QPointF(0,3), QPointF(0,0), QPointF(4,0), QPointF(3,-1)
    };
    BarycentricCoordinate *coordinate = new WachspressCoordinate(
            basePoints);

    QPointF originPoint(point);
    // QPointF originPoint(2,1); // w = [1/6, 1/3, 1/2]
    qDebug() << "originPoint: " << originPoint;
    std::vector<double> bc = coordinate->getCoordinateOf(originPoint); 

    QPointF fitPoint(0.0f,0.0f);
    for (unsigned int i = 0; i < basePoints.size(); ++i) {
        fitPoint += bc[i]*basePoints[i];
    }
    qDebug() << "fitPoint: " << fitPoint;
    
    QPointF delta = fitPoint - originPoint;
    qDebug() << "bias: " << delta;
    
    delete coordinate;

}
