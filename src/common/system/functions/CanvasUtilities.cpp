#include "CanvasUtilities.h"
#include "core/model/Graphics.h"

namespace Narradia {
    /**
     * Returns canvas size in pixels.
     */
    Size GetCanvasSize() {
        int width;
        int height;
        SDL_GetWindowSize(Graphics::Get()->window().get(), &width, &height);
        return {width, height};
    }

    /**
     * Returns aspect ratio of canvas.
     */
    float GetAspectRatio() {
        auto canvasSize = GetCanvasSize();
        return static_cast<float>(canvasSize.width) / canvasSize.height;
    }
}
