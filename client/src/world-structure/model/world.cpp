#include "world.h"
#include "fileio/model/map_loader.h"
#include "fileio/model/world_conf_reader.h"
namespace Narradia
{
   /**
    Initalizes and generates a complete MapArea.
   */
   World::World() {
      world_width_ = WorldConfReader::get()->world_map_width();
      world_height_ = WorldConfReader::get()->world_map_height();
      for (auto y = 0; y < world_height_; y++) {
         for (auto x = 0; x < world_width_; x++) {
             map_areas_[x][y] = nullptr;
             MapLoader::get()->LoadWorldMapFromFile(map_areas_[x][y]);
         }
      }
   }
}
