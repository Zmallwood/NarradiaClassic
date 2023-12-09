#pragma once

namespace Narradia
{
    void DrawImage(
        std::string_view image_name, RenderId rid, const RectF &dest,
        Color color = {255, 255, 255, 255});
}
