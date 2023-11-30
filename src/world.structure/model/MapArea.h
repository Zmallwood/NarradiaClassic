#pragma once
#include "Tile.h"

namespace Narradia {

    class MapArea {
      public:
        MapArea();

        std::shared_ptr<Tile> GetTile(int x, int y);

      private:
        std::vector<std::vector<std::shared_ptr<Tile>>> tiles_;
    };
}