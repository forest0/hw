#include "FixedBorderParameterizer.h"
#include <cassert>
#include "../../libs/Eigen/Dense"
#include "../../libs/Eigen/Sparse"
#include "../../libs/Eigen/SparseLU"
#include "../../utils/Logger.h"

FixedBorderParameterizer::FixedBorderParameterizer(Mesh3D * mesh) 
    : Parameterizer(mesh)
{

}

FixedBorderParameterizer::~FixedBorderParameterizer() {

}

std::vector<trimesh::vec3> FixedBorderParameterizer::parameterize()
    const {

    assert(mesh);
    const int totalVerticesAmount = mesh->num_of_vertex_list();
    assert(totalVerticesAmount > 3);

    std::vector<trimesh::vec3> parameterizedCoor;
    parameterizedCoor.reserve(totalVerticesAmount);

    Eigen::SparseMatrix<REAL> A(totalVerticesAmount,
            totalVerticesAmount);
    Eigen::MatrixX2f b = Eigen::MatrixX2f::Zero(
            totalVerticesAmount, 2);
    Eigen::MatrixX2f x;

    // find the max amount of neighbot for a vertex,
    //  to reverse enough space for sparse matrix A
    unsigned int maxNeighborAmount = 0;
    for (const auto &vert : *(mesh->get_vertex_list())) {
        if (vert->neighborIdx.size() > maxNeighborAmount) {
            maxNeighborAmount = vert->neighborIdx.size();
        }
    }
    A.reserve(Eigen::VectorXi::Constant(totalVerticesAmount,
                maxNeighborAmount+1));

    // construct coefficient matrix
    HE_vert * currentVert = nullptr;
    for (int i = 0; i < totalVerticesAmount; ++i) {
        A.insert(i, i) = 1;
        currentVert = mesh->get_vertex(i);
        if (!currentVert->isOnBoundary()) {
            for (const auto &neighborId : currentVert->neighborIdx) {
                A.insert(i,neighborId) = -getWeightIJ(i, neighborId);
            }
        }
    }
    A.makeCompressed();

    // construct b
    std::vector<HE_vert *> &orderedBoudaryVertices =
        mesh->orderedBoudaryVertices;
    std::vector<trimesh::vec3> parameterizedBorderCoor;
    parameterizeBorder(orderedBoudaryVertices,
            parameterizedBorderCoor);
    int id = 0;
    for (unsigned long i = 0; i < orderedBoudaryVertices.size(); ++i) {
        id = orderedBoudaryVertices[i]->id();
        b(id, 0) = parameterizedBorderCoor[i][0];
        b(id, 1) = parameterizedBorderCoor[i][1];
    }


    solveSparseEquation(A, b, x);

    // copy to return value
    for (int i = 0; i < totalVerticesAmount; ++i) {
        parameterizedCoor.push_back(
                trimesh::vec3(x(i,0), x(i, 1), 0.0f));
    }
    return parameterizedCoor;
}

void FixedBorderParameterizer::solveSparseEquation(
        const Eigen::SparseMatrix<REAL> &A,
        const Eigen::MatrixX2f &b,
        Eigen::MatrixX2f &x) const {


    typedef Eigen::SparseLU<Eigen::SparseMatrix<REAL>> SolverType;
    SolverType solver;
    solver.compute(A);

    if(solver.info() != Eigen::Success) {
        // decomposition failed
        Logger::e("decomposition failed\n");
        return;
    }
    x = solver.solve(b);
    if(solver.info() != Eigen::Success) {
        // solving failed
        Logger::e("solving failed\n");
        return;
    }
}

// map border vertices to a unit square
void FixedBorderParameterizer::parameterizeBorder(
        const std::vector<HE_vert *> orderedBoudaryVertices,
        std::vector<trimesh::vec3> & parameterizedBorderCoor) const {
    REAL totalBoundaryLength = mesh->getTotalBoundaryLength();
    const REAL EPSILON = 1e-6;
    assert(totalBoundaryLength > EPSILON);

    REAL sum = 0.0f;
    REAL rate = 0.0f;
    const int boundaryVerticesAmount = orderedBoudaryVertices.size();
    HE_vert *current = orderedBoudaryVertices[0];
    HE_vert *next = orderedBoudaryVertices[0];

    for (int i = 0; i < boundaryVerticesAmount; ++i) {
        sum += (next->position() - current->position()).length();
        rate = sum / totalBoundaryLength;

        assert((rate > -EPSILON) && (rate < 1+EPSILON));

        if (rate < 0.25f) {
            parameterizedBorderCoor.push_back(
                    trimesh::vec3(4.0f * rate, 0.0f, 0.0f));
        } else if (rate < 0.5f) {
            parameterizedBorderCoor.push_back(
                    trimesh::vec3(0.25f, 4.0f * rate - 1.0f, 0.0f));
        } else if (rate < 0.75f) {
            parameterizedBorderCoor.push_back(
                    trimesh::vec3(-4.0f * rate + 3, 1.0f, 0.0f));
        } else {
            parameterizedBorderCoor.push_back(
                    trimesh::vec3(0, -4.0f * rate + 4, 0.0f));
        }
        current = next;
        next = orderedBoudaryVertices[i+1%boundaryVerticesAmount];
    }
    
}
REAL FixedBorderParameterizer::getWeightIJ(int i, int j) const {
    assert(mesh);
    return getWeightIJ(mesh->get_vertex(i), mesh->get_vertex(j));
}
