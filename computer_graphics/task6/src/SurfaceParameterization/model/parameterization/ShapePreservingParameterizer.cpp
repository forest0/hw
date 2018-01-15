#include "ShapePreservingParameterizer.h"
#include "../../libs/Eigen/Dense"

ShapePreservingParameterizer::ShapePreservingParameterizer(Mesh3D * mesh) 
    : FixedBorderParameterizer(mesh)
{

}

ShapePreservingParameterizer::~ShapePreservingParameterizer() {

}


REAL ShapePreservingParameterizer::getWeightIJ(HE_vert * x_i, HE_vert * x_j_k)
    const {

    const std::vector<size_t> *neighbors = &(x_i->neighborIdx);
    std::vector<trimesh::vec2> planars;
    bool isNeighbor = false;
    float angleSum = 0.0f;
    static const float PI = 3.1415926;
    int k = 0;

    /* 默认 neighbors 按逆时针序存储邻点*/
    /* 求出角度总和 */
    for (int i = 0 ; i < neighbors->size(); ++i) {
        size_t vertId = neighbors->at(i);
        size_t nextVertId = neighbors->at(0);
        if (i < neighbors->size() - 1){
            nextVertId = neighbors->at(i+1);
        }
        angleSum += trimesh::angle(
                mesh->get_vertex(vertId)->position() - x_i->position_,
                   mesh->get_vertex(nextVertId)->position() - x_i->position_);
        if(vertId == x_j_k->id_) {
           isNeighbor = true;
           k = i;
        }
    }
    if (!isNeighbor) return 0.0f;
    /* 计算仿射点坐标 */
    /* x_i 对应于 (0, 0)*/
    float angle = 0.0f;
    for (int i = 0; i<neighbors->size(); ++i) {
        size_t vertId = neighbors->at(i);
        size_t nextVertId = neighbors->at(0);

        if (i == 0) {
            planars.push_back(trimesh::vec2(
                trimesh::dist(x_i->position_, 
                mesh->get_vertex(vertId)->position()), 0));
        } else {
            if (i < neighbors->size() - 1) nextVertId = neighbors->at(i+1);

            angle += trimesh::angle(mesh->get_vertex(
                        vertId)->position() - x_i->position_,
                    mesh->get_vertex(nextVertId)->position() - x_i->position_);
            float distance = trimesh::dist(x_i->position_,
                    mesh->get_vertex(nextVertId)->position());
            float x = distance*std::cos(2*PI*angle/angleSum);
            float y = distance*std::sin(2*PI*angle/angleSum);
            planars.push_back(trimesh::vec2(x, y));
        }
    }

    float u_sum = 0.0f;
    /* 计算权重 */
    for (int i = 0; i < neighbors->size(); ++i) {
        float x0 = planars.at(i).at(0);
        float y0 = planars.at(i).at(1);
        bool find = false;
        for (int j = 0; j < neighbors->size() && !find; ++j) {
            int next = j + 1;
            if ( i == j || i == next) continue;
            if ( j == neighbors->size() -1 ) next = 0;
            float x1 = planars.at(j).at(0);
            float y1 = planars.at(j).at(1);
            float x2 = planars.at(next).at(0);
            float y2 = planars.at(next).at(1);

            /* 判断经过 点p和点pi的直线与线段 pj-pnext 相交*/
            /* 计算 uk,l */
            /* 解矩阵方程 */
            /* x0 x1 x2 0*/
            /* y0 y1 y2 0*/
            /* 1  1  1  1*/

            if ((y0*x1 - x0*y1) * (y0 * x2 - x0*y2) < -1e-07 
                    || ((y0 * x1 - x0*y1) <= 1e-06 
                        && (y0 * x1 - x0*y1) >= -1e-06)) {
                find = true;
                Eigen::Matrix3f A;
                A << x0, x1, x2,
                     y0, y1, y2,
                     1,  1,  1;
                Eigen::Vector3f b(0, 0, 1);
                Eigen::Vector3f x = A.colPivHouseholderQr().solve(b);
                if (k == i) {
                    u_sum += x[0];
                } else if (k == j) {
                    u_sum += x[1];
                } else if (k == next) {
                    u_sum += x[2];
                }
            }
        }
    }
    return 1.0f/neighbors->size()*u_sum;
}
