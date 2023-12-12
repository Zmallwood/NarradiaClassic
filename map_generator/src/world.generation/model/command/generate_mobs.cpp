#include "generate_mobs.h"
#include "conf/model/conf.h"
#include "world.structure/model/map_area.h"
namespace Narradia
{
    /**
     Generate mobs randomly.
    */
    void GenerateMobs(std::shared_ptr<MapArea> map_area) {
        auto num_mob_types = 3;
        auto r_min = std::min(kMapWidth, kMapHeight) / 2;
        auto r_sector = (r_min - kShoreSize) / num_mob_types;
        auto x_center = kMapWidth / 2;
        auto y_center = kMapHeight / 2;
        for (auto i = 0; i < num_mob_types; i++) {
            auto r_start = r_min - i * r_sector;
            auto num_mobs = static_cast<int>(100 * kMapWidth / 100.0f * kMapHeight / 80.0f);
            for (auto j = 0; j < num_mobs; j++) {
                auto w = rand() % 360;
                auto r = r_start - rand() % r_sector;
                auto x = static_cast<int>(x_center + r * CosDeg(w));
                auto y = static_cast<int>(y_center + r * SinDeg(w));
                if (map_area->GetTile(x, y)->ground() != "GroundWater") {
                    if (nullptr == map_area->GetTile(x, y)->mob()) {
                        std::string mob_name;
                        switch (i) {
                        case 0:
                            mob_name = "MobPinkSlime";
                            break;
                        case 1:
                            mob_name = "MobBoar";
                            break;
                        case 2:
                            mob_name = "MobTroll";
                            break;
                        }
                        auto new_mob = std::make_shared<Mob>(mob_name);
                        map_area->GetTile(x, y)->set_mob(new_mob);
                        map_area->mobs_mirror()->insert({new_mob, {x, y}});
                    }
                }
            }
        }
        auto boss_mob = std::make_shared<Mob>("MobEvilSpirit");
        map_area->GetTile(x_center, y_center)->set_mob(boss_mob);
        map_area->mobs_mirror()->insert({boss_mob, {x_center, y_center}});
        //        auto num_boars = static_cast<int>(200 * kMapWidth / 100.0f * kMapHeight
        //        / 80.0f); for (auto i = 0; i < num_boars; i++) {
        //            auto x = rand() % kMapWidth;
        //            auto y = rand() % kMapHeight;
        //            if (map_area->GetTile(x, y)->ground() != "GroundWater") {
        //                if (nullptr == map_area->GetTile(x, y)->mob()) {
        //                    auto new_mob = std::make_shared<Mob>("MobPinkSlime");
        //                    map_area->GetTile(x, y)->set_mob(new_mob);
        //                    map_area->mobs_mirror()->insert({new_mob, {x, y}});
        //                }
        //            }
        //        }
    }
}
