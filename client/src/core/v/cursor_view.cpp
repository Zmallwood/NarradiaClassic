#if 1
#include "cursor_view.h"
#include "render/v/cmd/draw_image.h"
#include "render/v/cmd/new_image.h"
#include "core/m/cursor.h"
#endif

namespace Narradia
{
   CursorView::CursorView()
   {
      SDL_ShowCursor(0);
      rid_image = NewImage();
   }

   auto CursorView::RenderCursor() -> void
   {
      auto mouse_pos = MousePosition();
      auto w = kCursorWidth;
      auto h = w * AspectRatio();
      RectF rect = {mouse_pos.x - w, mouse_pos.y - h, w * 2, h * 2};
      auto image_name = Cursor::get()->GetCursorImageName();
      DrawImage(image_name, rid_image, rect);
   }
}
