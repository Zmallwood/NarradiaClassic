#include "world.h"
#include "fileio/model/map_loader.h"
#include "fileio/model/world_conf_reader.h"
namespace Narradia
{
   /**
    Initalizes and generates a complete MapArea.
   */
   World::World() {
      auto world_width = WorldConfReader::get()->world_map_width();
      auto world_height = WorldConfReader::get()->world_map_height();
      for (auto y = 0; y < world_height; y++) {
         for (auto x = 0; x < world_width; x++) {
             map_areas_[x][y] = nullptr;
             MapLoader::get()->LoadWorldMapFromFile(map_areas_[x][y]);
         }
      }
   }
}
