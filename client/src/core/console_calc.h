#pragma once

namespace Narradia
{
   class ConsoleCalc : public S<ConsoleCalc>
   {
     public:
      auto MaxNumLines() -> int;
      auto TextLineIndex(int visible_row_index) -> int;
      auto TextLinePosition(int visible_row_index) -> PointF;
      auto HorizontalSplitterRect() -> RectF;
      auto InputArrowRect() -> RectF;
      auto InputTextPosition() -> PointF;
   };
}
