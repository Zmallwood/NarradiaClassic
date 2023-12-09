#pragma once

namespace Narradia {
    /**
     Helper class for automatically free SDL resources.
    */
    class SDLDeleter {
      public:
        void operator()(SDL_Window *window);
        void operator()(SDL_Renderer *renderer);
        void operator()(SDL_Surface *surface);
        void operator()(SDL_Texture *texture);
        void operator()(TTF_Font *font);
    };
}
