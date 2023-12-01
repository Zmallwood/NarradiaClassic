#include "DoDrawObjects.h"
#include "world.structure/model/Tile.h"

namespace Narradia {
    void DoDrawObjects(TileInfo tile_info) {
        if (tile_info.tile->object()) {
            if (tile_info.tile->object()->type() != "") {
            }
        }
    }
}
