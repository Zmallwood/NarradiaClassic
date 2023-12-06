#include "MobMovementModule.h"
#include "world.structure/model/World.h"

namespace Narradia {
    void MobMovementModule::UpdateGameLogic() {
        auto map_area = World::Get()->curr_map_area();
        auto mobs = *(map_area->mobs_mirror());

        for (auto it = mobs.begin(); it != mobs.end();) {
            auto mob = it->first;
            auto coord = it->second;

            ++it;
        }
    }
}
