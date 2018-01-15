#ifndef FIXEDBORDERPARAMETERIZER_H
#define FIXEDBORDERPARAMETERIZER_H

#include "Parameterizer.h"
#include "../../libs/Eigen/Sparse"

#define REAL float

class FixedBorderParameterizer : public Parameterizer {

public:
    FixedBorderParameterizer(Mesh3D *mesh);
    virtual ~FixedBorderParameterizer();

    virtual std::vector<trimesh::vec3> parameterize() const;

protected:
    virtual REAL getWeightIJ(int i, int j) const;
    virtual REAL getWeightIJ(HE_vert *vertI, HE_vert *vertJ) const = 0;

    void parameterizeBorder(
            const std::vector<HE_vert *> orderedBoudaryVertices,
            std::vector<trimesh::vec3> &parameterizedBorderCoor) const;

private:
    void solveSparseEquation(
            const Eigen::SparseMatrix<REAL> &A,
            const Eigen::MatrixX2f &b,
            Eigen::MatrixX2f &x) const;
};

// #undef REAL
#endif /* FIXEDBORDERPARAMETERIZER_H */
