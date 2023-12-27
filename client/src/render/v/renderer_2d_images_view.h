#pragma once

#include "renderer_base_view.h"

namespace Narradia
{
   class Renderer2DImagesView : public RendererBaseView, public Singleton<Renderer2DImagesView>
   {
     public:
      Renderer2DImagesView();

      ~Renderer2DImagesView();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
      static constexpr int kLocationUv = 2;
   };
}
