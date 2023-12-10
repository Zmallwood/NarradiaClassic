#include "generate_objects.h"
#include "conf/model/conf.h"
#include "world.structure/model/map_area.h"

namespace Narradia {
  /**
   Generate objects randomly, such as vegetation and other
   kinds.
  */
  void GenerateObjects(std::shared_ptr<MapArea> map_area) {
    auto num_forests_tree1 = 20;
    for (auto i = 0; i < num_forests_tree1; i++) {
      auto x = rand() % kMapWidth;
      auto y = rand() % kMapHeight;
      auto num_trees = 5 + rand() % 20;
      for (auto j = 0; j < num_trees; j++) {
        if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
          continue;
        if (map_area->GetTile(x, y)->ground() != "GroundWater") {
          map_area->GetTile(x, y)->set_object(std::make_shared<Object>("ObjectTree1"));
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
          map_area->GetTile(x, y)->set_object(std::make_shared<Object>("ObjectTree2"));
        }
        x += rand() % 3 - rand() % 3;
        y += rand() % 3 - rand() % 3;
      }
    }
    auto num_bush1s = 200;
    for (auto i = 0; i < num_bush1s; i++) {
      auto x = rand() % kMapWidth;
      auto y = rand() % kMapHeight;
      if (map_area->GetTile(x, y)->ground() != "GroundWater")
        map_area->GetTile(x, y)->set_object(std::make_shared<Object>("ObjectBush1"));
    }
    auto num_stone_boulders = 100;
    for (auto i = 0; i < num_stone_boulders; i++) {
      auto x = rand() % kMapWidth;
      auto y = rand() % kMapHeight;
      if (map_area->GetTile(x, y)->ground() != "GroundWater")
        map_area->GetTile(x, y)->set_object(std::make_shared<Object>("ObjectStoneBoulder"));
    }
  }
}