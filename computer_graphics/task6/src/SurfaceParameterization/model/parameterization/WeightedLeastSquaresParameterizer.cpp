#include "WeightedLeastSquaresParameterizer.h"

WeightedLeastSquaresParameterizer::WeightedLeastSquaresParameterizer(
    Mesh3D * mesh) : FixedBorderParameterizer(mesh){

}

WeightedLeastSquaresParameterizer::~WeightedLeastSquaresParameterizer() {

}

REAL WeightedLeastSquaresParameterizer::getWeightIJ(
        HE_vert *vertI, HE_vert *vertJ) const {

    assert(vertI && vertJ);
    const REAL EPSILON = 1e-7;

    if (mesh->isNeighbors(vertI, vertJ)) {
        REAL sum = 0.0f;
        REAL disanceIJ = (vertI->position()-vertJ->position()).length();
        assert(disanceIJ > EPSILON);
        REAL wIJ = 1.0f / disanceIJ;
        REAL deltaDistance = 0.0f;
        for (const auto &neighborId : vertI->neighborIdx) {
            deltaDistance = (vertI->position() - 
                    mesh->get_vertex(neighborId)->position()).length();
            assert(disanceIJ > EPSILON);
            sum += 1 / deltaDistance;
        }
        assert(sum > EPSILON);
        return wIJ / sum;
    } else {
        return (REAL) 0;
    }
}
