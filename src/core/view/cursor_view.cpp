#include "cursor_view.h"
#include "core.render/view/renderer_2d_images_view.h"
#include "core.render/view/command/draw_image.h"
#include "core.render/view/command/new_image.h"
#include "core/model/cursor.h"

namespace Narradia {
  /**
   Hides default system cursor and prepares RenderIDs.
  */
  CursorView::CursorView() {
    SDL_ShowCursor(0);
    rid_image = NewImage();
  }

  /**
   Renders custom cursor image at mouse position.
  */
  void CursorView::RenderCursor() {
    auto mouse_pos = GetMousePosition();
    auto width = kCursorWidth;
    auto height = width * GetAspectRatio();
    RectF rect = {mouse_pos.x - width, mouse_pos.y - height, width * 2, height * 2};
    auto image_name = Cursor::Get()->GetCursorImageName();
    DrawImage(image_name, rid_image, rect);
  }
}
