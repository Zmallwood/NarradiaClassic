#include "utilities.h"
#include "core.assets/model/image_bank.h"
namespace Narradia
{
   int x_px, y_px;
   inline Size canv_sz;
   float x, y;
   time_t now;
   char buffer[80];
   std::tm *p_tstruct;
   Size dim;
   int mip_level = 0;
   RenderID img_id;

   auto MousePosition() -> PointF {
      canv_sz = CanvasSize();
      SDL_GetMouseState(&x_px, &y_px);
      x = static_cast<float>(x_px) / canv_sz.w;
      y = static_cast<float>(y_px) / canv_sz.h;
      return {x, y};
   }

   auto CurrTime() -> std::string_view {
      now = time(0);
      p_tstruct = localtime(&now);
      strftime(buffer, sizeof(buffer), "%X", p_tstruct);
      return std::string_view(buffer);
   }

   auto TextureDimensions(std::string_view img_name) -> Size {
      img_id = ImageBank::get()->GetImage(img_name);
      glBindTexture(GL_TEXTURE_2D, img_id);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_WIDTH, &dim.w);
      glGetTexLevelParameteriv(GL_TEXTURE_2D, mip_level, GL_TEXTURE_HEIGHT, &dim.h);
      return dim;
   }
}
