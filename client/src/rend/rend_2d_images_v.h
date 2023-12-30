#pragma once

#include "rend_base_v.h"

namespace Narradia
{
   class Rend2DImagesV : public RendBaseV, public S<Rend2DImagesV> {
     public:
      Rend2DImagesV();
      ~Rend2DImagesV();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
   };

   auto NewImage() -> RenderID;

   auto DrawImage(
       std::string_view image_name, RenderID rid, const RectF &dest, Color color = Colors::white)
       -> void;
}
