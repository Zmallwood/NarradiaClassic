#include "mob_movement_module.h"
#include "conf.world/model/mobs_conf.h"
#include "conf/model/constants.h"
#include "world.actors/model/player.h"
#include "world.structure/model/world.h"
namespace Narradia
{
   void MobMovementModule::UpdateGameLogic() {
      auto map_area = World::get()->curr_map_area();
      auto &mobs = *(map_area->mobs_mirror());
      for (auto it = mobs.begin(); it != mobs.end();) {
         auto mob = it->first;
         auto coord = it->second;
         if (SDL_GetTicks() > mob->ticks_last_move() + 400 / mob->movement_speed()) {
            auto player_pos = Player::get()->position().GetXZ().ToIntPoint();
            auto dx = player_pos.x - coord.x;
            auto dy = player_pos.y - coord.y;
            auto aggro_range = MobsConf::get()->GetAggroRange(mob->type());
            if (aggro_range > 0) {
               auto r = std::sqrt(dx * dx + dy * dy);
               if (r <= aggro_range)
                  mob->AggroPlayer();
            }
            int new_x;
            int new_y;
            if (mob->aggroing_player()) {
               auto norm_x = 0;
               auto norm_y = 0;
               auto abs_dx = std::abs(dx);
               auto abs_dy = std::abs(dy);
               if (dx)
                  norm_x = dx / abs_dx;
               if (dy)
                  norm_y = dy / abs_dy;
               new_x = coord.x + norm_x;
               new_y = coord.y + norm_y;
            }
            else {
               auto dx = rand() % 2 - rand() % 2;
               auto dy = rand() % 2 - rand() % 2;
               new_x = coord.x + dx;
               new_y = coord.y + dy;
            }
            if (new_x >= 0 && new_y >= 0 && new_x < map_area->GetWidth() &&
                new_y < map_area->GetHeight()) {
               auto tile = map_area->GetTile(new_x, new_y);
               if (tile->ground() != "GroundWater") {
                  if (nullptr == tile->object()) {
                     if (nullptr == tile->mob()) {
                        tile->set_mob(mob);
                        map_area->GetTile(coord.x, coord.y)->set_mob(nullptr);
                        mob->set_ticks_last_move(SDL_GetTicks());
                        mobs.erase(it++);
                        mobs.insert({mob, {new_x, new_y}});
                        continue;
                     }
                  }
               }
            }
         }
         ++it;
      }
   }
}
