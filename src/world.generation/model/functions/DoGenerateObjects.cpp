#include "DoGenerateObjects.h"
#include "configuration/model/Configuration.h"
#include "world.structure/model/MapArea.h"

namespace Narradia {
    void DoGenerateObjects(std::shared_ptr<MapArea> map_area) {
        auto num_forests_tree1 = 20;

        for (auto i = 0; i < num_forests_tree1; i++) {
            auto x = rand() % kMapWidth;
            auto y = rand() % kMapHeight;
            auto num_trees = 5 + rand() % 20;

            for (auto j = 0; j < num_trees; j++) {
                if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
                    continue;

                if (map_area->GetTile(x, y)->ground() != "GroundWater") {
                    map_area->GetTile(x, y)->set_object(
                        std::make_shared<Object>("ObjectTree1"));
                }

                x += rand() % 3 - rand() % 3;
                y += rand() % 3 - rand() % 3;
            }
        }
        auto num_forests_tree2 = 20;

        for (auto i = 0; i < num_forests_tree2; i++) {
            auto x = rand() % kMapWidth;
            auto y = rand() % kMapHeight;
            auto num_trees = 5 + rand() % 20;

            for (auto j = 0; j < num_trees; j++) {
                if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
                    continue;

                if (map_area->GetTile(x, y)->ground() != "GroundWater") {
                    map_area->GetTile(x, y)->set_object(
                        std::make_shared<Object>("ObjectTree2"));
                }

                x += rand() % 3 - rand() % 3;
                y += rand() % 3 - rand() % 3;
            }
        }
    }
}
