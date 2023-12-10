#include "world.h"
#include "world.generation/model/map_generator.h"

namespace Narradia {
  /**
   Initalizes and generates a complete MapArea.
  */
  World::World() {
    curr_map_area_ = std::make_shared<MapArea>();
    MapGenerator::Get()->GenerateMapArea(curr_map_area_);
  }
}