#if 1
#include "combat_chase_movement_module.h"
#include "mob_targeting_module.h"
#include "world-actors/m/player.h"
#include "world-struct/m/world.h"
#include "world-struct/m/map_area.h"
#endif

namespace Narradia
{
   void CombatChaseMovementModule::UpdateGameLogic()
   {
      auto time_to_update =
          SDL_GetTicks() > Player::get()->ticks_last_move() + 400 / Player::get()->movement_speed();
      if (false == time_to_update)
         return;
      auto targeted_mob = MobTargetingModule::get()->targeted_mob();
      if (targeted_mob)
      {
         auto map_area = World::get()->CurrMapArea();
         auto player_pos = Player::get()->position();
         auto mob_coord = map_area->mobs_mirror()->at(targeted_mob);
         auto dx = mob_coord.x - player_pos.x;
         auto dy = mob_coord.y - player_pos.z;
         auto abs_dx = std::abs(dx);
         auto abs_dy = std::abs(dy);
         if (abs_dx < 0.5f && abs_dy < 0.5f)
            return;
         auto base_angle_deg = std::atan2(dy, dx) * 180.0f / M_PI - 90.0f;
         Player::get()->set_facing_angle_deg(-base_angle_deg);
         auto angle_deg = base_angle_deg + Player::get()->facing_angle_deg();
         Player::get()->MoveAtAngle(angle_deg);
         Player::get()->set_facing_angle_deg(angle_deg);
         Player::get()->set_ticks_last_move(SDL_GetTicks());
         Player::get()->set_destination({-1, -1});
      }
   }
}
