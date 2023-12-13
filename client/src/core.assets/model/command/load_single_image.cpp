#include "load_single_image.h"
namespace Narradia
{
   GLuint tex_id;
   SDL_Surface *surf;

   auto LoadSingleImage(std::string_view abs_file_path) -> GLuint {
      surf = IMG_Load(abs_file_path.data());
      glEnable(GL_TEXTURE_2D);
      glGenTextures(1, &tex_id);
      glBindTexture(GL_TEXTURE_2D, tex_id);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      if (surf->format->BytesPerPixel == 4) {
         glTexImage2D(
             GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
             surf->pixels);
      }
      else {
         glTexImage2D(
             GL_TEXTURE_2D, 0, GL_RGBA, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE,
             surf->pixels);
      }
      SDL_FreeSurface(surf);
      return tex_id;
   }
}
