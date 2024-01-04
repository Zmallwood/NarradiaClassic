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
   RenderID NewRect();
   void DrawRect(RenderID vao_id, RectF rect, Color color);
   void FillRect(RenderID vao_id, RectF rect, Color color);
#endif
#endif
}
