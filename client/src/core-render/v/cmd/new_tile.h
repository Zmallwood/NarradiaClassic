#pragma once
#include "core-render/v/renderer_tiles_view.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Prepares resources for a new tile to be rendered in 3D space, and returns its RID for
   /// later rendering.
   ///
   /// @return RID for the new tile.
   ////////////////////////////////////////////////////////////////////////////////
   RenderID NewTile();
}
