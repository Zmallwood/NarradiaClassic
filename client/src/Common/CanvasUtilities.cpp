#include "CanvasUtilities.h"

namespace Narradia {
   Size CanvasSize() {
      int _w, _h;
      SDL_GetWindowSize(Graphics::get()->win().get(), &_w, &_h);
      return {_w, _h};
   }

   float AspectRatio() {
      auto _canvSz = CanvasSize();
      return static_cast<float>(_canvSz.w) / _canvSz.h;
   }

   float WidthToHeight(float _w) {
      return _w * AspectRatio();
   }

   float HeightToWidth(float _h) {
      return _h / AspectRatio();
   }
}
