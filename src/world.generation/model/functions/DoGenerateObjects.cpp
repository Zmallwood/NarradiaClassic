#include "DoGenerateObjects.h"
#include "configuration/model/Configuration.h"
#include "world.structure/model/MapArea.h"

namespace Narradia {
    void DoGenerateObjects(std::shared_ptr<MapArea> map_area) {
        auto num_tree1s = 200;

        for (auto i = 0; i < num_tree1s; i++) {
            auto x = rand() % kMapWidth;
            auto y = rand() % kMapHeight;

            if (map_area->GetTile(x, y)->ground() != "GroundWater") {
                map_area->GetTile(x, y)->set_object(
                    std::make_shared<Object>("ObjectTree1"));
            }
        }
        auto num_tree2s = 200;

        for (auto i = 0; i < num_tree2s; i++) {
            auto x = rand() % kMapWidth;
            auto y = rand() % kMapHeight;

            if (map_area->GetTile(x, y)->ground() != "GroundWater") {
                map_area->GetTile(x, y)->set_object(
                    std::make_shared<Object>("ObjectTree2"));
            }
        }
    }
}