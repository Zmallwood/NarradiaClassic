#include "DoDrawObjects.h"
#include "core.drawing/view/ImageDrawingView.h"
#include "world.structure/model/Tile.h"

namespace Narradia {
    void DoDrawObjects(TileInfo tile_info) {
        if (tile_info.tile->object()) {
            if (tile_info.tile->object()->type() != "") {
                ImageDrawingView::Get()->DrawImage(
                    tile_info.tile->object()->type(),
                    {tile_info.col * tile_info.tile_width,
                     tile_info.row * tile_info.tile_height,
                     tile_info.tile_width, tile_info.tile_height});
            }
        }
    }
}