#include "DoGenerateGrass.h"
#include "configuration/model/Configuration.h"
#include "world.structure/model/MapArea.h"

namespace Narradia {
    /**
     * Generate grass on the whole map.
     */
    void DoGenerateGrass(std::shared_ptr<MapArea> map_area) {
        for (auto y = 0; y < kMapHeight; y++) {
            for (auto x = 0; x < kMapWidth; x++) {
                map_area->GetTile(x, y)->set_ground("GroundGrass");
            }
        }
    }
}
