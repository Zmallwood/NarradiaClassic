#include "map_generator.h"
#include "cmd/calc_normals.h"
#include "cmd/generate_elevation.h"
#include "cmd/generate_grass.h"
#include "cmd/generate_ground_color.h"
#include "cmd/generate_mobs.h"
#include "cmd/generate_objects.h"
#include "cmd/generate_water.h"
#include "cmd/generate_desert.h"
#include "cmd/generate_snow.h"
namespace Narradia
{
    /**
     Generate all terrain and content for a MapArea.
    */
    void MapGenerator::GenerateMapArea(std::shared_ptr<MapArea> map_area) {
        GenerateGrass(map_area);
        //GenerateDesert(map_area);
        //GenerateWater(map_area);
        //GenerateSnow(map_area);
        //GenerateElevation(map_area);
        GenerateObjects(map_area);
        GenerateMobs(map_area);
        GenerateGroundColor(map_area);
        CalcNormals(map_area);
    }
}
