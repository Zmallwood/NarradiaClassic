#include "DoDrawPlayer.h"
#include "common/system/functions/Utilities.h"
#include "core.render/view/Renderer2DImagesView.h"
#include "world.actors/model/Player.h"

namespace Narradia {
    void DoDrawPlayer(TileInfo tile_info) {
        static RenderId rid_player = Renderer2DImagesView::Get()->NewImage();
        if (tile_info.col == GetGridCenterX() &&
            tile_info.row == GetGridCenterY()) {
            if (SDL_GetTicks() < Player::Get()->ticks_ulti_skill_start() +
                                     Player::Get()->ulti_skill_duration() &&
                Player::Get()->ticks_ulti_skill_start() != 0) {
                Renderer2DImagesView::Get()->DrawImage(
                    "PlayerUltiSkillEffect", rid_player,
                    {GetGridCenterX() * tile_info.tile_width,
                     GetGridCenterY() * tile_info.tile_height,
                     tile_info.tile_width, tile_info.tile_height});
            }
            Renderer2DImagesView::Get()->DrawImage(
                "Player", rid_player,
                {GetGridCenterX() * tile_info.tile_width,
                 GetGridCenterY() * tile_info.tile_height, tile_info.tile_width,
                 tile_info.tile_height});
        }
    }
}
