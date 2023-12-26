#pragma once
#include "../../core-render-shaders/m/2d_solid_colors_fragment.inc.cpp"
#include "../../core-render-shaders/m/2d_solid_colors_vertex.inc.cpp"
#include "renderer_base_view.h"
namespace Narradia
{
   ////////////////////////////////////////////////////////////////////////////////
   /// @brief Prepares resources and renders color-filled rectangles to the canvas.
   ////////////////////////////////////////////////////////////////////////////////
   class Renderer2DSolidColorsView : public RendererBaseView,
                                     public Singleton<Renderer2DSolidColorsView>
   {
     public:
      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Creates the shader program from shader sources.
      ////////////////////////////////////////////////////////////////////////////////
      Renderer2DSolidColorsView();

      ////////////////////////////////////////////////////////////////////////////////
      /// @brief Forwarding the cleanup command to render view base.
      ////////////////////////////////////////////////////////////////////////////////
      ~Renderer2DSolidColorsView();

      static constexpr int kLocationPosition = 0;
      static constexpr int kLocationColor = 1;
   };
}
