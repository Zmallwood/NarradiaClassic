#include "calc_normals.h"
#include "conf/model/constants.h"
#include "world.structure/model/map_area.h"
namespace Narradia
{
    void CalcNormals(std::shared_ptr<MapArea> map_area) {
        for (auto y = 0; y < kMapHeight; y++) {
            for (auto x = 0; x < kMapWidth; x++) {
                auto tile_coord = Point{x, y};
                auto tile = map_area->GetTile(tile_coord.x, tile_coord.y);
                auto elev00 = tile->elevation();
                auto elev10 = elev00;
                auto elev11 = elev00;
                auto elev01 = elev00;
                auto coord10 = tile_coord.Translate(1, 0);
                auto coord11 = tile_coord.Translate(1, 1);
                auto coord01 = tile_coord.Translate(0, 1);
                if (map_area->IsInsideMap(coord10))
                    elev10 = map_area->GetTile(coord10)->elevation();
                if (map_area->IsInsideMap(coord11))
                    elev11 = map_area->GetTile(coord11)->elevation();
                if (map_area->IsInsideMap(coord01))
                    elev01 = map_area->GetTile(coord01)->elevation();
                auto x0 = tile_coord.x * kTileSize;
                auto y0 = elev00 * kElevAmount;
                auto z0 = tile_coord.y * kTileSize;
                auto x1 = tile_coord.x * kTileSize + kTileSize;
                auto y1 = elev10 * kElevAmount;
                auto z1 = tile_coord.y * kTileSize;
                auto x3 = tile_coord.x * kTileSize;
                auto y3 = elev01 * kElevAmount;
                auto z3 = tile_coord.y * kTileSize + kTileSize;
                auto p0 = Point3F{x0, y0, z0};
                auto p1 = Point3F{x1, y1, z1};
                auto p3 = Point3F{x3, y3, z3};
                tile->set_normal(CalcTileNormal(p0, p1, p3));
            }
        }
    }
}
