#include "canvas_utils.h"
#include "core/model/graphics.h"

namespace Narradia {
  /**
   Returns canvas size in pixels.
  */
  Size GetCanvasSize() {
    int width;
    int height;
    SDL_GetWindowSize(Graphics::Get()->window().get(), &width, &height);
    return {width, height};
  }

  /**
   Returns aspect ratio of canvas.
  */
  float GetAspectRatio() {
    auto canvas_size = GetCanvasSize();
    return static_cast<float>(canvas_size.width) / canvas_size.height;
  }
}
