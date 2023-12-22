#include "new_string.h"
namespace Narradia
{
   auto NewString() -> RenderID {
      auto unique_name = CreateGetBlankTexture();
      auto rendid_image_rect = NewImage();
      RendererText::get()->unique_name_ids()->insert({rendid_image_rect, unique_name});
      return rendid_image_rect;
   }
}
