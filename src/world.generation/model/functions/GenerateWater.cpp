#include "GenerateWater.h"
#include "configuration/model/Configuration.h"
#include "world.structure/model/MapArea.h"

namespace Narradia {

    /**
     * Generate water randomly.
     */
    void GenerateWater(std::shared_ptr<MapArea> map_area) {

        auto num_lakes = 30;

        for (auto i = 0; i < num_lakes; i++) {
            auto x_center = rand() % kMapWidth;
            auto y_center = rand() % kMapHeight;
            auto r = 3 + rand() % 10;

            for (auto y = y_center - r; y <= y_center + r; y++) {

                for (auto x = x_center - r; x <= x_center + r; x++) {

                    if (x < 0 || y < 0 || x >= kMapWidth || y >= kMapHeight)
                        continue;
                    auto dx = x - x_center;
                    auto dy = y - y_center;

                    if (dx * dx + dy * dy <= r * r)
                        map_area->GetTile(x, y)->set_ground("GroundWater");
                }
            }
        }
    }
}
