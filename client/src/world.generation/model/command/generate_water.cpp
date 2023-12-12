#include "generate_water.h"
#include "conf/model/conf.h"
#include "world.structure/model/map_area.h"
namespace Narradia
{
    /**
     Generate water randomly.
    */
    void GenerateWater(std::shared_ptr<MapArea> map_area) {
        auto r_max = std::max(map_area->GetWidth(), map_area->GetHeight());
        auto r_min = std::min(map_area->GetWidth(), map_area->GetHeight()) / 2;
        auto x_center = map_area->GetWidth()/ 2;
        auto y_center = map_area->GetHeight()/ 2;
        for (auto r = r_max; r >= r_min - kShoreSize; r--) {
            for (auto y = y_center - r; y <= y_center + r; y++) {
                for (auto x = x_center - r; x <= x_center + r; x++) {
                    if (x < 0 || y < 0 || x >= map_area->GetWidth()|| y >= map_area->GetHeight())
                        continue;
                    auto dx = x - x_center;
                    auto dy = y - y_center;
                    if (dx * dx + dy * dy >= r * r) {
                        map_area->GetTile(x, y)->set_ground("GroundWater");
                        map_area->GetTile(x, y)->color()->b = 1.0f;
                    }
                }
            }
        }
        //    auto num_lakes = static_cast<int>(20 * map_area->GetWidth()/ 100.0f * map_area->GetHeight()/ 80.0f);
        //    for (auto i = 0; i < num_lakes; i++) {
        //      auto x_center = rand() % map_area->GetWidth();
        //      auto y_center = rand() % map_area->GetHeight();
        //      auto r = 2 + rand() % 6;
        //      for (auto y = y_center - r; y <= y_center + r; y++) {
        //        for (auto x = x_center - r; x <= x_center + r; x++) {
        //          if (x < 0 || y < 0 || x >= map_area->GetWidth()|| y >= map_area->GetHeight())
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
