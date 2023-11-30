#include "ImageDrawingView.h"
#include "core.assets/model/ImageBank.h"
#include "core/model/Graphics.h"

namespace Narradia {
    void ImageDrawingView::DrawImage(std::string_view image_name, RectF rect) {
        auto canvas_size = GetCanvasSize();

        SDL_Rect sdl_rect_pixels = {
            rect.x * canvas_size.width, rect.y * canvas_size.height,
            rect.width * canvas_size.width, rect.height * canvas_size.height};

        auto image = ImageBank::Get()->GetImage(image_name);
        
        SDL_RenderCopy(
            Graphics::Get()->renderer().get(), image, NULL, &sdl_rect_pixels);
    }
}