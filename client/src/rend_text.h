#pragma once

namespace Narradia
{
   // View
#if 1
   enum class FontSizes { _20, _40 };

   class Font;

   class RendTextV : public S<RendTextV> {
     public:
      RendTextV();
      ~RendTextV();
      void RenderText(
          RenderID rid, std::string_view text, Color color, bool center_align, FontSizes font_size,
          std::string &out_unique_name_id, SizeF &out_size) const;
      auto fonts() {
         return fonts_;
      }
      auto unique_name_ids() {
         return unique_name_ids_;
      }

     private:
      const std::string kRelFontsPath = "Resources/Fonts/";
      const Color kOutlineColor = {0.0f, 0.0f, 0.0f, 1.0f};
      std::map<FontSizes, std::shared_ptr<Font>> fonts_;
      std::shared_ptr<std::map<RenderID, std::string>> unique_name_ids_;
   };

   // Belonging Font class
#if 1
   class Font {
     public:
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
#endif

   // Free functions
#if 1
   auto NewString() -> RenderID;

   auto DrawString(
       RenderID rid, std::string_view text, PointF position, Color color = Colors::white,
       bool center_align = false, FontSizes font_size = FontSizes::_20) -> void;
#endif
#endif
}
