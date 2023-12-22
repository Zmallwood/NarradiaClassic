#include "tile_calc.h"
#include "conf/model/constants.h"
#include "world-structure/model/world.h"
namespace Narradia
{
    Point3F CalcTileNormal(Point3F v0, Point3F v1, Point3F v2) {
        auto point0 = glm::vec3(v0.x, v0.y, v0.z);
        auto point1 = glm::vec3(v1.x, v1.y, v1.z);
        auto Point2 = glm::vec3(v2.x, v2.y, v2.z);
        auto vector0 = point1 - point0;
        auto vector1 = Point2 - point0;
        auto vector2 = glm::cross(vector0, vector1);
        auto normal_gl = glm::normalize(vector2);
        return {-normal_gl.x, -normal_gl.y - normal_gl.z};
    }
}
