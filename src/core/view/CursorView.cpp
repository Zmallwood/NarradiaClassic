#include "CursorView.h"
#include "core.render/view/Renderer2DImagesView.h"
#include "core/model/Cursor.h"

namespace Narradia {
    /**
     * Hides default system cursor and prepares RenderIDs.
     */
    CursorView::CursorView() {
        SDL_ShowCursor(0);
        rid_image = Renderer2DImagesView::Get()->NewImage();
    }

    /**
     * Renders custom cursor image at mouse position.
     */
    void CursorView::RenderCursor() {
        auto mouse_pos = GetMousePosition();
        auto width = kCursorWidth;
        auto height = width * GetAspectRatio();
        RectF rect = {mouse_pos.x - width, mouse_pos.y - height, width * 2, height * 2};
        auto image_name = Cursor::Get()->GetCursorImageName();
        Renderer2DImagesView::Get()->DrawImage(image_name, rid_image, rect);
    }
}
