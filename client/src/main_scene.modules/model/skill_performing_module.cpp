#include "skill_performing_module.h"
#include "conf/model/conf.h"
#include "world.actors/model/player.h"
#include "world.structure/model/world.h"
namespace Narradia
{
    void SkillPerformingModule::UpdateGameLogic() {
        if (SDL_GetTicks() > ticks_last_skill_tick_ + 400 / skill_ticks_frequency_) {
            if (SDL_GetTicks() < Player::get()->ticks_ulti_skill_start() +
                                     Player::get()->ulti_skill_duration() &&
                Player::get()->ticks_ulti_skill_start() != 0) {
                auto player_pos = Player::get()->position().GetXZ().ToIntPoint();
                auto map_area = World::get()->curr_map_area();
                auto r = 7;
                for (auto y = player_pos.y - r; y < player_pos.y + r; y++) {
                    for (auto x = player_pos.x - r; x <= player_pos.x + r; x++) {
                        if (x < 0 || y < 0 || x >= map_area->GetWidth() ||
                            y >= map_area->GetHeight())
                            continue;
                        auto dx = x - player_pos.x;
                        auto dy = y - player_pos.y;
                        if (dx * dx + dy * dy <= r * r) {
                            map_area->GetTile(x, y)->set_tile_effect(
                                {"UltiSkillTileFire", static_cast<int>(SDL_GetTicks())});
                            if (map_area->GetTile(x, y)->mob()) {
                                map_area->GetTile(x, y)->mob()->Hit(
                                    map_area->GetTile(x, y)->mob()->hp());
                                Player::get()->AddExperience(30);
                            }
                        }
                    }
                }
            }
            ticks_last_skill_tick_ = SDL_GetTicks();
        }
    }
}