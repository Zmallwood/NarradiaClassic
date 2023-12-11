#include "generate_water.h"
#include "conf/model/conf.h"
#include "world.structure/model/map_area.h"
namespace Narradia {
  /**
   Generate water randomly.
  */
  void GenerateWater(std::shared_ptr<MapArea> map_area) {
    auto r_max = std::max(kMapHeight, kMapWidth);
    auto r_min = std::min(kMapHeight, kMapWidth) / 2;
    auto x_center = kMapWidth / 2;
    auto y_center = kMapHeight / 2;
    for (auto r = r_max; r >= r_min - 8; r--) {
      for (auto y = y_center - r; y <= y_center + r; y++) {
        for (auto x = x_center - r; x <= x_center + r; x++) {
          if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
            continue;
          auto dx = x - x_center;
          auto dy = y - y_center;
          if (dx * dx + dy * dy >= r * r)
            map_area->GetTile(x, y)->set_ground("GroundWater");
        }
      }
    }
    //    auto num_lakes = static_cast<int>(20 * kMapWidth / 100.0f * kMapHeight / 80.0f);
    //    for (auto i = 0; i < num_lakes; i++) {
    //      auto x_center = rand() % kMapWidth;
    //      auto y_center = rand() % kMapHeight;
    //      auto r = 2 + rand() % 6;
    //      for (auto y = y_center - r; y <= y_center + r; y++) {
    //        for (auto x = x_center - r; x <= x_center + r; x++) {
    //          if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
    //            continue;
    //          auto dx = x - x_center;
    //          auto dy = y - y_center;
    //          if (dx * dx + dy * dy <= r * r)
    //            map_area->GetTile(x, y)->set_ground("GroundWater");
    //        }
    //      }
    //    }
  }
}
