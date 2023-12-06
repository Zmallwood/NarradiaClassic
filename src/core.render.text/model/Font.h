#pragma once

namespace Narradia {
    class Font {
      public:
        Font(std::string_view font_file_name, int font_size);

        std::shared_ptr<TTF_Font> SDL_font() {
            return SDL_font_;
        }

        std::shared_ptr<TTF_Font> outline_SDL_font() {
            return outline_SDL_font_;
        }

        static constexpr int kFontOutlineWidth = 2;

      private:
        std::shared_ptr<TTF_Font> SDL_font_;
        std::shared_ptr<TTF_Font> outline_SDL_font_;
    };
}