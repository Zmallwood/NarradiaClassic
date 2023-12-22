#include "canvas_utilities.h"
#include "core/model/graphics.h"
namespace Narradia
{
   int w, h;
   static Size canv_sz;

   auto CanvasSize() -> Size {
      SDL_GetWindowSize(Graphics::get()->win().get(), &w, &h);
      return {w, h};
   }

   auto AspectRatio() -> float {
      canv_sz = CanvasSize();
      return static_cast<float>(canv_sz.w) / canv_sz.h;
   }

   float WidthToHeight(float width) {
      return width * AspectRatio();
   }

   float HeightToWidth(float height) {
      return height / AspectRatio();
   }
}
