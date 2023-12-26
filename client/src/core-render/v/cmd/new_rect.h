#pragma once
#include "core-render/v/renderer_2d_solid_colors_view.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Prepares resources for a new colored rectangle, and the returns its RID for later
   /// rendering.
   ///
   /// @return RID for the new rectangle.
   ////////////////////////////////////////////////////////////////////////////////
   auto NewRect() -> RenderID;
}
