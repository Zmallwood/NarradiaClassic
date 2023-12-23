#include "draw_player.h"
#include "conf/model/constants.h"
#include "core-render-models/view/command/draw_model.h"
#include "world-actors/model/player.h"
namespace Narradia
{
   void DrawPlayer() {
      auto map_area = World::get()->CurrMapArea();
      auto curr_map_location = Player::get()->world_location();
      auto tile_size = kTileSize;
      auto map_offset_x = curr_map_location.x * map_area->GetWidth() * tile_size;
      auto map_offset_y = curr_map_location.y * map_area->GetHeight() * tile_size;
      auto player_space_coord = Player::get()->position().Multiply(kTileSize);
      player_space_coord.x += map_offset_x;
      player_space_coord.z += map_offset_y;
      auto player_map_coord = Player::get()->position().GetXZ().ToIntPoint();
      auto tile_average_elevation = CalcTileAverageElevation(player_map_coord);
      player_space_coord.y += tile_average_elevation;
      auto ms_anim_time = 0.0f;
      if (Player::get()->IsMoving())
         ms_anim_time = SDL_GetTicks();
      DrawModel(
          "Player2", ms_anim_time, player_space_coord, Player::get()->facing_angle_deg() + 180.0f,
          0.6f);
   }
}
