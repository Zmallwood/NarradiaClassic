#include "generate_mobs.h"
#include "conf/model/conf.h"
#include "world.structure/model/map_area.h"
namespace Narradia {
  /**
   Generate mobs randomly.
  */
  void GenerateMobs(std::shared_ptr<MapArea> map_area) {
    auto num_boards = 200;
    for (auto i = 0; i < num_boards; i++) {
      auto x = rand() % kMapWidth;
      auto y = rand() % kMapHeight;
      if (map_area->GetTile(x, y)->ground() != "GroundWater") {
        if (nullptr == map_area->GetTile(x, y)->mob()) {
          auto new_mob = std::make_shared<Mob>("MobBoar");
          map_area->GetTile(x, y)->set_mob(new_mob);
          map_area->mobs_mirror()->insert({new_mob, {x, y}});
        }
      }
    }
  }
}
