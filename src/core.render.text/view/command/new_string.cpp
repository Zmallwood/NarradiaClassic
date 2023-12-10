#include "new_string.h"
#include "../renderer_text.h"
#include "create_get_blank_texture.h"
#include "core.render/view/command/new_image.h"

namespace Narradia {
  /**
   Prepares resources for a new string to be rendered.
  */
  RenderID NewString() {
    auto unique_name = CreateGetBlankTexture();
    auto rendid_image_rect = NewImage();
    RendererText::Get()->unique_name_ids()->insert({rendid_image_rect, unique_name});
    return rendid_image_rect;
  }
}
