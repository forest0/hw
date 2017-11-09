#ifndef RBFMAPPER_H
#define RBFMAPPER_H

#include "Mapper.h"
#include "Eigen/Dense"

class RBFMapper : public Mapper {
    public:
        explicit RBFMapper(
                const std::vector<std::pair<QPoint, QPoint>> &controlPoints);
        ~RBFMapper();
        QPoint map(const QPoint &point) const;

    private:
        double distance(const QPoint &pointA, const QPoint &pointB) const;
        double fi_func(const QPoint &p, int idx) const;
        void calculate_ri();
        void init_A();
        void init_b();
        void calculate_alphai();
    
    private:
        std::vector<QPoint> headOfControlPoints;
        std::vector<QPoint> tailOfControlPoints;
        std::vector<double> ri;
        double u;
        Eigen::MatrixXd A;
        Eigen::MatrixX2d b;
        Eigen::MatrixX2d alphai;
};


#endif /* end of include guard: RBFMAPPER_H */
