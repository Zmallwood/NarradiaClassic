#include "MobMovementModule.h"
#include "conf/model/Configuration.h"
#include "world.structure/model/World.h"

namespace Narradia {
    void MobMovementModule::UpdateGameLogic() {
        auto map_area = World::Get()->curr_map_area();
        auto &mobs = *(map_area->mobs_mirror());

        for (auto it = mobs.begin(); it != mobs.end();) {
            auto mob = it->first;
            auto coord = it->second;

            if (SDL_GetTicks() > mob->ticks_last_move() + 400 / mob->movement_speed()) {
                auto dx = rand() % 2 - rand() % 2;
                auto dy = rand() % 2 - rand() % 2;
                auto new_x = coord.x + dx;
                auto new_y = coord.y + dy;

                if (new_x >= 0 && new_y >= 0 && new_x < kMapWidth && new_y < kMapHeight) {
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
