#pragma once

#include "render-shaders/m/2d_solid_colors_fragment.inc.cpp"
#include "render-shaders/m/2d_solid_colors_vertex.inc.cpp"
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
