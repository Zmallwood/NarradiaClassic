#include "world.h"
#include "fileio/model/MapLoader.h"
namespace Narradia
{
    /**
     Initalizes and generates a complete MapArea.
    */
    World::World() {
        MapLoader::get()->LoadWorldMapFromFile(curr_map_area_);
    }
}
