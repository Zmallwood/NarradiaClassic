#include "tile_calc.h"
#include "conf/model/constants.h"
#include "world.structure/model/world.h"
namespace Narradia
{
    float CalcTileAverageElevation(Point coord) {
        auto map_area = World::get()->curr_map_area();
        auto elev00 = map_area->GetTile(coord.x, coord.y)->elevation() * kElevAmount;
        auto elev10 = elev00;
        auto elev11 = elev00;
        auto elev01 = elev00;
        auto coord10 = Point{coord.x + 1, coord.y};
        auto coord11 = Point{coord.x + 1, coord.y + 1};
        auto coord01 = Point{coord.x, coord.y + 1};
        if (map_area->IsInsideMap(coord10))
            elev10 = map_area->GetTile(coord10)->elevation() * kElevAmount;
        if (map_area->IsInsideMap(coord11))
            elev11 = map_area->GetTile(coord11)->elevation() * kElevAmount;
        if (map_area->IsInsideMap(coord01))
            elev01 = map_area->GetTile(coord01)->elevation() * kElevAmount;
        return (elev00 + elev10 + elev11 + elev01) / 4.0f;
    }

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
