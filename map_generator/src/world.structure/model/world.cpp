#include "world.h"
#include "world.generation/model/map_generator.h"
namespace Narradia
{
    /**
     Initalizes and generates a complete MapArea.
    */
    World::World() {
        curr_map_area_ = std::make_shared<MapArea>();
        MapGenerator::get()->GenerateMapArea(curr_map_area_);
    }
}
