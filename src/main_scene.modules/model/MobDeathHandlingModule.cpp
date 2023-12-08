#include "MobDeathHandlingModule.h"
#include "MobTargetingModule.h"
#include "world.structure/model/World.h"

namespace Narradia {

    void MobDeathHandlingModule::UpdateGameLogic() {

        auto map_area = World::Get()->curr_map_area();
        auto &mobs = *map_area->mobs_mirror();

        for (auto it = mobs.begin(); it != mobs.end();) {
            auto mob = it->first;
            auto mob_coord = it->second;

            if (mob->IsDead()) {
                map_area->GetTile(mob_coord.x, mob_coord.y)->set_mob(nullptr);
                MobTargetingModule::Get()->ClearTarget();
                mobs.erase(it++);
                map_area->GetTile(mob_coord.x, mob_coord.y)
                    ->set_object(std::make_shared<Object>("ObjectPoolOfBlood"));
                continue;
            }

            ++it;
        }
    }
}
