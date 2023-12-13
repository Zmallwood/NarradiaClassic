#include "new_string.h"
#include "core.render.text/view/renderer_text.h"
#include "core.render/view/command/new_image.h"
#include "create_get_blank_texture.h"
namespace Narradia
{
    /**
     Prepares resources for a new string to be rendered.
    */
    RenderID NewString() {
        auto unique_name = CreateGetBlankTexture();
        auto rendid_image_rect = NewImage();
        RendererText::get()->unique_name_ids()->insert({rendid_image_rect, unique_name});
        return rendid_image_rect;
    }
}
