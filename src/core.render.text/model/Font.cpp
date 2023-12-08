#include "Font.h"

namespace Narradia {
    /**
     * Initialize two SDL fonts, one regular and one for the outline. Also,
     * specify outline width.
     */
    Font::Font(std::string_view font_file_name, int font_size) {
        SDL_font_ = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(font_file_name.data(), font_size), SDLDeleter());
        outline_SDL_font_ = std::shared_ptr<TTF_Font>(
            TTF_OpenFont(font_file_name.data(), font_size), SDLDeleter());
        TTF_SetFontOutline(outline_SDL_font_.get(), kFontOutlineWidth);
    }
}
