#include "map_generator.h"
#include "command/calc_normals.h"
#include "command/generate_elevation.h"
#include "command/generate_grass.h"
#include "command/generate_ground_color.h"
#include "command/generate_mobs.h"
#include "command/generate_objects.h"
#include "command/generate_water.h"
#include "command/generate_desert.h"
#include "command/generate_snow.h"
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
        GenerateElevation(map_area);
        //GenerateObjects(map_area);
        GenerateMobs(map_area);
        //GenerateGroundColor(map_area);
        CalcNormals(map_area);
    }
}
