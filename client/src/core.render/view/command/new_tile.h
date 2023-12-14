#pragma once
#include "core.render/view/renderer_tiles_view.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Prepares resources for a new tile to be rendered in 3D space, and returns its RID for
   /// later rendering.
   ///
   /// @return RID for the new tile.
   ////////////////////////////////////////////////////////////////////////////////
   auto NewTile() -> RenderID;
}
