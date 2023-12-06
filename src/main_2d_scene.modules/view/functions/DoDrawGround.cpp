#include "DoDrawGround.h"
#include "core.render/view/Renderer2DImagesView.h"
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

        if (ground == "GroundGrass") {
            auto vary_index = (tile_info.map_x * tile_info.map_y) % 3;
            ground = "GroundGrass_" + std::to_string(vary_index);
        }
        
        Renderer2DImagesView::Get()->DrawImage(
            ground, tile_info.rid_ground,
            {tile_info.col * tile_info.tile_width,
             tile_info.row * tile_info.tile_height, tile_info.tile_width,
             tile_info.tile_height});

        if (SDL_GetTicks() < tile_info.tile->tile_effect().ticks_started + 800) {
        Renderer2DImagesView::Get()->DrawImage(
            tile_info.tile->tile_effect().type, tile_info.rid_ground,
            {tile_info.col * tile_info.tile_width,
             tile_info.row * tile_info.tile_height, tile_info.tile_width,
             tile_info.tile_height});
        }
    }
}
