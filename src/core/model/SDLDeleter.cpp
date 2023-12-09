#include "SDLDeleter.h"

namespace Narradia {
    /**
     Destroy window when no longer used.
    */
    void SDLDeleter::operator()(SDL_Window *window) { SDL_DestroyWindow(window); }

    /**
     Destroy renderer when no longer used.
    */
    void SDLDeleter::operator()(SDL_Renderer *renderer) { SDL_DestroyRenderer(renderer); }

    /**
     Free surface when no longer used.
    */
    void SDLDeleter::operator()(SDL_Surface *surface) { SDL_FreeSurface(surface); }

    /**
     Destroy texture when no longer used.
    */
    void SDLDeleter::operator()(SDL_Texture *texture) { SDL_DestroyTexture(texture); }

    /** 
     Close font when no longer used.
    */
    void SDLDeleter::operator()(TTF_Font *font) { TTF_CloseFont(font); }
}
