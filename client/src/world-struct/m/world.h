#pragma once
#include "map_area.h"
namespace Narradia
{
   /**
    Top most object in the world map hierchical structure.
   */
   class World : public Singleton<World>
   {
     public:
      World();

      std::shared_ptr<MapArea> CurrMapArea();

      std::shared_ptr<MapArea> MapAreaAt(Point location);

      auto world_width()
      {
         return world_width_;
      }
      auto world_height()
      {
         return world_height_;
      }

      auto map_areas()
      {
         return map_areas_;
      }

     private:
      std::map<int, std::map<int, std::shared_ptr<MapArea>>> map_areas_;
      int world_width_ = -1;
      int world_height_ = -1;
   };
}
