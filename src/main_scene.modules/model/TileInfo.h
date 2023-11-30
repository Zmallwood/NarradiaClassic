#pragma once

namespace Narradia {
    class Tile;

    class TileInfo {
      public:
        std::shared_ptr<Tile> tile;
        int map_x = -1;
        int map_y = -1;
        int col = -1;
        int row = -1;
        float tile_width = 0.0f;
        float tile_height = 0.0f;
    };
}