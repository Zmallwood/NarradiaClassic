#pragma once
#include "../../m/font_sizes.h"
#include "core-render-text/m/font.h"
#include "core-render-text/v/renderer_text.h"
#include "core-render/v/cmd/draw_image.h"
namespace Narradia
{
   auto DrawString(
       RenderID rid, std::string_view text, PointF position, Color color = Colors::white,
       bool center_align = false, FontSizes font_size = FontSizes::_20) -> void;
}
