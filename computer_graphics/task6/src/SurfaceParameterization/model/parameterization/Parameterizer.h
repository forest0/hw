#ifndef PARAMETERIZER_H
#define PARAMETERIZER_H

#include <vector>
#include "../HE_mesh/Vec.h"
#include "../HE_mesh/Mesh3D.h"

// parameterizer abstract interface
class Parameterizer {

public:
    Parameterizer(Mesh3D *mesh);
    virtual ~Parameterizer();

    // parameterize a 3D mesh, return 2D coordinates
    virtual std::vector<trimesh::vec3> parameterize() const = 0;

protected:
    Mesh3D * mesh;

private:
    
};

enum class ParameterizationMethod {
    UNIFORM = 0,
    WEIGHTED_LEAST_SQUARES,
    SHAPE_PRESERVING
};

#endif /* PARAMETERIZER_H */
