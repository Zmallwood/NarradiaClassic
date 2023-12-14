#pragma once
#include "core.render/view/renderer_tiles_view.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Stops tile batch drawing, called after a tile rendering loop.
   ////////////////////////////////////////////////////////////////////////////////
   auto StopTileBatchDrawing() -> void;
}
