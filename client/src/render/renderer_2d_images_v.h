#pragma once

#include "renderer_base_v.h"

namespace Narradia
{
   class Renderer2DImagesV : public RendererBaseV, public S<Renderer2DImagesV>
   {
     public:
      Renderer2DImagesV();
      ~Renderer2DImagesV();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
   };
}
