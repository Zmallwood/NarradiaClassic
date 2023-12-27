#pragma once

namespace Narradia
{
   // Show sub classes
#if 1
   class TextLine
   {
     public:
      std::string text;
      Color color;
   };
#endif

   class Console : public S<Console>
   {
     public:
      auto UpdateGameLogic() -> void;
      auto Print(std::string_view text, Color text_color = Colors::wheat) -> void;
      auto InputTextWithCursor() -> std::string;
      auto Bounds() -> RectF;
      auto text_lines()
      {
         return text_lines_;
      }
      auto enabled()
      {
         return enabled_;
      }
      auto input_active()
      {
         return input_active_;
      }
      auto cursor_position()
      {
         return cursor_position_;
      }
      auto input_text()
      {
         return input_text_;
      }

      static constexpr float kTextLineHeight = 0.02f;
      static constexpr float kSplitLineHeight = 0.001f;

     private:
      static constexpr RectF kDefaultBounds = {0.0f, 0.8f, 0.3f, 0.2f};

      std::vector<TextLine> text_lines_;
      bool enabled_ = true;
      bool input_active_ = false;
      int cursor_position_ = 0;
      std::string input_text_;
   };
}
