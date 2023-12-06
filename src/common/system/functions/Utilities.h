#pragma once

namespace Narradia {
    Size GetCanvasSize();

    float GetAspectRatio();

    PointF GetMousePosition();

    std::string_view GetCurrTime();

    float GetTileHeight();

    int GetNumGridCols();

    int GetNumGridRows();

    int GetGridCenterX();

    int GetGridCenterY();
}
