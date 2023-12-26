#pragma once
#include "world-struct/m/tile.h"
#include <memory>
namespace Narradia
{
   void DrawTileSymbols(std::shared_ptr<Tile> tile, Point coord);
}
