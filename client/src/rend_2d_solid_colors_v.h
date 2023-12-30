#pragma once

#include "rend-core_v.h"

namespace Narradia
{
   class Rend2DSolidColorsV : public RendBaseV, public S<Rend2DSolidColorsV> {
     public:
      Rend2DSolidColorsV();
      ~Rend2DSolidColorsV();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
   };

   // Free functions
#if 1
   auto NewRect() -> RenderID;
   auto DrawRect(RenderID vao_id, RectF rect, Color color) -> void;
   auto FillRect(RenderID vao_id, RectF rect, Color color) -> void;
#endif
}
