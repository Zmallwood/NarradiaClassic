#pragma once
#include "core.render.text/model/font_sizes.h"
namespace Narradia {
  void DrawString(
      RenderID rid, std::string_view text, PointF position, Color color = {1.0f, 1.0f, 1.0f, 1.0f},
      bool center_align = false, FontSizes font_size = FontSizes::_20);
}
