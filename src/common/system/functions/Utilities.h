#pragma once

namespace Narradia {
    Size GetCanvasSize();

    float GetAspectRatio();

    PointF GetMousePosition();

    std::string_view GetCurrTime();

    Size GetTextureDimensions(std::string_view image_name);
}
