#include "CombatChaseMovementModule.h"
#include "MobTargetingModule.h"
#include "world.actors/model/Player.h"
#include "world.structure/model/World.h"

namespace Narradia
{
    void CombatChaseMovementModule::UpdateGameLogic()
    {
        auto time_to_update = SDL_GetTicks() > Player::Get()->ticks_last_move() +
                                                   400 / Player::Get()->movement_speed();

        if (false == time_to_update)
            return;

        auto targeted_mob = MobTargetingModule::Get()->targeted_mob();

        if (targeted_mob) {
            auto map_area = World::Get()->curr_map_area();
            auto player_pos = Player::Get()->position();
            auto mob_coord = map_area->mobs_mirror()->at(targeted_mob);
            auto dx = mob_coord.x - player_pos.x;
            auto dy = mob_coord.y - player_pos.y;
            auto abs_dx = std::abs(dx);
            auto abs_dy = std::abs(dy);
            auto norm_x = 0;
            auto norm_y = 0;
            if (dx)
                norm_x = dx / abs_dx;
            if (dy)
                norm_y = dy / abs_dy;
            auto new_x = player_pos.x + norm_x;
            auto new_y = player_pos.y + norm_y;
            auto tile = map_area->GetTile(new_x, new_y);
            if (tile->ground() == "GroundWater")
                return;
            if (tile->object() != nullptr)
                return;
            if (tile->mob() != nullptr)
                return;
            if (dx > 0)
                Player::Get()->MoveRight();
            if (dx < 0)
                Player::Get()->MoveLeft();
            if (dy > 0)
                Player::Get()->MoveDown();
            if (dy < 0)
                Player::Get()->MoveUp();
            Player::Get()->set_ticks_last_move(SDL_GetTicks());
            Player::Get()->set_destination({-1, -1});
        }
    }
}
