#if 1
#include "world-struct.h"
#include "conf.h"
#include "world_map_loader.h"
#include "actors.h"
#endif

namespace Narradia
{
   // Object
#if 1
   Object::Object(std::string type)
       : type_(type)
   {
   }
#endif

   // Tile
#if 1
   void Tile::IncreaseElevation(float amount)
   {
      elevation_ += amount;
   }
#endif

   // MapArea
#if 1
   MapArea::MapArea(int width, int height)
       : mobs_mirror_(std::make_shared<std::map<std::shared_ptr<Mob>, Point>>())
   {
      for (auto x = 0; x < width; x++)
      {
         tiles_.push_back(std::vector<std::shared_ptr<Tile>>());
         for (auto y = 0; y < height; y++)
         {
            tiles_.at(x).push_back(std::make_shared<Tile>());
         }
      }
   }
   std::shared_ptr<Tile> MapArea::GetTile(int x, int y)
   {
      return tiles_.at(x).at(y);
   }
   std::shared_ptr<Tile> MapArea::GetTile(Point coord)
   {
      return GetTile(coord.x, coord.y);
   }
   bool MapArea::IsInsideMap(Point coord)
   {
      return coord.x < tiles_.size() && coord.y < tiles_.at(0).size();
   }
   int MapArea::GetWidth()
   {
      return tiles_.size();
   }
   int MapArea::GetHeight()
   {
      return tiles_.at(0).size();
   }
   void MapArea::ClearAllRIDS()
   {
      for (auto y = 0; y < GetHeight(); y++)
      {
         for (auto x = 0; x < GetWidth(); x++)
         {
            tiles_.at(x).at(y)->set_rid(0);
         }
      }
   }
#endif

   // World
#if 1
   World::World()
   {
      world_width_ = WorldMapLoader::get()->world_map_width();
      world_height_ = WorldMapLoader::get()->world_map_height();
      auto map_names = WorldMapLoader::get()->map_area_names();
      for (auto y = 0; y < world_height_; y++)
      {
         for (auto x = 0; x < world_width_; x++)
         {
            map_areas_[x][y] = nullptr;
            WorldMapLoader::get()->LoadWorldMapFromFile(map_areas_[x][y], map_names[x][y]);
         }
      }
   }
   auto World::CurrMapArea() -> std::shared_ptr<MapArea>
   {
      auto world_loc = Player::get()->world_location();
      return map_areas_[world_loc.x][world_loc.y];
   }
   auto World::MapAreaAt(Point location) -> std::shared_ptr<MapArea>
   {
      if (map_areas_.count(location.x) != 0)
         if (map_areas_.at(location.x).count(location.y) != 0)
            return map_areas_[location.x][location.y];
      return nullptr;
   }
#endif
}
