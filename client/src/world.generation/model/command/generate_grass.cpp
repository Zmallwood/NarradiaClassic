#include "generate_grass.h"
#include "conf/model/conf.h"
#include "world.structure/model/map_area.h"
namespace Narradia
{
    /**
     Generate grass on the whole map.
    */
    void GenerateGrass(std::shared_ptr<MapArea> map_area) {
        for (auto y = 0; y < map_area->GetHeight(); y++) {
            for (auto x = 0; x < map_area->GetWidth(); x++) {
                map_area->GetTile(x, y)->set_ground("Ground");
                map_area->GetTile(x, y)->color()->r = 0.0f;
                map_area->GetTile(x, y)->color()->b = 0.0f;
            }
        }
    }
}
