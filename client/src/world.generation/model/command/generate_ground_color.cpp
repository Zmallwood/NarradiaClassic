#include "generate_ground_color.h"
#include "conf/model/conf.h"
#include "world.structure/model/map_area.h"
namespace Narradia
{
    void GenerateGroundColor(std::shared_ptr<MapArea> map_area) {
        auto num_areas =
            static_cast<int>(50 * map_area->GetWidth() / 100.0f * map_area->GetHeight() / 80.0f);
        for (auto i = 0; i < num_areas; i++) {
            auto x_center = rand() % map_area->GetWidth();
            auto y_center = rand() % map_area->GetHeight();
            auto r = 2 + rand() % 6;
            auto color_style = rand() % 3;
            for (auto y = y_center - r; y <= y_center + r; y++) {
                for (auto x = x_center - r; x <= x_center + r; x++) {
                    if (x < 0 || y < 0 || x >= map_area->GetWidth() || y >= map_area->GetHeight())
                        continue;
                    auto dx = x - x_center;
                    auto dy = y - y_center;
                    if (dx * dx + dy * dy <= r * r) {
                        if (map_area->GetTile(x, y)->ground() == "Ground") {
                            if (color_style == 0) {
                                map_area->GetTile(x, y)->color()->g *= 0.6f;
                            }
                            else if (color_style == 1) {
                                map_area->GetTile(x, y)->color()->g *= 0.6f;
                                map_area->GetTile(x, y)->color()->r = 0.3f;
                                map_area->GetTile(x, y)->color()->b = 0.0f;
                            }
                            else if (color_style == 2) {
                                map_area->GetTile(x, y)->color()->g = 1.0f;
                                map_area->GetTile(x, y)->color()->r = 1.0f;
                                map_area->GetTile(x, y)->color()->b = 1.0f;
                            }
                        }
                    }
                }
            }
        }
    }
}
