#ifndef UNIFORMPARAMETERIZER_H
#define UNIFORMPARAMETERIZER_H

#include "FixedBorderParameterizer.h"

class UniformParameterizer : public FixedBorderParameterizer {

public:
    UniformParameterizer(Mesh3D *mesh);
    virtual ~UniformParameterizer();

    REAL getWeightIJ(HE_vert *vertI, HE_vert *vertJ) const override;

private:
    
};

#endif /* UNIFORMPARAMETERIZER_H */
