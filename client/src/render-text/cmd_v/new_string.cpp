#if 1
#include "new_string.h"
#include "create_get_blank_texture.h"
#include "render-text/renderer_text.h"
#include "render/renderer_2d_images_v.h"
#endif

namespace Narradia
{
   auto NewString() -> RenderID {
      auto unique_name = CreateGetBlankTexture();
      auto rendid_image_rect = NewImage();
      RendererText::get()->unique_name_ids()->insert({rendid_image_rect, unique_name});
      return rendid_image_rect;
   }
}
