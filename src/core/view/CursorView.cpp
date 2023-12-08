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
        RectF rect = {
            mouse_pos.x - width, mouse_pos.y - height, width * 2, height * 2};
        std::string_view image_name;
        switch (Cursor::Get()->cursor_style()) {
        case CursorStyles::Default:
            image_name = "CursorDefault";
            break;
        case CursorStyles::Hovering:
            image_name = "CursorHovering";
            break;
        case CursorStyles::Rotating:
            image_name = "CursorRotating";
            break;
        case CursorStyles::Attack:
            image_name = "CursorAttack";
            break;
        }
        Renderer2DImagesView::Get()->DrawImage(image_name, rid_image, rect);
    }
}
