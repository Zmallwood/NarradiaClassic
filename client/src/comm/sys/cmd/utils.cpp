#if 1
#include "utils.h"
#include "core-assets/m/image_bank.h"
#include "core/m/graphics.h"
#endif

namespace Narradia
{
   Size CanvasSize()
   {
      int w, h;
      SDL_GetWindowSize(Graphics::get()->win().get(), &w, &h);

      return {w, h};
   }

   float AspectRatio()
   {
      auto canv_sz = CanvasSize();

      return static_cast<float>(canv_sz.w) / canv_sz.h;
   }

   float WidthToHeight(float w)
   {
      return w * AspectRatio();
   }

   float HeightToWidth(float h)
   {
      return h / AspectRatio();
   }

   PointF MousePosition()
   {
      int x_px, y_px;
      auto canv_sz = CanvasSize();
      SDL_GetMouseState(&x_px, &y_px);
      auto x = static_cast<float>(x_px) / canv_sz.w;
      auto y = static_cast<float>(y_px) / canv_sz.h;

      return {x, y};
   }

   std::string_view CurrTime()
   {
      char buffer[80];
      auto now = time(0);
      auto p_tstruct = localtime(&now);
      strftime(buffer, sizeof(buffer), "%X", p_tstruct);

      return std::string_view(buffer);
   }

   Size TextureDimensions(std::string_view img_name)
   {
      Size dim;
      int mip_level = 0;
      auto img_id = ImageBank::get()->GetImage(img_name);
      glBindTexture(GL_TEXTURE_2D, img_id);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_WIDTH, &dim.w);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_HEIGHT, &dim.h);

      return dim;
   }
}
