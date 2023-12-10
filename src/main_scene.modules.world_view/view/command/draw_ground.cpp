#include "draw_ground.h"
#include "core.render/view/renderer_tiles_view.h"
#include "core.render/view/command/draw_tile.h"

namespace Narradia {
  void DrawGround(std::shared_ptr<Tile> tile, Point coord) {
    auto ground = tile->ground();
    if (ground == "GroundWater") {
      auto anim_index = ((SDL_GetTicks() + coord.x * coord.y) % 900) / 300;
      if (anim_index > 0)
        ground = "GroundWater_" + std::to_string(anim_index);
    }
    if (ground == "GroundGrass") {
      auto vary_index = (coord.x * coord.y) % 3;
      ground = "GroundGrass_" + std::to_string(vary_index);
    }
    DrawTile(ground, tile->rid());
  }
}
