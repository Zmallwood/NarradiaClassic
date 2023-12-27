#pragma once

namespace Narradia
{
   class SDLDeleter
   {
     public:
      void operator()(SDL_Window *win);

      void operator()(SDL_Renderer *rend);

      void operator()(SDL_Surface *surf);

      void operator()(SDL_Texture *tex);

      void operator()(TTF_Font *font);
   };
}
