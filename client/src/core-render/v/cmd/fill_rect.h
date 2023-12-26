#pragma once
#include "../renderer_2d_solid_colors_view.h"
#include <vector>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Renders a color-filled rectangle to the canvas. Must previously have been initialized
   /// with NewRect();.
   ///
   /// @param[[TODO:direction]] vao_id [TODO:description]
   /// @param[[TODO:direction]] rect [TODO:description]
   /// @param[[TODO:direction]] color [TODO:description]
   ////////////////////////////////////////////////////////////////////////////////
   auto FillRect(RenderID vao_id, RectF rect, Color color) -> void;
}
