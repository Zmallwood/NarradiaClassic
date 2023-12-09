#include "DrawPlayer.h"
#include "core.render/view/RendererModelsView.h"
#include "world.actors/model/Player.h"
#include "conf/model/Configuration.h"

namespace Narradia
{
    void DrawPlayer() {
        auto player_space_coord = Player::Get()->position().Multiply(kTileSize);
        RendererModelsView::Get()->DrawModel("Player2", 0.0f, player_space_coord, 0.0f, 0.6f);
    }
}
