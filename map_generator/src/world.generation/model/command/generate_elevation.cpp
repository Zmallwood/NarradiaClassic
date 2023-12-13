#include "generate_elevation.h"
#include "conf/model/conf.h"
#include "world.structure/model/map_area.h"
namespace Narradia
{
   void GenerateElevation(std::shared_ptr<MapArea> map_area) {
      auto r_max = std::max(kMapHeight, kMapWidth) / 2;
      auto r_min = std::min(kMapHeight, kMapWidth) / 2;
      auto x_center = kMapWidth / 2;
      auto y_center = kMapHeight / 2;
      for (auto r = r_min - kShoreSize; r >= 0; r--) {
         // for (auto r = r_min - kShoreSize; r >= 0; r--) {
         for (auto y = y_center - r; y <= y_center + r; y++) {
            for (auto x = x_center - r; x <= x_center + r; x++) {
               if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
                  continue;
               auto dx = x - x_center;
               auto dy = y - y_center;
               if (dx * dx + dy * dy <= r * r) {
                  if (map_area->GetTile(x, y)->ground() != "GroundWater")
                     map_area->GetTile(x, y)->IncreaseElevation(
                         0.4 * static_cast<float>(r_max) /
                         (r + 50.0f * kMapWidth / 200.0f * kMapHeight / 160.0f));
               }
            }
         }
      }
      auto num_spikes = static_cast<int>(20 * (kMapWidth / 100.0f * kMapHeight / 80.0f));
      for (auto i = 0; i < num_spikes; i++) {
         auto x_center = rand() % kMapWidth;
         auto y_center = rand() % kMapHeight;
         auto r = 3 + rand() % 7;
         for (auto y = y_center - r; y <= y_center + r; y++) {
            for (auto x = x_center - r; x <= x_center + r; x++) {
               if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
                  continue;
               auto dx = x - x_center;
               auto dy = y - y_center;
               if (dx * dx + dy * dy <= r * r) {
                  if (map_area->GetTile(x, y)->ground() != "GroundWater")
                     map_area->GetTile(x, y)->IncreaseElevation(0.1f);
               }
            }
         }
      }
      auto num_hills = static_cast<int>(20 * (kMapWidth / 100.0f * kMapHeight / 80.0f));
      for (auto i = 0; i < num_hills; i++) {
         auto x_center = rand() % kMapWidth;
         auto y_center = rand() % kMapHeight;
         auto r = 13 + rand() % 14;
         for (auto y = y_center - r; y <= y_center + r; y++) {
            for (auto x = x_center - r; x <= x_center + r; x++) {
               if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
                  continue;
               auto dx = x - x_center;
               auto dy = y - y_center;
               if (dx * dx + dy * dy <= r * r) {
                  if (map_area->GetTile(x, y)->ground() != "GroundWater")
                     map_area->GetTile(x, y)->IncreaseElevation(0.8f);
               }
            }
         }
      }
   }
}
