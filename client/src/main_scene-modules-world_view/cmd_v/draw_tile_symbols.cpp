#if 1
#include "draw_tile_symbols.h"
#include "render/cmd_v/draw_tile.h"
#include "main_scene-modules/mob_targeting_module.h"
#include "main_scene-modules/tile_hovering_module.h"
#include "actors/player.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   void DrawTileSymbols(std::shared_ptr<Tile> tile, Point coord)
   {
      auto player_pos = Player::get()->position().GetXZ().ToIntPoint();
      if (SDL_GetTicks() <
              Player::get()->ticks_ulti_skill_start() + Player::get()->ulti_skill_duration() &&
          Player::get()->ticks_ulti_skill_start() != 0 && coord.x == player_pos.x &&
          coord.y == player_pos.y)
      {
         DrawTile("TilePlayerUltiSkill", tile->rid());
      }
      else if (MobTargetingModule::get()->targeted_mob() == tile->mob() && tile->mob() != nullptr)
      {
         DrawTile("TileTargetedMob", tile->rid());
      }
      else if (SDL_GetTicks() < tile->tile_effect().ticks_started + 800)
      {
         DrawTile(tile->tile_effect().type, tile->rid());
      }
      else
      {
         auto hovered_tile = TileHoveringModule::get()->hovered_tile();
         if (hovered_tile.x == coord.x && hovered_tile.y == coord.y)
         {
            DrawTile("TileHovered", tile->rid());
         }
      }
   }
}
