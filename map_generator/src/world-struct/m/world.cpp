#include "world.h"
namespace Narradia
{
    /**
     Initalizes and generates a complete MapArea.
    */
    World::World() {
        curr_map_area_ = std::make_shared<MapArea>();
    }
}
