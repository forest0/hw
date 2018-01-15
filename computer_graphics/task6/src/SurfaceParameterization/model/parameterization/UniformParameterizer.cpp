#include "UniformParameterizer.h"
#include <cassert>

UniformParameterizer::UniformParameterizer(Mesh3D * mesh) 
    : FixedBorderParameterizer(mesh)
{

}

UniformParameterizer::~UniformParameterizer() {

}



REAL UniformParameterizer::getWeightIJ(HE_vert * vertI, HE_vert * vertJ)
    const {
    assert(vertI && vertJ);

    if (mesh->isNeighbors(vertI, vertJ)) {
        int degree = vertI->degree();
        assert(degree > 0);
        return ((REAL) 1) / degree;
    } else {
        return (REAL) 0;
    }
}

