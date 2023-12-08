#pragma once
#include "world.structure/model/Tile.h"
#include <memory>

namespace Narradia {
    void DoDrawGround(std::shared_ptr<Tile> tile, Point coord);
}
