#include "tile_calc.h"
#include "world.structure/model/world.h"
#include "conf/model/conf.h"
namespace Narradia {
  float CalcTileAverageElevation(Point coord) {
    auto map_area = World::Get()->curr_map_area();
    auto elev00 = map_area->GetTile(coord.x, coord.y)->elevation() * kElevAmount;
    auto elev10 = elev00;
    auto elev11 = elev00;
    auto elev01 = elev00;
    auto coord10 = Point{coord.x + 1, coord.y};
    auto coord11 = Point{coord.x + 1, coord.y + 1};
    auto coord01 = Point{coord.x, coord.y + 1};
    if (map_area->IsInsideMap(coord10))
      elev10 = map_area->GetTile(coord10)->elevation() * kElevAmount;
    if (map_area->IsInsideMap(coord11))
      elev11 = map_area->GetTile(coord11)->elevation() * kElevAmount;
    if (map_area->IsInsideMap(coord01))
      elev01 = map_area->GetTile(coord01)->elevation() * kElevAmount;
    return (elev00 + elev10 + elev11 + elev01) / 4.0f;
  }
}
