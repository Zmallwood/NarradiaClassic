#pragma once
#include "tile.h"
namespace Narradia
{
   class MapArea
   {
     public:
      MapArea(int width, int height);
      std::shared_ptr<Tile> GetTile(int x, int y);
      std::shared_ptr<Tile> GetTile(Point coord);
      bool IsInsideMap(Point coord);
      int GetWidth();
      int GetHeight();
      void ClearAllRIDS();

      auto mobs_mirror()
      {
         return mobs_mirror_;
      }

     private:
      std::vector<std::vector<std::shared_ptr<Tile>>> tiles_;
      std::shared_ptr<std::map<std::shared_ptr<Mob>, Point>> mobs_mirror_;
   };
}
