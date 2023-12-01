#include "DoDrawGround.h"
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
    }
}
