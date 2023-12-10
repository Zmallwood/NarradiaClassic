#include "draw_tile_symbols.h"
#include "core.render/view/command/draw_tile.h"
#include "main_scene.modules/model/mob_targeting_module.h"
#include "main_scene.modules/model/tile_hovering_module.h"
#include "world.actors/model/player.h"
namespace Narradia {
  void DrawTileSymbols(std::shared_ptr<Tile> tile, Point coord) {
    auto player_pos = Player::Get()->position().GetXZ().ToIntPoint();
    if (SDL_GetTicks() <
            Player::Get()->ticks_ulti_skill_start() + Player::Get()->ulti_skill_duration() &&
        Player::Get()->ticks_ulti_skill_start() != 0 && coord.x == player_pos.x &&
        coord.y == player_pos.y) {
      DrawTile("TilePlayerUltiSkill", tile->rid());
    }
    else if (MobTargetingModule::Get()->targeted_mob() == tile->mob() && tile->mob() != nullptr) {
      DrawTile("TileTargetedMob", tile->rid());
    }
    else if (SDL_GetTicks() < tile->tile_effect().ticks_started + 800) {
      DrawTile(tile->tile_effect().type, tile->rid());
    }
    else {
      auto hovered_tile = TileHoveringModule::Get()->hovered_tile();
      if (hovered_tile.x == coord.x && hovered_tile.y == coord.y) {
        DrawTile("TileHovered", tile->rid());
      }
    }
  }
}
