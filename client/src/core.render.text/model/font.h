#pragma once
#include <memory>
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Holds SDL font objects for a single font with a specfic size, requires two, one
   /// regular and one for the outline.
   ////////////////////////////////////////////////////////////////////////////////
   class Font {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Creates the SDL font objects and set font outline width.
      ///
      /// @param[in] font_file_name Font file name, with path.
      /// @param[in] font_size Font size to use for the new font.
      ////////////////////////////////////////////////////////////////////////////////
      Font(std::string_view font_file_name, int font_size);

      auto SDL_font() {
         return SDL_font_;
      }

      auto outline_SDL_font() {
         return outline_SDL_font_;
      }

      static constexpr int kFontOutlineWidth = 2;

     private:
      std::shared_ptr<TTF_Font> SDL_font_;
      std::shared_ptr<TTF_Font> outline_SDL_font_;
   };
}
