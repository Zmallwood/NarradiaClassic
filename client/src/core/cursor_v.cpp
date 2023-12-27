#if 1
#include "cursor_v.h"
#include "core/cursor.h"
#include "render/cmd_v/draw_image.h"
#include "render/cmd_v/new_image.h"
#endif

namespace Narradia
{
   CursorV::CursorV()
   {
      SDL_ShowCursor(0);
      rid_image = NewImage();
   }
   void CursorV::RenderCursor()
   {
      auto mouse_pos = MousePosition();
      auto w = kCursorWidth;
      auto h = w * AspectRatio();
      RectF rect = {mouse_pos.x - w, mouse_pos.y - h, w * 2, h * 2};
      auto image_name = Cursor::get()->GetCursorImageName();
      DrawImage(image_name, rid_image, rect);
   }
}
