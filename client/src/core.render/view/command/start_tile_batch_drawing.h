#pragma once
#include "../../../conf/model/constants.h"
#include "../camera_gl.h"
#include "../renderer_tiles_view.h"
#include "../../../world.actors/model/player.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Starts batch drawing of tiles, called before a tile rendering loop.
   ////////////////////////////////////////////////////////////////////////////////
   auto StartTileBatchDrawing() -> void;
}
