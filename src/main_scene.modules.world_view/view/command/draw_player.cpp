#include "draw_player.h"
#include "conf/model/conf.h"
#include "core.render/view/renderer_models_view.h"
#include "world.actors/model/player.h"
namespace Narradia {
  void DrawPlayer() {
    auto player_space_coord = Player::Get()->position().Multiply(kTileSize);
    auto player_map_coord = Player::Get()->position().GetXZ().ToIntPoint();
    auto tile_average_elevation = CalcTileAverageElevation(player_map_coord);
    player_space_coord.y += tile_average_elevation;
    auto ms_anim_time = 0.0f;
    if (Player::Get()->IsMoving())
      ms_anim_time = SDL_GetTicks();
    RendererModelsView::Get()->DrawModel(
        "Player2", ms_anim_time, player_space_coord, Player::Get()->facing_angle_deg() + 180.0f,
        0.6f);
  }
}
