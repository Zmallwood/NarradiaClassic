#include "generate_desert.h"
#include "conf/model/constants.h"
#include "world-structure/model/map_area.h"
namespace Narradia
{
    /**
     Generate grass on the whole map.
    */
    void GenerateDesert(std::shared_ptr<MapArea> map_area) {
        for (auto y = 0; y < kMapHeight; y++) {
            for (auto x = 0; x < kMapWidth; x++) {
                map_area->GetTile(x, y)->set_ground("GroundSand");
                map_area->GetTile(x, y)->color()->r = 1.0f;
                map_area->GetTile(x, y)->color()->g = 1.0f;
                map_area->GetTile(x, y)->color()->b = 1.0f;
            }
        }
    }
}

