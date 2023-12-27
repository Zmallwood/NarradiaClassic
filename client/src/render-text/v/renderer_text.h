#pragma once

namespace Narradia
{
   enum class FontSizes
   {
      _20,
      _40
   };

   class Font;

   class RendererText : public Singleton<RendererText>
   {
     public:
      RendererText();

      auto RenderText(
          RenderID rid, std::string_view text, Color color, bool center_align, FontSizes font_size,
          std::string &out_unique_name_id, SizeF &out_size) const -> void;

      auto fonts()
      {
         return fonts_;
      }

      auto unique_name_ids()
      {
         return unique_name_ids_;
      }

     private:
      const std::string kRelFontsPath = "Resources/Fonts/";
      const Color kOutlineColor = {0.0f, 0.0f, 0.0f, 1.0f};
      std::map<FontSizes, std::shared_ptr<Font>> fonts_;
      std::shared_ptr<std::map<RenderID, std::string>> unique_name_ids_;
   };
}
