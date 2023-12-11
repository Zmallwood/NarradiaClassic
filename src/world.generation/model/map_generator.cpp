#include "map_generator.h"
#include "command/generate_grass.h"
#include "command/generate_mobs.h"
#include "command/generate_objects.h"
#include "command/generate_water.h"
#include "command/generate_elevation.h"
#include "command/calc_normals.h"
namespace Narradia {
  /**
   Generate all terrain and content for a MapArea.
  */
  void MapGenerator::GenerateMapArea(std::shared_ptr<MapArea> map_area) {
    GenerateGrass(map_area);
    GenerateWater(map_area);
    GenerateElevation(map_area);
    GenerateObjects(map_area);
    GenerateMobs(map_area);
    CalcNormals(map_area);
  }
}
