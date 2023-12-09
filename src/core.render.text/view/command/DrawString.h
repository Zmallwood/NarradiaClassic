#pragma once
#include "../../model/FontSizes.h"

namespace Narradia
{
    void DrawString(
        RenderId rid, std::string_view text, PointF position,
        Color color = {1.0f, 1.0f, 1.0f, 1.0f}, bool center_align = false,
        FontSizes font_size = FontSizes::_20);
}