#include "Utilities.h"
#include "configuration/model/Configuration.h"
#include "core/model/Graphics.h"

namespace Narradia {
    Size GetCanvasSize() {
        int width;
        int height;
        SDL_GetWindowSize(Graphics::Get()->window().get(), &width, &height);

        return {width, height};
    }

    float GetAspectRatio() {
        auto canvasSize = GetCanvasSize();

        return static_cast<float>(canvasSize.width) / canvasSize.height;
    }

    PointF GetMousePosition() {
        int xPixels;
        int yPixels;
        auto canvasSize = GetCanvasSize();
        SDL_GetMouseState(&xPixels, &yPixels);
        auto x = static_cast<float>(xPixels) / canvasSize.width;
        auto y = static_cast<float>(yPixels) / canvasSize.height;

        return {x, y};
    }

    std::string_view GetCurrTime() {
        time_t now = time(0);
        char buffer[80];
        auto p_tstruct = localtime(&now);
        strftime(buffer, sizeof(buffer), "%X", p_tstruct);

        return buffer;
    }

    float GetTileHeight() {
        return kTileWidth * GetAspectRatio();
    }

    int GetNumGridCols() {
        return static_cast<int>(1.0f / kTileWidth);
    }

    int GetNumGridRows() {
        return static_cast<int>(1.0f / GetTileHeight());
    }

    int GetGridCenterX() {
        return (GetNumGridCols() - 1) / 2;
    }

    int GetGridCenterY() {
        return (GetNumGridRows() - 1) / 2;
    }
}
