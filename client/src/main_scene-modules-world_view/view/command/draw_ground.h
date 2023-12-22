#pragma once
#include "world-structure/model/tile.h"
#include <memory>
namespace Narradia
{
    void DrawGround(std::shared_ptr<Tile> tile, Point coord);
}
