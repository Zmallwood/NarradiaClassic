#pragma once
#include "../../../matter/m/color.h"
#include "../../../matter/m/colors.h"
#include "../../../matter/m/rectf.h"
#include "../../m/font_sizes.h"
#include "core-render-text/m/font.h"
#include "core-render-text/v/renderer_text.h"
#include "core-render/v/cmd/draw_image.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Renders a text string to the canvas. Requires it to first have been initialized with
   /// NewString().
   ///
   /// @param[in] rid RID obtained with NewString().
   /// @param[in] text Text to be rendered.
   /// @param[in] position Canvas position to render the text at.
   /// @param[in] color Color to render the text in.
   /// @param[in] center_align Center align text with the center at the provided position.
   /// @param[in] font_size Font size to render the text in.
   ////////////////////////////////////////////////////////////////////////////////
   auto DrawString(
       RenderID rid, std::string_view text, PointF position, Color color = Colors::white,
       bool center_align = false, FontSizes font_size = FontSizes::_20) -> void;
}
