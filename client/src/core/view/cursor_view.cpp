#include "cursor_view.h"
#include "core.render/view/command/draw_image.h"
#include "core.render/view/command/new_image.h"
#include "core/model/cursor.h"
namespace Narradia
{
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
        auto mouse_pos = MousePosition();
        auto width = kCursorWidth;
        auto height = width * AspectRatio();
        RectF rect = {mouse_pos.x - width, mouse_pos.y - height, width * 2, height * 2};
        auto image_name = Cursor::get()->GetCursorImageName();
        DrawImage(image_name, rid_image, rect);
    }
}
