#include "sdl_deleter.h"

namespace Narradia
{
   void SDLDeleter::operator()(SDL_Window *win)
   {
      SDL_DestroyWindow(win);
   }

   void SDLDeleter::operator()(SDL_Renderer *rend)
   {
      SDL_DestroyRenderer(rend);
   }

   void SDLDeleter::operator()(SDL_Surface *surf)
   {
      SDL_FreeSurface(surf);
   }

   void SDLDeleter::operator()(SDL_Texture *tex)
   {
      SDL_DestroyTexture(tex);
   }

   void SDLDeleter::operator()(TTF_Font *font)
   {
      TTF_CloseFont(font);
   }
}
