#include "draw_player.h"
#include "conf/model/configuration.h"
#include "core.render/view/renderer_models_view.h"
#include "world.actors/model/player.h"

namespace Narradia {
  void DrawPlayer() {
    auto player_space_coord = Player::Get()->position().Multiply(kTileSize);
    RendererModelsView::Get()->DrawModel(
        "Player2", 0.0f, player_space_coord, Player::Get()->facing_angle_deg() + 180.0f, 0.6f);
  }
}
