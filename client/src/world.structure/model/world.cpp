#include "world.h"
#include "fileio/model/MapLoader.h"
namespace Narradia
{
    /**
     Initalizes and generates a complete MapArea.
    */
    World::World() {
        MapLoader::Get()->LoadWorldMapFromFile(curr_map_area_);
    }
}
