#pragma once

namespace Narradia
{
    PointF GetMousePosition();
    std::string_view GetCurrTime();
    Size GetTextureDimensions(std::string_view image_name);
}
