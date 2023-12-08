#include "GenerateMobs.h"
#include "configuration/model/Configuration.h"
#include "world.structure/model/MapArea.h"

namespace Narradia {

    /**
     * Generate mobs randomly.
     */
    void GenerateMobs(std::shared_ptr<MapArea> map_area) {

        auto num_cows = 200;

        for (auto i = 0; i < num_cows; i++) {
            auto x = rand() % kMapWidth;
            auto y = rand() % kMapHeight;

            if (map_area->GetTile(x, y)->ground() != "GroundWater") {

                if (nullptr == map_area->GetTile(x, y)->mob()) {
                    auto new_mob = std::make_shared<Mob>("MobCow");
                    map_area->GetTile(x, y)->set_mob(new_mob);
                    map_area->mobs_mirror()->insert({new_mob, {x, y}});
                }
            }
        }
        auto num_rats = 200;

        for (auto i = 0; i < num_rats; i++) {
            auto x = rand() % kMapWidth;
            auto y = rand() % kMapHeight;

            if (map_area->GetTile(x, y)->ground() != "GroundWater") {

                if (nullptr == map_area->GetTile(x, y)->mob()) {
                    auto new_mob = std::make_shared<Mob>("MobRat");
                    map_area->GetTile(x, y)->set_mob(new_mob);
                    map_area->mobs_mirror()->insert({new_mob, {x, y}});
                }
            }
        }
    }
}
