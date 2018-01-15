#ifndef WEIGHTEDLEASTSQUARESPARAMETERIZER_H
#define WEIGHTEDLEASTSQUARESPARAMETERIZER_H

#include "FixedBorderParameterizer.h"

class WeightedLeastSquaresParameterizer : public FixedBorderParameterizer{

public:
    WeightedLeastSquaresParameterizer(Mesh3D *mesh);
    virtual ~WeightedLeastSquaresParameterizer();

    virtual REAL getWeightIJ(HE_vert *vertI, HE_vert *vertJ) const override;

private:
    
};

#endif /* WEIGHTEDLEASTSQUARESPARAMETERIZER_H */
