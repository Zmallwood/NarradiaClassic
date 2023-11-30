#include "DoDrawTileSymbols.h"
#include "core.drawing/view/ImageDrawingView.h"
#include "main_scene.modules/model/TileHoveringModule.h"
#include "world.structure/model/Tile.h"

namespace Narradia {
    void DoDrawTileSymbols(TileInfo tile_info) {
        auto hovered_tile = TileHoveringModule::Get()->hovered_tile();

        if (tile_info.map_x == hovered_tile.x &&
            tile_info.map_y == hovered_tile.y) {
            ImageDrawingView::Get()->DrawImage(
                "HoveredTile", {tile_info.col * tile_info.tile_width,
                                tile_info.row * tile_info.tile_height,
                                tile_info.tile_width, tile_info.tile_height});
        }
    }
}