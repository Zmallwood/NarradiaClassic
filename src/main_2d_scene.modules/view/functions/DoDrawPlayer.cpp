#include "DoDrawPlayer.h"
#include "common/system/functions/Utilities.h"
#include "core.render/view/Renderer2DImagesView.h"

namespace Narradia {
    void DoDrawPlayer(TileInfo tile_info) {
        static RenderId rid_player = Renderer2DImagesView::Get()->NewImage();
        if (tile_info.col == GetGridCenterX() &&
            tile_info.row == GetGridCenterY()) {
            Renderer2DImagesView::Get()->DrawImage(
                "Player", rid_player,
                {GetGridCenterX() * tile_info.tile_width,
                 GetGridCenterY() * tile_info.tile_height, tile_info.tile_width,
                 tile_info.tile_height});
        }
    }
}
