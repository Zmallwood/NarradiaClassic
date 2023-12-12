#include "world.h"
#include "fileio/model/MapLoader.h"
#include "world.generation/model/map_generator.h"
namespace Narradia
{
    /**
     Initalizes and generates a complete MapArea.
    */
    World::World() {
        //curr_map_area_ = std::make_shared<MapArea>();
        // MapGenerator::Get()->GenerateMapArea(curr_map_area_);
        std::cout << "Load\n";
        MapLoader::Get()->LoadWorldMapFromFile(curr_map_area_);
        std::cout << "ground 00: " <<  curr_map_area_->GetTile(0,0)->ground() << std::endl;
    }
}
