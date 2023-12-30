#if 1
#include "main_pg-adds-non-visual.h"
#include "actors.h"
#include "conf.h"
#include "core.h"
#include "main_pg-adds-visual.h"
#include "main_pg-gui_windows.h"
#include "math.h"
#include "world-struct.h"
#endif

namespace Narradia
{
   // CombatModule
#if 1
   void CombatAdd::UpdateGameLogic() {
      auto targeted_mob = MobTargetingAdd::get()->targeted_mob();
      if (targeted_mob) {
         if (SDL_GetTicks() >
             Player::get()->ticks_last_hit_performed() + 400 / Player::get()->attack_speed()) {
            auto map_area = World::get()->CurrWorldArea();
            auto mob_coord = map_area->mobs_mirror()->at(targeted_mob);
            auto player_pos = Player::get()->position();
            auto dx = mob_coord.x - player_pos.x;
            auto dy = mob_coord.y - player_pos.z;
            auto abs_dx = std::abs(dx);
            auto abs_dy = std::abs(dy);
            if (abs_dx <= 1 && abs_dy <= 1) {
               targeted_mob->Hit(10.0f);
               Player::get()->set_ticks_last_hit_performed(SDL_GetTicks());
               Player::get()->AddExperience(30);
               auto dice = static_cast<float>(rand()) / RAND_MAX;
               if (dice < Player::get()->ultimate_skill_chance()) {
                  Player::get()->set_ticks_ulti_skill_start(SDL_GetTicks());
                  Console::get()->Print("Ulti-skill has been activated!");
               }
            }
         }
      }
      auto map_area = World::get()->CurrWorldArea();
      auto &mobs = *(map_area->mobs_mirror());
      for (auto it = mobs.begin(); it != mobs.end();) {
         auto mob = it->first;
         auto coord = it->second;
         if (SDL_GetTicks() > mob->ticks_last_hit_performed() + 400 / mob->attack_speed()) {
            auto player_pos = Player::get()->position().GetXZ().ToIntPoint();
            auto dx = player_pos.x - coord.x;
            auto dy = player_pos.y - coord.y;
            if (mob->aggroing_player()) {
               auto r = std::sqrt(dx * dx + dy * dy);
               if (r <= 1.0f) {
                  Player::get()->Hit(1);
                  mob->set_ticks_last_hit_performed(SDL_GetTicks());
               }
            }
         }
         ++it;
      }
   }
#endif

   // KbBindingsModule
#if 1
   void KbBindingsAdd::UpdateGameLogic() {
      if (KbInput::get()->KeyHasBeenFiredPickResult(SDLK_m)) {
         GuiWindowWorldMap::get()->ToggleVisibility();
      }
   }
#endif

   // MobDeathHandlingModule
#if 1
   void MobDeathHandlingAdd::UpdateGameLogic() {
      auto map_area = World::get()->CurrWorldArea();
      auto &mobs = *map_area->mobs_mirror();
      for (auto it = mobs.begin(); it != mobs.end();) {
         auto mob = it->first;
         auto mob_coord = it->second;
         if (mob->IsDead()) {
            map_area->GetTile(mob_coord.x, mob_coord.y)->set_mob(nullptr);
            MobTargetingAdd::get()->ClearTarget();
            mobs.erase(it++);
            map_area->GetTile(mob_coord.x, mob_coord.y)
                ->set_tile_effect({"ObjectPoolOfBlood", static_cast<int>(SDL_GetTicks())});
            continue;
         }
         ++it;
      }
   }
#endif

   // PlayerSpawnPositioningModule
#if 1
   void PlayerSpawnPositioningAdd::SpawnAtGoodLocation() {
      Player::get()->set_world_location({2, 2});
      auto map_area = World::get()->CurrWorldArea();
      std::shared_ptr<Tile> tile;
      int x;
      int y;
      auto x_center = map_area->GetWidth() / 2;
      auto y_center = map_area->GetHeight() / 2;
      auto r_min = std::min(map_area->GetWidth(), map_area->GetHeight()) / 2;
      do {
         auto angle_deg = static_cast<float>(rand() % 360);
         x = x_center + static_cast<int>((r_min - 1) * CosDeg(angle_deg));
         y = y_center + static_cast<int>((r_min - 1) * SinDeg(angle_deg));
         tile = map_area->GetTile(x, y);
      } while (tile->ground() == "GroundWater" || tile->object() || tile->mob());
      Player::get()->set_position({static_cast<float>(x), 0.0f, static_cast<float>(y)});
   }
#endif
}
