#include "generate_objects.h"
#include "conf/model/constants.h"
#include "world-structure/model/map_area.h"
namespace Narradia
{
    /**
     Generate objects randomly, such as vegetation and other
     kinds.
    */
    void GenerateObjects(std::shared_ptr<MapArea> map_area) {
        auto num_forests_tree1 = static_cast<int>(20 * kMapWidth / 100.0f * kMapHeight / 80.0f);
        for (auto i = 0; i < num_forests_tree1; i++) {
            auto x = rand() % kMapWidth;
            auto y = rand() % kMapHeight;
            auto num_trees = 5 + rand() % 10;
            for (auto j = 0; j < num_trees; j++) {
                if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
                    continue;
                if (map_area->GetTile(x, y)->ground() != "GroundWater") {
                    map_area->GetTile(x, y)->set_object(std::make_shared<Object>("ObjectTree1"));
                }
                x += rand() % 4 - rand() % 4;
                y += rand() % 4 - rand() % 4;
            }
        }
        auto num_forests_tree2 = static_cast<int>(20 * kMapWidth / 100.0f * kMapHeight / 80.0f);
        for (auto i = 0; i < num_forests_tree2; i++) {
            auto x = rand() % kMapWidth;
            auto y = rand() % kMapHeight;
            auto num_trees = 5 + rand() % 10;
            for (auto j = 0; j < num_trees; j++) {
                if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
                    continue;
                if (map_area->GetTile(x, y)->ground() != "GroundWater") {
                    map_area->GetTile(x, y)->set_object(std::make_shared<Object>("ObjectTree2"));
                }
                x += rand() % 4 - rand() % 4;
                y += rand() % 4 - rand() % 4;
            }
        }
        auto num_bush1s = static_cast<int>(200 * kMapWidth / 100.0f * kMapHeight / 80.0f);
        for (auto i = 0; i < num_bush1s; i++) {
            auto x = rand() % kMapWidth;
            auto y = rand() % kMapHeight;
            if (map_area->GetTile(x, y)->ground() != "GroundWater")
                map_area->GetTile(x, y)->set_object(std::make_shared<Object>("ObjectBush1"));
        }
        auto num_stone_boulders = static_cast<int>(100 * kMapWidth / 100.0f * kMapHeight / 80.0f);
        for (auto i = 0; i < num_stone_boulders; i++) {
            auto x = rand() % kMapWidth;
            auto y = rand() % kMapHeight;
            if (map_area->GetTile(x, y)->ground() != "GroundWater")
                map_area->GetTile(x, y)->set_object(std::make_shared<Object>("ObjectStoneBoulder"));
        }
    }
}
