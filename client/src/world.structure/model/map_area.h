#pragma once
#include "tile.h"
namespace Narradia
{
    /**
     Map object composed of a 2D grid of tiles and a mirror to
     facilitate/speedup access to all mob actors on the map.
    */
    class MapArea {
      public:
        MapArea();
        std::shared_ptr<Tile> GetTile(int x, int y);
        std::shared_ptr<Tile> GetTile(Point coord);
        bool IsInsideMap(Point coord);

        auto mobs_mirror() {
            return mobs_mirror_;
        }
      private:
        std::vector<std::vector<std::shared_ptr<Tile>>> tiles_;
        std::shared_ptr<std::map<std::shared_ptr<Mob>, Point>> mobs_mirror_;
    };
}
