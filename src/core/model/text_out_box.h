#pragma once
#include "text_line.h"
namespace Narradia {
  /**
   Renders text lines to a box available in all scenes,
   takes text input to be rendered through the Print
   function.
  */
  class TextOutBox : public Singleton<TextOutBox> {
   public:
    void UpdateGameLogic();
    void Print(std::string_view text, Color text_color = Colors::wheat);
    int GetMaxNumLines();
    int GetTextLineIndex(int visible_row_index);
    PointF GetTextLinePosition(int visible_row_index);
    RectF GetHorizontalSplitterRect();
    RectF GetInputArrowRect();
    PointF GetInputTextPosition();
    std::string GetInputTextWithCursor();

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

    static constexpr RectF kBounds = {0.0f, 0.8f, 0.3f, 0.2f};
    static constexpr float kTextLineHeight = 0.02f;
    static constexpr float kSplitLineHeight = 0.001f;

   private:
    std::vector<TextLine> text_lines_;
    bool enabled_ = true;
    bool input_active_ = false;
    int cursor_position_ = 0;
    std::string input_text_;
  };
}
