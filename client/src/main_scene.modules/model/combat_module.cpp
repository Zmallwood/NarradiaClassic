#include "combat_module.h"
#include "core/model/console.h"
#include "mob_targeting_module.h"
#include "world.actors/model/player.h"
#include "world.structure/model/world.h"
namespace Narradia
{
    void CombatModule::UpdateGameLogic() {
        auto targeted_mob = MobTargetingModule::get()->targeted_mob();
        if (targeted_mob) {
            if (SDL_GetTicks() >
                Player::get()->ticks_last_hit_performed() + 400 / Player::get()->attack_speed()) {
                auto map_area = World::get()->curr_map_area();
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
    }
}
