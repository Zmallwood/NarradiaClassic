#pragma once
#include "core.input/model/kb_input.h"
#include "core/model/scene_mngr.h"
#include "main_scene.gui/model/experience_bar.h"
#include "text_line.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Renders text lines to a box available in all scenes, takes text input to be renderer
   /// through the Print function.
   ////////////////////////////////////////////////////////////////////////////////
   class TextOutBox : public Singleton<TextOutBox> {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Checks if input should be activated and processed typed input characters.
      ////////////////////////////////////////////////////////////////////////////////
      auto UpdateGameLogic() -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Adds provided text with color to the internal data structure, beind ready for
      /// rendering.
      ///
      /// @param[in] text Text to be printed.
      /// @param[in] text_color Color of the text to be printed.
      ////////////////////////////////////////////////////////////////////////////////
      auto Print(std::string_view text, Color text_color = Colors::wheat) -> void;

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Calculates the maximum number of text lines that can be displayed in the text box
      /// without overflowing.
      ///
      /// @return Maximum number of text lines.
      ////////////////////////////////////////////////////////////////////////////////
      auto MaxNumLines() -> int;

      auto TextLineIndex(int visible_row_index) -> int;

      auto TextLinePosition(int visible_row_index) -> PointF;

      auto HorizontalSplitterRect() -> RectF;

      auto InputArrowRect() -> RectF;

      auto InputTextPosition() -> PointF;

      auto InputTextWithCursor() -> std::string;

      auto Bounds() -> RectF;

      auto text_lines() {
         return text_lines_;
      }

      auto enabled() {
         return enabled_;
      }

      auto input_active() {
         return input_active_;
      }

      auto cursor_position() {
         return cursor_position_;
      }

      auto input_text() {
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
