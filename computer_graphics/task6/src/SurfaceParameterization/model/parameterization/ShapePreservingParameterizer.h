#ifndef SHAPEPRESERVINGPARAMETERIZER_H
#define SHAPEPRESERVINGPARAMETERIZER_H

#include "FixedBorderParameterizer.h"

class ShapePreservingParameterizer : public FixedBorderParameterizer {

public:
    ShapePreservingParameterizer(Mesh3D *mesh);
    virtual ~ShapePreservingParameterizer();

    virtual REAL getWeightIJ(HE_vert *vertI, HE_vert *vertJ) const;


private:
    
};

#endif /* SHAPEPRESERVINGPARAMETERIZER_H */
