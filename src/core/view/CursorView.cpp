#include "CursorView.h"
#include "core.render/view/Renderer2DImagesView.h"

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
        RectF rect = {
            mouse_pos.x - width, mouse_pos.y - height, width * 2, height * 2};
        Renderer2DImagesView::Get()->DrawImage("CursorDefault", rid_image, rect);
    }
}
