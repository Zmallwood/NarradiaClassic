#pragma once

#include "rend-core.h"

namespace Narradia
{
   // View
#if 1
   class DrwImagesV : public RendBaseV, public S<DrwImagesV> {
     public:
      DrwImagesV();
      ~DrwImagesV();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
   };

   // Free functions
#if 1
   RenderID NewImage();
   void
   DrawImage(StringView image_name, RenderID rid, const RectF &dest, Color color = Colors::white);
#endif
#endif
}
