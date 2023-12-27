#include "world.h"
#include "file_io/m/world_conf_reader.h"
#include "file_io/m/map_loader.h"
#include "world-actors/m/player.h"

namespace Narradia
{
   World::World()
   {
      world_width_ = WorldConfReader::get()->world_map_width();
      world_height_ = WorldConfReader::get()->world_map_height();
      auto map_names = WorldConfReader::get()->map_area_names();
      for (auto y = 0; y < world_height_; y++)
      {
         for (auto x = 0; x < world_width_; x++)
         {
            map_areas_[x][y] = nullptr;
            MapLoader::get()->LoadWorldMapFromFile(map_areas_[x][y], map_names[x][y]);
         }
      }
   }

   std::shared_ptr<MapArea> World::CurrMapArea()
   {
      auto world_loc = Player::get()->world_location();
      return map_areas_[world_loc.x][world_loc.y];
   }

   std::shared_ptr<MapArea> World::MapAreaAt(Point location)
   {
      if (map_areas_.count(location.x) != 0)
         if (map_areas_.at(location.x).count(location.y) != 0)
            return map_areas_[location.x][location.y];
      return nullptr;
   }
}
