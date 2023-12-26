#include "combat_module.h"
#include "core/m/console.h"
#include "mob_targeting_module.h"
#include "world-actors/m/player.h"
#include "world-struct/m/world.h"
namespace Narradia
{
   void CombatModule::UpdateGameLogic()
   {
      auto targeted_mob = MobTargetingModule::get()->targeted_mob();
      if (targeted_mob)
      {
         if (SDL_GetTicks() >
             Player::get()->ticks_last_hit_performed() + 400 / Player::get()->attack_speed())
         {
            auto map_area = World::get()->CurrMapArea();
            auto mob_coord = map_area->mobs_mirror()->at(targeted_mob);
            auto player_pos = Player::get()->position();
            auto dx = mob_coord.x - player_pos.x;
            auto dy = mob_coord.y - player_pos.z;
            auto abs_dx = std::abs(dx);
            auto abs_dy = std::abs(dy);
            if (abs_dx <= 1 && abs_dy <= 1)
            {
               targeted_mob->Hit(10.0f);
               Player::get()->set_ticks_last_hit_performed(SDL_GetTicks());
               Player::get()->AddExperience(30);
               auto dice = static_cast<float>(rand()) / RAND_MAX;
               if (dice < Player::get()->ultimate_skill_chance())
               {
                  Player::get()->set_ticks_ulti_skill_start(SDL_GetTicks());
                  Console::get()->Print("Ulti-skill has been activated!");
               }
            }
         }
      }
      auto map_area = World::get()->CurrMapArea();
      auto &mobs = *(map_area->mobs_mirror());
      for (auto it = mobs.begin(); it != mobs.end();)
      {
         auto mob = it->first;
         auto coord = it->second;
         if (SDL_GetTicks() > mob->ticks_last_hit_performed() + 400 / mob->attack_speed())
         {
            auto player_pos = Player::get()->position().GetXZ().ToIntPoint();
            auto dx = player_pos.x - coord.x;
            auto dy = player_pos.y - coord.y;
            if (mob->aggroing_player())
            {
               auto r = std::sqrt(dx * dx + dy * dy);
               if (r <= 1.0f)
               {
                  Player::get()->Hit(1);
                  mob->set_ticks_last_hit_performed(SDL_GetTicks());
               }
            }
         }
         ++it;
      }
   }
}
