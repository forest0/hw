#include "ShapePreservingParameterizer.h"

ShapePreservingParameterizer::ShapePreservingParameterizer(Mesh3D * mesh) 
    : FixedBorderParameterizer(mesh)
{

}

ShapePreservingParameterizer::~ShapePreservingParameterizer() {

}

REAL ShapePreservingParameterizer::getWeightIJ(HE_vert * vertI, HE_vert * vertJ) const {
    return 0.0f;
}

