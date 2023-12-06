#include "CombatModule.h"
#include "MobTargetingModule.h"
#include "world.actors/model/Player.h"
#include "world.structure/model/World.h"

namespace Narradia {
    void CombatModule::UpdateGameLogic() {
        auto targeted_mob = MobTargetingModule::Get()->targeted_mob();

        if (targeted_mob) {
            if (SDL_GetTicks() > Player::Get()->ticks_last_hit_performed() +
                                     400 / Player::Get()->attack_speed() &&
                SDL_GetTicks() > Player::Get()->ticks_last_move() +
                                     400 / Player::Get()->movement_speed()) {
                auto map_area = World::Get()->curr_map_area();
                auto mob_coord = map_area->mobs_mirror()->at(targeted_mob);

                auto player_pos = Player::Get()->position();

                auto dx = mob_coord.x - player_pos.x;
                auto dy = mob_coord.y - player_pos.y;

                auto abs_dx = std::abs(dx);
                auto abs_dy = std::abs(dy);

                if (abs_dx <= 1 && abs_dy <= 1) {
                    targeted_mob->Hit(10.0f);
                    Player::Get()->set_ticks_last_hit_performed(SDL_GetTicks());

                    auto dice = static_cast<float>(rand()) / RAND_MAX;

                    if (dice < Player::Get()->ultimate_skill_chance()) {
                        Player::Get()->set_ultimate_skill_duraiton(3000);
                    }
                }
            }
        }
    }
}
