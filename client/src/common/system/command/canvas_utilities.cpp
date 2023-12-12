#include "canvas_utilities.h"
#include "core/model/graphics.h"
namespace Narradia
{
    ////////////////////////////////////////////////////////////////////////////////
    /// @brief Returns canvas size
    ///
    /// @return Canvas size in pixels.
    ////////////////////////////////////////////////////////////////////////////////
    Size GetCanvasSize() {
        int w, h;
        SDL_GetWindowSize(Graphics::Get()->window().get(), &w, &h);
        return Size(w, h);
    }

    ////////////////////////////////////////////////////////////////////////////////
    /// @brief Gets aspect ratio of canvas.
    ///
    /// @return Aspect ratio (w/h)
    ////////////////////////////////////////////////////////////////////////////////
    float GetAspectRatio() {
        auto canv_sz = GetCanvasSize();
        return static_cast<float>(canv_sz.w) / canv_sz.h;
    }
}
