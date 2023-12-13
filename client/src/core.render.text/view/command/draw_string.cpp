#include "draw_string.h"
#include "core.render.text/model/font.h"
#include "core.render.text/view/renderer_text.h"
#include "core.render/view/command/draw_image.h"
namespace Narradia
{
    /**
     Draws a string to the canvas, requires it to first have
     been initialized with NewString().
    */
    void DrawString(
        RenderID rid, std::string_view text, PointF position, Color color, bool center_align,
        FontSizes font_size) {
        std::string unique_name_id;
        SizeF size;
        RendererText::get()->RenderText(
            rid, text, color, center_align, font_size, unique_name_id, size);
        auto canvas_size = GetCanvasSize();
        auto rect = RectF{position.x, position.y, size.w, size.h};
        int text_w;
        int text_h;
        TTF_SizeText(
            RendererText::get()->fonts().at(font_size)->SDL_font().get(), text.data(), &text_w,
            &text_h);
        rect.y -= static_cast<float>(text_h / GetAspectRatio()) / canvas_size.h / 2.0f;
        if (center_align)
            rect.x -= static_cast<float>(text_w) / static_cast<float>(canvas_size.h) / 2.0f /
                      GetAspectRatio();
        DrawImage(unique_name_id, rid, rect);
    }
}
