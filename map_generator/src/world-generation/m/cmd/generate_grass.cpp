#include "generate_grass.h"
#include "conf/m/consts.h"
#include "world-struct/m/map_area.h"
namespace Narradia
{
    /**
     Generate grass on the whole map.
    */
    void GenerateGrass(std::shared_ptr<MapArea> map_area) {
        for (auto y = 0; y < kMapHeight; y++) {
            for (auto x = 0; x < kMapWidth; x++) {
                map_area->GetTile(x, y)->set_ground("Ground");
                map_area->GetTile(x, y)->color()->r = 0.3f;
                map_area->GetTile(x, y)->color()->b = 0.3f;
            }
        }
    }
}
