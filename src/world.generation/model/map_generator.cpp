#include "map_generator.h"
#include "command/generate_grass.h"
#include "command/generate_mobs.h"
#include "command/generate_objects.h"
#include "command/generate_water.h"
namespace Narradia {
  /**
   Generate all terrain and content for a MapArea.
  */
  void MapGenerator::GenerateMapArea(std::shared_ptr<MapArea> map_area) {
    GenerateGrass(map_area);
    GenerateWater(map_area);
    GenerateObjects(map_area);
    GenerateMobs(map_area);
  }
}
