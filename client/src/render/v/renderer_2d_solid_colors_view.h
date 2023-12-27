#pragma once

#include "renderer_base_view.h"

namespace Narradia
{
   class Renderer2DSolidColorsView : public RendererBaseView,
                                     public Singleton<Renderer2DSolidColorsView>
   {
     public:
      Renderer2DSolidColorsView();

      ~Renderer2DSolidColorsView();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
   };
}
