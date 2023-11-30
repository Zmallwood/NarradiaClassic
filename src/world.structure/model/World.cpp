#include "World.h"
#include "world.generation/model/MapGenerator.h"

namespace Narradia {
    World::World() {
        curr_map_area_ = std::make_shared<MapArea>();
        MapGenerator::Get()->GenerateMapArea(curr_map_area_);
    }
}