#include "DoDrawPlayer.h"
#include "core.drawing/view/ImageDrawingView.h"

namespace Narradia {
    void DoDrawPlayer(TileInfo tile_info) {
        if (tile_info.col == 5 && tile_info.row == 5)
            ImageDrawingView::Get()->DrawImage(
                "Player", {tile_info.col * tile_info.tile_width,
                           tile_info.row * tile_info.tile_height,
                           tile_info.tile_width, tile_info.tile_height});
    }
}