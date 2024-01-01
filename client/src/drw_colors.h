#pragma once

#include "rend-core.h"

namespace Narradia
{
   // View
#if 1
   class DrwColorsV : public RendBaseV, public S<DrwColorsV> {
     public:
      DrwColorsV();
      ~DrwColorsV();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
   };

   // Free functions
#if 1
   auto NewRect() -> RenderID;
   auto DrawRect(RenderID vao_id, RectF rect, Color color) -> void;
   auto FillRect(RenderID vao_id, RectF rect, Color color) -> void;
#endif
#endif
}
