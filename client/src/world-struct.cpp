#if 1
#include "world-struct.h"
#include "actors.h"
#include "conf.h"
#include "world_map_loader.h"
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

   // WorldArea
#if 1
   WorldArea::WorldArea(int width, int height)
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
   std::shared_ptr<Tile> WorldArea::GetTile(int x, int y)
   {
      try
      {
         return tiles_.at(x).at(y);
      }
      catch (std::exception &e)
      {
         throw std::runtime_error("Tried to access tile with an invalid coordinate.");
      }
   }
   std::shared_ptr<Tile> WorldArea::GetTile(Point coord)
   {
      return GetTile(coord.x, coord.y);
   }
   bool WorldArea::IsInsideMap(Point coord)
   {
      return coord.x < tiles_.size() && coord.y < tiles_.at(0).size();
   }
   int WorldArea::GetWidth()
   {
      return tiles_.size();
   }
   int WorldArea::GetHeight()
   {
      return tiles_.at(0).size();
   }
   void WorldArea::ClearAllRIDS()
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
      auto map_names = WorldMapLoader::get()->world_area_names();
      for (auto y = 0; y < world_height_; y++)
      {
         for (auto x = 0; x < world_width_; x++)
         {
            world_areas_[x][y] = nullptr;
            WorldMapLoader::get()->LoadWorldMapFromFile(world_areas_[x][y], map_names[x][y]);
         }
      }
   }
   auto World::CurrWorldArea() -> std::shared_ptr<WorldArea>
   {
      auto world_loc = Player::get()->world_location();
      return world_areas_[world_loc.x][world_loc.y];
   }
   auto World::WorldAreaAt(Point location) -> std::shared_ptr<WorldArea>
   {
      if (world_areas_.count(location.x) != 0)
         if (world_areas_.at(location.x).count(location.y) != 0)
            return world_areas_[location.x][location.y];
      return nullptr;
   }
#endif
}
