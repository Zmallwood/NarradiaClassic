#include "DoDrawGround.h"
#include "core.drawing/view/ImageDrawingView.h"
#include "world.structure/model/Tile.h"

namespace Narradia {
    void DoDrawGround(TileInfo tile_info) {

        auto ground = tile_info.tile->ground();

        if (ground == "GroundWater") {
            auto anim_index =
                ((SDL_GetTicks() + tile_info.map_x * tile_info.map_y) % 900) /
                300;

            if (anim_index > 0)
                ground = "GroundWater_" + std::to_string(anim_index);
        }

        ImageDrawingView::Get()->DrawImage(
            ground, {tile_info.col * tile_info.tile_width,
                     tile_info.row * tile_info.tile_height,
                     tile_info.tile_width, tile_info.tile_height});
    }
}