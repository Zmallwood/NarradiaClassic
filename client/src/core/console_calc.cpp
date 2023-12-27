#include "console_calc.h"
#include "console.h"

namespace Narradia
{
   auto ConsoleCalc::MaxNumLines() -> int
   {
      return static_cast<int>(Console::get()->Bounds().h / Console::kTextLineHeight) - 2;
   }
   auto ConsoleCalc::TextLineIndex(int visible_row_index) -> int
   {
      return static_cast<int>(Console::get()->text_lines().size()) - MaxNumLines() +
             visible_row_index;
   }
   auto ConsoleCalc::InputTextPosition() -> PointF
   {
      return InputArrowRect().GetPosition().Translate(
          Console::kTextLineHeight, Console::kTextLineHeight / 2);
   }
   auto ConsoleCalc::TextLinePosition(int visible_row_index) -> PointF
   {
      return {
          Console::get()->Bounds().x + 0.01f,
          Console::get()->Bounds().y + (visible_row_index + 1) * Console::kTextLineHeight};
   }
   auto ConsoleCalc::HorizontalSplitterRect() -> RectF
   {
      return {
          0.0f,
          Console::get()->Bounds().y + Console::get()->Bounds().h - 1.3f * Console::kTextLineHeight,
          Console::get()->Bounds().w, Console::kSplitLineHeight};
   }
   auto ConsoleCalc::InputArrowRect() -> RectF
   {
      return {
          0.0f,
          Console::get()->Bounds().y + Console::get()->Bounds().h - 1.3f * Console::kTextLineHeight,
          Console::kTextLineHeight, Console::kTextLineHeight};
   }
}
