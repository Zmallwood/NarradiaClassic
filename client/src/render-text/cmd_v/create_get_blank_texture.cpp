#if 1
#include "create_get_blank_texture.h"
#include "assets.h"
#endif

namespace Narradia
{
   auto CreateGetBlankTexture() -> std::string {
      static int id_counter = 0;
      auto id = id_counter++;
      auto unique_name = "RenderedImage" + std::to_string(id);
      ImageBank::get()->CreateBlankTextImage(unique_name);
      return unique_name;
   }
}
