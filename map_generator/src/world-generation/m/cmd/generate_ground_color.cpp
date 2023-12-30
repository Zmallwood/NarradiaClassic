#include "generate_ground_color.h"
#include "conf/m/consts.h"
#include "world-struct/m/map_area.h"
namespace Narradia
{
   void GenerateGroundColor(std::shared_ptr<MapArea> map_area) {
      auto num_areas = static_cast<int>(50 * kMapWidth / 100.0f * kMapHeight / 80.0f);
      for (auto i = 0; i < num_areas; i++) {
         auto x_center = rand() % kMapWidth;
         auto y_center = rand() % kMapHeight;
         auto r = 2 + rand() % 16;
         auto color_style = rand() % 3;
         for (auto y = y_center - r; y <= y_center + r; y++) {
            for (auto x = x_center - r; x <= x_center + r; x++) {
               if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
                  continue;
               auto dx = x - x_center;
               auto dy = y - y_center;
               if (dx * dx + dy * dy <= r * r) {
                  auto r_inv = r - std::sqrt(dx * dx + dy * dy);
                  auto k = 0.5f;
                  if (map_area->GetTile(x, y)->ground() == "Ground") {
                     if (color_style == 0) {
                        map_area->GetTile(x, y)->color()->g *= 0.91f * r_inv * k;
                     }
                     else if (color_style == 1) {
                        map_area->GetTile(x, y)->color()->g *= 0.2f * r_inv * k;
                        map_area->GetTile(x, y)->color()->r = 0.1f * r_inv * k;
                        map_area->GetTile(x, y)->color()->b = 0.f;
                     }
                     else if (color_style == 2) {
                        map_area->GetTile(x, y)->color()->g = 0.3f * r_inv * k;
                        map_area->GetTile(x, y)->color()->r = 0.3f * r_inv * k;
                        map_area->GetTile(x, y)->color()->b = 0.3f * r_inv * k;
                     }
                  }
                  else if (map_area->GetTile(x, y)->ground() == "GroundWater") {
                     map_area->GetTile(x, y)->color()->g = 0.0f;
                     map_area->GetTile(x, y)->color()->r = 0.5f;
                     map_area->GetTile(x, y)->color()->b = 1.0f;
                  }
               }
            }
         }
      }
   }
}