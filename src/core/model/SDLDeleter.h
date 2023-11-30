#pragma once

namespace Narradia {
    /**
     * Helper class for automatically free SDL resources.
     */
    class SDLDeleter {
      public:
        void operator()(SDL_Window *);

        void operator()(SDL_Renderer *);

        void operator()(SDL_Surface *);

        void operator()(SDL_Texture *);

        void operator()(TTF_Font *);
    };
}
