#pragma once

#include "render-text/v/renderer_text.h"

namespace Narradia
{
   auto DrawString(
       RenderID rid, std::string_view text, PointF position, Color color = Colors::white,
       bool center_align = false, FontSizes font_size = FontSizes::_20) -> void;
}
