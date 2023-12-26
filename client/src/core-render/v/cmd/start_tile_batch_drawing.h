#pragma once
#include "../../../conf/m/consts.h"
#include "../../../world-actors/m/player.h"
#include "../camera_gl.h"
#include "../renderer_tiles_view.h"
#include "world-struct/m/world.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Starts batch drawing of tiles, called before a tile rendering loop.
   ////////////////////////////////////////////////////////////////////////////////
   auto StartTileBatchDrawing() -> void;
}
