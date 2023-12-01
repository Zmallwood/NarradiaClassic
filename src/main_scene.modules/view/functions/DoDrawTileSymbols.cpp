#include "DoDrawTileSymbols.h"
#include "main_scene.modules/model/TileHoveringModule.h"
#include "world.structure/model/Tile.h"

namespace Narradia {
    void DoDrawTileSymbols(TileInfo tile_info) {
        auto hovered_tile = TileHoveringModule::Get()->hovered_tile();

        if (tile_info.map_x == hovered_tile.x &&
            tile_info.map_y == hovered_tile.y) {
        }
    }
}
